#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void mainMenu();

bool isLeapYear(long);

void addDaysToDate(long, long, long, long);

void checkLeapYear();

void calculateDifferenceInDays();

long days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Indexed by month number Jan. = 1, etc.

int main() {
    mainMenu();
}

void mainMenu() {
    char menuEntry[3];
    char *menuPtr;
    long menuChoice;

    do {
        printf("\n\nThis small demo app will allow you to:\n");
        printf("\t1. Determine if a particular year is/was a leap year.\n");
        printf("\t2. Calculate the number of days between today and a date of your choice.\n");
        printf("\t0. Exit");
        printf("\nMake your selection: ");
        scanf("%2s", menuEntry);
        menuChoice = strtol(menuEntry, &menuPtr, 10);

        switch (menuChoice) {
            case 1:
                checkLeapYear();
                continue;
            case 2:
                calculateDifferenceInDays();
                continue;
            case 0:
                break;
            default:
                printf("You've entered an invalid choice.");
        }
    } while (menuChoice != 0);
    exit(0);
}

void checkLeapYear() {
    char yearToCheck[6];
    char *yearPtr;
    long year;

    printf("Choose a year between 1582 and 99999 to check for a leap year: \n");
    scanf("%5s", yearToCheck);
    year = strtol(yearToCheck, &yearPtr, 10);
    bool leapYear = isLeapYear(year);
    if (leapYear) {
        printf("Leap Year\n");
    } else {
        printf("Not Leap Year\n");
    }
}

bool isLeapYear(long year) {
    // A leap year has to be divisible by 4 and NOT divisible by 100 except when the year is divisible by 400.
    return (year % 4 == 0 && (year % 100 || year % 400 == 0));
}

void calculateDifferenceInDays() {
    char monthToCalculate[3];
    char dayToCalculate[3];
    char yearToCalculate[3];
    char daysToAdd[5];
    char *monthToCalculatePtr;
    char *dayToCalculatePtr;
    char *yearToCalculatePtr;
    char *daysToAddPtr;
    long mm;
    long dd;
    long yy;
    long days_left_to_add;

    printf("\nPlease enter a date between the years 2000 and 2099 in the format 'mm dd yy' and provide the number of days (0 - 9999) to add to this date: \n");
    scanf("%2s %2s %2s %4s", monthToCalculate, dayToCalculate, yearToCalculate, daysToAdd);
    mm = strtol(monthToCalculate, &monthToCalculatePtr, 10);
    dd = strtol(dayToCalculate, &dayToCalculatePtr, 10);
    yy = strtol(yearToCalculate, &yearToCalculatePtr, 10);
    days_left_to_add = strtol(daysToAdd, &daysToAddPtr, 10);

    addDaysToDate(mm, dd, yy, days_left_to_add);
    printf("%li %li %li\n", mm, dd, yy);
}

void addDaysToDate(long mm, long dd, long yy, long days_left_to_add) {
    long days_left_in_month;
    int monthIndex;
    if (mm > 0 && mm < 13) {
        monthIndex = (int) mm;
    } else {
        monthIndex = 0;
    }

    while (days_left_to_add > 0) {
        days_left_in_month = days_in_month[monthIndex] - dd;

        if (mm == 2 && isLeapYear(yy)) {
            days_left_in_month++; // Adjust for February as needed
        }
        if (days_left_to_add > days_left_in_month) { // if more days left than can be added in a month
            days_left_to_add -= days_left_in_month + 1; // jump to the first day of the next month
            dd = 1; // we are on the first day of the next month, but what is the next month?
            if (mm == 12) { // if last month was December
                mm = 1; // next month is January
                yy = yy + 1; // and we are in a new year so increase by 1
            } else mm = mm + 1; // if some other month, just increase by 1
        } else { // if all days can be added in this month
            dd = dd + days_left_to_add; // simply add the days
            days_left_to_add = 0; // no more days to add!
        }
    }
}