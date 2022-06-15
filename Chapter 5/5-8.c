#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    printf("day_of_year: %d\t%d\t%d\t= %d day of the year.\n", 1999, 3, 1, day_of_year(1999, 3, 1));    // OK
    printf("day_of_year: %d\t%d\t%d\t= %d day of the year.\n", 1999, 0, 1, day_of_year(1999, 0, 1));    // NOT OK

    int month, day;
    month_day(1999, 60, &month, &day);
    printf("month_day: %d\t%d\t= month %d day %d.\n", 1999, 60, month, day);    // OK
    month_day(1999, 366, &month, &day);
    printf("month_day: %d\t%d\t= month %d day %d.\n", 1999, 366, month, day);    // NOT OK
    month_day(2024, 366, &month, &day);
    printf("month_day: %d\t%d\t= month %d day %d.\n", 2024, 366, month, day);    // OK
    month_day(1999, -3, &month, &day);
    printf("month_day: %d\t%d\t= month %d day %d.\n", 1999, -1, month, day);    // NOT OK

    return 0;
}

static char daytab[2][13] = {
    {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0,31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day.
                return -1 if input is invalid. */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month < 1 || month > 12 || day < 1 || day > daytab[leap][day])
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    
    return day;
}

/* month_day:   set mont, day from day of year.
                set both pmonth and pday to -1 if the input is invalid. */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if (yearday < 0 || (leap && yearday > 366) || (!leap && yearday > 365)){
        *pmonth = -1;
        *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    
    *pmonth = i;
    *pday = yearday;
}