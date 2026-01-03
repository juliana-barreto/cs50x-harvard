from cs50 import SQL
import csv

db = SQL("sqlite:///roster.db")

reader = csv.DictReader(open("students.csv"))

houses = {}

for row in reader:
    
    student = row["student_name"]
    house = row["house"]
    head = row["head"]

    student_id = db.execute("INSERT INTO students (name) VALUES (?)", student)

    if house not in houses:
      house_id = db.execute("INSERT INTO houses (name, head) VALUES (?, ?)", house, head)
      houses[house] = house_id
    else:
      house_id = houses[house]

    db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id, houses[house])


