menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

total = 0.0

## Print menu
print("Welcome to the Taqueria!")
print("Menu:")
for item, price in menu.items():
  print(f"{item}: ${price:.2f}")

while (True):
  try:
    ## Get user input
    item = input("Item: ").title()
    ## Check if item is in menu
    if item in menu:
      ## Add item price to total and print it
      total += menu[item]
      print(f"Total: ${total:.2f}")
  ## Handle end of input (Ctrl+D)
  except EOFError:
    break;