from datetime import datetime
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    ## Get user's cash balance
    cash_rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    user_cash = cash_rows[0]["cash"]

    ## Get user's portfolio
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)

    portfolio = []
    grand_total = user_cash

    ## For each stock, get current price and calculate total value
    for stock in stocks:
        quote = lookup(stock["symbol"])
        total_value = quote["price"] * stock["total_shares"]
        grand_total += total_value
        portfolio.append({
            "symbol": stock["symbol"],
            "name": quote["name"],
            "shares": stock["total_shares"],
            "price": quote["price"],
            "total": total_value
        })

    return render_template("index.html", portfolio=portfolio, cash=user_cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or symbol == "":
            return apology("must provide symbol", 400)
        
        ## Search for stock quote
        stock = lookup(symbol)

        if stock is None:
            return apology("invalid  symbol", 400)

        ## Validate shares input
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("must provide a valid number of shares", 400)
        except ValueError:
            return apology("must provide a valid number of shares", 400)
                
        ## Calculate total cost
        price = stock["price"]
        total_cost = shares * price
        user_id = session["user_id"]

        ## Check user's cash balance
        user_cash_rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_rows[0]["cash"]

        if user_cash < total_cost:
            return apology("insufficient funds", 400)
        
        try:
            ## Realize transaction
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], datetime.now())
        
        except ValueError:
            return apology("transaction failed", 400)
        
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    ## Get user's transactions
    transactions = db.execute("SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ? ORDER BY transacted DESC", user_id)

    return render_template("history.html", transactions=transactions)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        
        symbol = request.form.get("symbol")
        if not symbol or symbol == "":
            return apology("must provide symbol", 400)
        
        ## Search for stock quote
        item = lookup(symbol)
        if item is None:
            return apology("invalid symbol", 400)
        
        ## Redirect to quoted.html
        return render_template("quoted.html", quote=item)
    
    else:
        return render_template("quote.html")
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        ## Validate submission
        if not username or username == "":
            return apology("must provide username", 400)
        
        if not password or password == "":
            return apology("must provide password", 400)
        
        if confirmation != password:
            return apology("passwords do not match", 400)  
        
        ## Generate password hash
        hash = generate_password_hash(password)

        try:
            ## Insert into database
            new_user_id = db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash
            )
        except ValueError:
            ## Catch duplicate username error
            return apology("username already exists", 400)

        ## Log in newly registered user
        session["user_id"] = new_user_id
        ## Redirect to home page
        return redirect("/")

    else:
        return render_template("register.html")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or symbol == "":
            return apology("must provide symbol", 400)
        
        ## Validate shares input
        try:
            shares = int(shares)
            if shares < 1:
                return apology("must provide a positive number of shares", 400)
        except ValueError:
            return apology("must provide a positive number of shares", 400)
        
        stock = lookup(symbol)
        if not stock:
            return apology("invalid  symbol", 400)
        
        ## Check if user owns enough shares
                
        owned_shares_rows = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)

        if not owned_shares_rows or owned_shares_rows[0]["total_shares"] < shares:
                return apology("insufficient shares", 400)
        
        price = stock["price"]
        total_revenue = price * shares

        ## Realize transaction
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_revenue, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",
            user_id, stock["symbol"], -shares, price, datetime.now()
        )

        ## Redirect to home page
        return redirect("/")
        
    else:
        ## Search only for symbols the user owns
        user_symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)

        return render_template("sell.html", symbols=user_symbols)
    
@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add additional cash to user account"""
    if request.method == "POST":
        try:
            amount = int(request.form.get("amount"))
        except ValueError:
            return apology("amount must be an integer", 400)

        if amount < 0:
            return apology("amount must be a positive integer", 400)

        user_id = session["user_id"]
        
        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)

        return redirect("/")

    else:
        return render_template("add_cash.html")