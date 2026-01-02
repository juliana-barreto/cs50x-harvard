import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    # Initialize dictionaries for tracking cases
    new_cases = {}
    previous_cases = {}
    # Iterate over each dictionary in the CSV reader
    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        # If state not in previous_cases, add it
        if state not in previous_cases:
            previous_cases[state] = cases
            new_cases[state] = []
            new_cases[state].append(cases)
        # Else, calculate new cases and update dictionaries
        else:
            new_count_cases = cases - previous_cases[state]
            new_cases[state].append(new_count_cases)
            # Keep only the most recent 14 days
            if len(new_cases[state]) > 14:
                new_cases[state].pop(0)
            previous_cases[state] = cases
    return new_cases

# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        # Calculate last week and current week averages
        last_week_avg = sum(new_cases[state][:7]) / 7
        current_week_avg = sum(new_cases[state][-7:]) / 7
        # Calculate percent change and print it out
        try:
            percentage = round(((current_week_avg - last_week_avg) / last_week_avg) * 100, 2)   
        except ZeroDivisionError:
            percentage = 0
        # Print out the averages
        print(f"{state} had a 7-day average of {current_week_avg:.2f}", end=" ")
        # Print out the percentage change
        if percentage > 0:
            print(f"and an increase of {percentage}%.")
        elif percentage < 0:
            percentage = abs(percentage)
            print(f"and a decrease of {percentage}%.")
        else :
            print("and there was no change.")

main()