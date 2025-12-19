while (True):
  try:
    height = int(input("Height: "))
    if 1 <= height <= 8:
     break
    else:
    print("Height must be between 1 and 8")
  except ValueError:
    print("Please enter a valid integer")

for row in range(1, height + 1):
  spaces = " " * (height - row)
  hashes = "#" * row
  print(f"{spaces}{hashes}  {hashes}")