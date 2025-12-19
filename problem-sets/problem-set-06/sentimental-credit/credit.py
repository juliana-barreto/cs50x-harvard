from sys import exit
import re

def is_card(card_number):
  numbers_list = [int(digit) for digit in card_number]
  sum = 0
  ## Multiply every other digit by 2, starting with the number's second-to-last digit
  for digit in numbers_list[-2::-2]:
    product = digit * 2
    ## Add only the digits of the products (e.g., 12: 1 + 2 = 3)
    if product > 9:
       sum += (product // 10) + (product % 10)
    else:
       sum += product
  ## Add the sum to the sum of the digits that were not multiplied by 2
  for digit in numbers_list[::-2]:
    sum += digit
  ## If the total’s last digit is 0, the number is valid
  return sum % 10 == 0

def brand_checker(card_number):
   ## American Express: 15 digits, starts with 34 or 37
   if re.match(r"^3[47]\d{13}$", card_number):
    return "AMEX"
   ## MasterCard: 16 digits, starts with 51, 52, 53, 54, or 55
   if re.match(r"^5[1-5]\d{14}$", card_number):
    return "MASTERCARD"
   ## VISA: 13 or 16 digits, starts with 4
   if re.match(r"^4(\d{12}|\d{15})", card_number):
    return "VISA"
   ## If none of the above, return INVALID
   return "INVALID"

card_number = input("Number: ")

if not card_number.isdigit():
    print("INVALID")
    exit(0)

length = len(card_number)
if length not in [13, 15, 16]:
    print("INVALID")
    exit(0)

if is_card(card_number):
    print(brand_checker(card_number))
else:
   print("INVALID")
   exit(0)