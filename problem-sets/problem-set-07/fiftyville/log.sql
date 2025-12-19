-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Discover what happened on July 28, 2024, at Humphrey Street.
SELECT description 
FROM crime_scene_reports
WHERE year = 2024
  AND month = 7
  AND day = 28  
  AND street = 'Humphrey Street';

/*
  Theft confirmed at 10:15am at the Humphrey Street Bakery.
  Three witnesses were present, and all mentioned the bakery in their transcripts.
*/

-- Find interviews from July 28, 2024, that mention the bakery.
SELECT name, transcript 
FROM interviews 
WHERE transcript LIKE '%bakery%'
  AND year = 2024
  AND month = 7
  AND day = 28;

/*
  Ruth: The thief drove away from the bakery parking lot within 10 minutes of the theft.
  Eugene: The thief withdrew money from the ATM on Leggett Street earlier that morning.
  Raymond: The thief called someone for less than a minute to buy the earliest flight for tomorrow.
*/

-- Check bakery parking lot activity on July 28, 2024.
SELECT license_plate, hour, minute
FROM bakery_security_logs
WHERE year = 2024
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute >= 15
  AND minute <= 25
  AND activity = 'exit';

/* 
  Suspects' license plates:
  5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55
*/

-- Check ATM withdrawals on Leggett Street on July 28, 2024.
SELECT account_number
FROM atm_transactions
WHERE year = 2024
  AND month = 7
  AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

/*
  Suspects' account numbers:
  28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199
*/

-- Check phone calls on July 28, 2024 that lasted less than a minute.
SELECT caller 
FROM phone_calls
WHERE year = 2024
  AND month = 7
  AND day = 28
  AND duration < 60;

/*
  Suspects' phone numbers:
  (130) 555-0289, (499) 555-9472, (367) 555-5533, (286) 555-6063, (770) 555-1861, (031) 555-6622, (826) 555-1652, (338) 555-6650
*/

-- Cross-reference data to identify the suspect.
SELECT name 
FROM people
WHERE phone_number IN (
    '(130) 555-0289', 
    '(499) 555-9472', 
    '(367) 555-5533', 
    '(286) 555-6063', 
    '(770) 555-1861', 
    '(031) 555-6622', 
    '(826) 555-1652', 
    '(338) 555-6650'
  )
  AND license_plate IN (
    '5P2BI95', 
    '94KL13X', 
    '6P58WS2', 
    '4328GD8', 
    'G412CB7', 
    'L93JTIZ', 
    '322W7JE', 
    '0NTHK55'
  );

/*
  Suspects' list:
  Sofia, Diana, Kelsey, Bruce
*/

-- Cross-reference the remaining suspects with the account numbers.
SELECT name 
FROM people
WHERE id IN (
    SELECT person_id 
    FROM bank_accounts
    WHERE account_number IN (
        28500762, 28296815, 76054385, 49610011, 
        16153065, 25506511, 81061156, 26013199
    )
)
AND name IN ('Sofia', 'Diana', 'Kelsey', 'Bruce');

--Remaining suspects: Diana, Bruce

-- Check the earliest flight out of Fiftyville and its destination on July 29, 2024.
SELECT flights.id, airports.city
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
)
AND YEAR = 2024
AND MONTH = 7
AND DAY = 29
ORDER BY hour, minute
LIMIT 1;

-- The flight's id is 36 and it was going to New York City.

-- Check which suspect booked flight id 36 on July 29, 2024.
SELECT name 
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = 36
AND name IN ('Diana', 'Bruce');

-- Thief identified: Bruce

-- Discover Bruce's accomplice by checking who received his call on July 28, 2024.
SELECT accomplice.name
FROM phone_calls
JOIN people thief ON phone_calls.caller = thief.phone_number
JOIN people accomplice ON phone_calls.receiver = accomplice.phone_number
WHERE thief.name = 'Bruce'
AND year = 2024
AND month = 7
AND day = 28
AND duration < 60;

-- Accomplice identified: Robin