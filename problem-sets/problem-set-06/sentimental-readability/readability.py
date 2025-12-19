import re

text = input("Text: ")

## Count letters, words, and sentences
letters = sum(1 for char in text if char.isalpha())
words = len(text.split())
sentences = len(re.split(r"[!?.]+", text)) - 1

## Calculate the Coleman-Liau index
L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

## Print the grade level
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
