import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = int(request.form.get("month"))
        day = int(request.form.get("day"))

        if not name or name == "":
            flash("Name cannot be empty")
            return render_template("failure.html", message="Missing name")

        if not month or month < 1 or month > 12:
            flash("Month must be between 1 and 12")
            return render_template("failure.html", message="Invalid month")
        
        if not day or day < 1 or day > 31:
            flash("Day must be between 1 and 31")
            return render_template("failure.html", message="Invalid day")
        
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)


