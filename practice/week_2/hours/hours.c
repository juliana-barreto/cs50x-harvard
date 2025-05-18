// Program that tracks and calculates total/average study hours for CS50 course

#include <ctype.h>
#include <stdio.h>
#include <string.h>

float calc_hours(int hours[], int weeks, char output) {
    int sum = 0;
    for (int i = 0; i < weeks; i++) {
        sum += hours[i];
    }
    switch (output) {
        case 'T':
        case 't':
            return sum;
        case 'A':
        case 'a':
            return ((float)sum / weeks);
    }
}
int main( ) {
    int weeks;
    printf("Number of weeks taking CS50: ");
    scanf("%d", &weeks);
    int hours[weeks];
    for (int i = 0; i < weeks; i++) {
        printf("Week %i HW Hours: ", i);
        scanf("%d", &hours[i]);
    }
    char output;
    do {
        printf("Enter T for total hours, A for average hours per week: ");
        scanf("%c", &output);
    } while (output != 'T' && output != 'A');
    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}