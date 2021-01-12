-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Starting out from the only info we have available: the crime took place in Chamberlin Street on the 28th of July
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Report: "Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse."
-- Report: "Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse."

-- Let's take a look at the interviews transcripts from the 28th of July and see if anyone mentions the courthouse

SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- Transcript #1: Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Hint: we can look at the courthouse_security_logs to see if we can retrieve a license plate leaving between 10 and 11 am

-- Transcript #2: I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Hint: check the atm_transactions db to retrieve a bank account id

-- Transcript #3: As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that
-- they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Hint: two tables to check: phone_calls and airports

SELECT license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;

-- Hint: 14 licence plates where recorded on that day and hour
-- Hint: However 9 of them left the courthouse at 10 while just 5 were entering
-- The owners of the following plates are all suspects now. One of them must be the thief:
-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55, 1106N58

SELECT name, phone_number, passport_number, license_plate FROM people WHERE license_plate IN
("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55", "1106N58");

-- What follow is the list of suspects, their phone numbers, passport numbers and license plate. All of these people left the courthouse between 10 and 11.
-- name | phone_number      | passport_number | license_plate
-- Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
-- Amber | (301) 555-4174 | 7526138472 | 6P58WS2
-- Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- Roger | (130) 555-0289 | 1695452385 | G412CB7
-- Madison | (286) 555-6063 | 1988161715 | 1106N58
-- Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Let's check the phone calls table now, one of the witnesses said that the thief called between 10 and 11 and the duration was under a minute

SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- According to the register Roger, Evelyn, Ernest, Madison and Russel all made a phone call of that duration
-- This is our new, shortened list of suspects:
-- name | phone_number      | passport_number | license_plate
-- Roger | (130) 555-0289 | 1695452385 | G412CB7
-- Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- Madison | (286) 555-6063 | 1988161715 | 1106N58
-- Russell | (770) 555-1861 | 3592750733 | 322W7JE

-- Let's look up also the number they called, it might prove useful towards the end of the case

SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
SELECT name, phone_number FROM people WHERE phone_number IN ("(996) 555-8899", "(892) 555-8872", "(717) 555-1342", "(375) 555-8161", "(676) 555-6554", "(725) 555-3243");

-- Name  | caller          | receiver      | name
-- Roger | (130) 555-0289 | (996) 555-8899 | Jack
-- Evelyn | (499) 555-9472 | (892) 555-8872, (717) 555-1342 | Larry, Melissa
-- Ernest | (367) 555-5533 | (375) 555-8161 | Berthold
-- Madison | (286) 555-6063 | (676) 555-6554 | James
-- Russell | (770) 555-1861 | (725) 555-3243 | Philip

-- Time to follow the other hint: the atm
-- "Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money."

SELECT account_number, transaction_type FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- A list of account numbers from which money has been withdrawn on the day of the theft on Fifer Street, as per the witness interview
-- 28500762 | withdraw
-- 28296815 | withdraw
-- 76054385 | withdraw
-- 49610011 | withdraw
-- 16153065 | withdraw
-- 25506511 | withdraw
-- 81061156 | withdraw
-- 26013199 | withdraw

-- Let's see if any of these accounts is linked to one or more of our supsects

SELECT person_id FROM bank_accounts WHERE account_number IN ("28500762", "28296815", "76054385", "49610011", "16153065", "25506511", "81061156", "26013199");

-- Let's look for names now

SELECT name, passport_number FROM people WHERE id IN ("686048", "514354", "458378", "395717", "396669", "467400", "449774", "438727");

-- What follows is a list of names and passport numbers of the people who have used the Fifer Street atm on the day of the theft
-- Bobby | 9878712108
-- Elizabeth | 7049073643
-- Victoria | 9586786673
-- Madison | 1988161715
-- Roy | 4408372428
-- Danielle | 8496433585
-- Russell | 3592750733
-- Ernest | 5773159633

-- Three of our suspesct seem to have used the atm, just like the witness told the police.
-- Our list of supsects is down to these people:
-- Ernest | (367) 555-5533 | 5773159633
-- Madison | (286) 555-6063 | 1988161715
-- Russell | (770) 555-1861 | 3592750733


-- It's time to follow the final clue: the airport ticket
-- "In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket."

SELECT id, full_name FROM airports WHERE city = "Fiftyville";

-- 8 | Fiftyville Regional Airport

SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2020 AND month = 7 AND day = 29;

-- According to the flights db, this is the first flight leaving the city on the 29th:
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 | 8                 | 4                      | 2020 | 7     | 29  | 8    | 20

SELECT full_name, city FROM airports WHERE id = 4;

-- They are leaving the country! Their flight is directed to Heathrow Airport, London

-- But we are two steps ahead of them. Let's not waste time and check the passengers database. If one of our suspects is on that list then he's our guy!

SELECT passport_number FROM passengers WHERE flight_id = 36;

-- Just have to lookup the names now

SELECT name, passport_number FROM people WHERE passport_number IN ("7214083635", "1695452385", "5773159633", "1540955065", "8294398571", "1988161715", "9878712108", "8496433585");

-- Names of passangers boarding on the earliest plane tomorrow morning:
-- Bobby
-- Roger
-- Madison
-- Danielle
-- Evelyn
-- Edward
-- Ernest
-- Doris

-- Our supsects:
-- Ernest | (367) 555-5533 | 5773159633
-- Madison | (286) 555-6063 | 1988161715
-- Russell | (770) 555-1861 | 3592750733

-- Russel can be taken out of our suspect list. Our thief is one between Madison and Ernest
-- The accomplince is instead one between Berthold and James

-- Name  | caller          | receiver      | name
-- Ernest | (367) 555-5533 | (375) 555-8161 | Berthold
-- Madison | (286) 555-6063 | (676) 555-6554 | James

-- Both Ernest and Madison have left the courthouse between 10 and 11, have withdrawn money from the atm on Fifer Street,
-- both have made a phone call of under a minute and finally both are on the earliest flight tomorrow mornign from Fiftyville

-- It's time to take a step back and dig in some other details to solve the case
-- The first witness said the thief left the courthouse within ten minutes from the theft
-- This means between 10:15 and 10:25 am
-- Let's have a closer look to the courthouse_security_logs

SELECT minute FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND license_plate = "94KL13X";
-- License plate 94KL13X left at 10:18, 3 minutes after the theft

SELECT minute FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND license_plate = "1106N58";
-- License plate 1106N58 left at 10:35, 20 minutes after the theft


SELECT name, license_plate FROM people WHERE license_plate IN ("1106N58", "94KL13X");

-- Madison | 1106N58
-- Ernest | 94KL13X

-- Madison left 20 mintues after the theft, while Ernest 3 minutes after. Ernest MUST be the theft and Berthold is accomplince!
