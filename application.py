import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    row = db.execute("SELECT symbol, name, sum(shares) FROM transactions WHERE user_id = (?) group by symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])

    list = []
    new = []
    total = []

    for rows in row:
        list.append(rows["symbol"])

    for lists in list:
        query = lookup(lists)
        new.append(query["price"])

    for i in range(len(row)):
        for j in range(len(new)):
            if i > j:
                j = i
            row[i]['prices'] = new[j]
            break

    for rows in row:
        rows["total"] = rows["sum(shares)"] * rows["prices"]

    for rows in row:
        total.append(rows["total"])

    for cashs in cash:
        total.append(cashs["cash"])

    grand_total = int(sum(total))

    return render_template("index.html", row=row, new=new, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        query = lookup(symbol)
        if query is None:
            return apology("Invalid symbol", 403)

        shares = request.form.get("shares")

        if shares == '':
            return apology("Missing shares", 403)


        # saving lookup result into variables
        price = query["price"]
        name = query["name"]
        symbols = query["symbol"]
        userid = session["user_id"]

        # caluclating total price of transaction and quering user's available cash
        total = price * int(shares)
        cash = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])
        available = cash[0]["cash"]

        # if user doesn't have enough money
        if total > available:
            return apology("Insufficient funds", 403)

        # purchase registered in table transactions and amount spent subtracted from cash in users table
        else:
            db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)", userid, symbols, name, shares, price, total)
            db.execute("INSERT INTO history (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)", userid, symbols, name, shares, price, total)
            db.execute("UPDATE users SET cash = cash - (?) WHERE id = (?)", total, session["user_id"])
            return redirect("/", 302)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    row = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = (?)", session["user_id"])
    return render_template("history.html", row=row)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        message = lookup(symbol)
        if message is None:
            return apology("Invalid symbol", 403)
        name = message["name"]
        price = message["price"]
        symbols = message["symbol"]
        return render_template("quoted.html", name=name, price=price, symbols=symbols)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # if method is get simply render register.html """
    if request.method == "GET":
        return render_template("register.html")

    # if method is post check if username and password fields are empty first
    else:
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 403)
        check = db.execute("SELECT username FROM users")
        for checks in check:
            if checks["username"] == username:
                return apology("username taken", 403)

        password = request.form.get("password")
        if not password:
            return apology("must provide password", 403)

        password_confirmation = request.form.get("confirmation")
        if not password_confirmation:
            return apology("must confirm password", 403)

        if password != password_confirmation:
            return apology("passwords don't match", 403)

        # if username and password are good then insert user into table
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=generate_password_hash(password))
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        symbol = db.execute("SELECT symbol FROM transactions WHERE user_id = (?) GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbol=symbol)

    else:
        # checking for empty shares field
        shares = request.form.get("shares")
        if shares == '':
            return apology("Numbers of shares missing", 403)

        symbol = request.form.get("symbol")
        # querying the number of shares user owns
        position = db.execute("SELECT sum(shares) FROM transactions WHERE user_id = (?) and symbol = (?)", session["user_id"], symbol)

        # saving the query result into a variable
        for positions in position:
            shares_number = int(positions["sum(shares)"])

        # checking if user actually owns that many shares to sell
        if shares_number < int(shares):
            return apology("You don't own this many shares", 403)

        # lookup the current price of the shares to be sold
        query = lookup(symbol)
        if query is None:
            return apology("Invalid symbol", 403)

        # saving lookup result into variables
        price = query["price"]
        name = query["name"]
        symbols = query["symbol"]
        userid = session["user_id"]

        # converting shares into a negative int
        new_shares = int(shares) * (-1)

        # caluclating total price of transaction
        total = price * int(shares)

        # purchase registered in table transactions and amount sold added to cash in users table
        db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)", userid, symbols, name, new_shares, price, total)
        db.execute("INSERT INTO history (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)", userid, symbols, name, new_shares, price, total)
        db.execute("UPDATE users SET cash = cash + (?) WHERE id = (?)", total, session["user_id"])

        return redirect("/", 302)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
