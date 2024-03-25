#include <stdio.h>
#include <stdbool.h>

bool isLeapYear(int);

void addDaysToDate(int *, int *, int *, int);

int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Indexed by month number Jan. = 1, etc.

int main() {
    int year = 0;
    printf("Choose a year between 1800 and 10000 to check for a leap year: \n");
    scanf("%i", &year);
    bool leapYear = isLeapYear(year);
    if (leapYear) {
        printf("Leap Year\n");
    } else {
        printf("Not Leap Year\n");
    }

    int mm;
    int dd;
    int yy;
    int days_left_to_add;
    printf("\nPlease enter a date between the years 1800 and 10000 in the format 'mm dd yy' and provide the number of days to add to this date: \n");
    scanf("%i %i %i %i", &mm, &dd, &yy, &days_left_to_add);
    addDaysToDate(&mm, &dd, &yy, days_left_to_add);
    printf("%i %i %i\n", mm, dd, yy);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 || year % 400 ==
                                            0)); // A leap year has to be divisible by 4 and NOT divisible by 100 except when the year is divisible by 400.
}

void addDaysToDate(int *mm, int *dd, int *yy, int days_left_to_add) {
    int days_left_in_month;

    while (days_left_to_add > 0) {
        days_left_in_month = days_in_month[*mm] - *dd;

        if (*mm == 2 && isLeapYear(*yy)) {
            days_left_in_month++; // Adjust for February as needed
        }

        if (days_left_to_add > days_left_in_month) { // if more days left than can be added in a month
            days_left_to_add -= days_left_in_month + 1; // jump to the first day of the next month
            *dd = 1; // we are on the first day of the next month, but what is the next month?
            if (*mm == 12) { // if last month was December
                *mm = 1; // next month is January
                *yy = *yy + 1; // and we are in a new year so increase by 1
            } else *mm = *mm + 1; // if some other month, just increase by 1
        } else { // if all days can be added in this month
            *dd = *dd + days_left_to_add; // simply add the days
            days_left_to_add = 0; // no more days to add!
        }
    }
}