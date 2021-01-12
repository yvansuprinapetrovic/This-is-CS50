import urllib.parse
import json
import requests

# International Space Station Current Location

# calling the api
def location():

    # Contact API
    try:
        response = requests.get("http://api.open-notify.org/iss-now.json")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return quote
    except (KeyError, TypeError, ValueError):
        return None


# api here http://open-notify.org/Open-Notify-API/ISS-Location-Now/


# this could be another idea: NASA API! https://api.nasa.gov/index.html
