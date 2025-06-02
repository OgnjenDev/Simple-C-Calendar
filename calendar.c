#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month-1];
}

int getFirstWeekday(int month, int year) {
    struct tm time_in = {0,0,0,1,month-1,year-1900};
    mktime(&time_in);
    return time_in.tm_wday;
}

void printTitle(int month, int year) {
    const char *months[] = {"January","February","March","April","May","June",
                            "July","August","September","October","November","December"};
    printf("\n     %s %d\n", months[month-1], year);
    printf("Su Mo Tu We Th Fr Sa\n");
}

void printCalendar(int month, int year) {
    printTitle(month, year);

    int firstDay = getFirstWeekday(month, year);
    int totalDays = daysInMonth(month, year);

    for (int i = 0; i < firstDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= totalDays; day++) {
        printf("%2d ", day);
        if ((firstDay + day) % 7 == 0) printf("\n");
    }
    printf("\n");
}

void adjustMonthYear(int *month, int *year, int delta) {
    *month += delta;
    if (*month > 12) {
        *month = 1;
        (*year)++;
    } else if (*month < 1) {
        *month = 12;
        (*year)--;
    }
}

int main(int argc, char *argv[]) {
    int month, year;

    if (argc == 1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        month = t->tm_mon + 1;
        year = t->tm_year + 1900;
    } else if (argc == 3) {
        sscanf(argv[1], "%d", &month);
        sscanf(argv[2], "%d", &year);
        if (month < 1 || month > 12) {
            printf("Invalid month.\n");
            return 1;
        }
    } else {
        printf("Usage: %s [month year]\n", argv[0]);
        return 1;
    }

    char command;

    while (1) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        printCalendar(month, year);

        printf("\nEnter 'n' for next month, 'p' for previous month, 'q' to quit: ");
        command = getchar();

        // Clear input buffer (remove extra characters like newline)
        while (getchar() != '\n');

        if (command == 'n') {
            adjustMonthYear(&month, &year, 1);
        } else if (command == 'p') {
            adjustMonthYear(&month, &year, -1);
        } else if (command == 'q') {
            break;
        }
    }

    return 0;
}
