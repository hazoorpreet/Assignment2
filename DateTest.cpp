#include "Date.h"
#include <iomanip>
#include <iostream>

std::ostream & operator<<(std::ostream & output, Date date);

int main()
{
    std::cout << "Test 1: Create default date.\n";
    Date date1;
    std::cout << "Date: " << date1;
    std::cout << "\n\n";

    std::cout << "Test 2: Create date with parameters.\n";
    Date date2(30, 11, 2025);
    std::cout << "Date: " << date2;
    std::cout << "\n\n";

    std::cout << "Test 3: Set date\n";
    date1.SetDay(14);
    date1.SetMonth(6);
    date1.SetYear(2023);
    std::cout << "Date: " << date1;
    std::cout << "\n\n";

    std::cout << "Test 4: Output date with month in string form.\n";
    std::cout << date1.GetDay() << ' ' << MonthString(date1.GetMonth()) << ' ' << date1.GetYear();
    std::cout << "\n\n";
}

std::ostream & operator<<(std::ostream & output, Date date) {
    output << std::right << std::setfill('0');
    output << std::setw(2) << date.GetDay() << '/' << std::setw(2) << date.GetMonth() << '/'
         << std::setw(2) << date.GetYear();
    output << std::setfill(' ') << std::left;
    return output;
}
