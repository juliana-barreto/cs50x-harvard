while True:
  try:
      dollar = float(input("Change (in dollars): "))
      if dollar >= 0:
          break
      else:
          print("Please enter a positive number")
  except ValueError:
      print("Please enter a valid number")

cents = round(dollar * 100)

quarters = cents//25
## Update change to reflect remaining amount
cents = cents % 25

dimes = cents//10
cents = cents % 10

nickels = cents//5    
cents = cents % 5

## Remaining change is all in pennies
pennies = cents

total_coins = quarters + dimes + nickels + pennies
print(total_coins)
