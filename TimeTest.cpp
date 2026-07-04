#include "Time.h"
#include <iomanip>
#include <iostream>

std::ostream & operator<<(std::ostream & output, Time time);

int main()
{
    std::cout << "Test 1: Create default time.\n";
    Time time1;
    std::cout << "Time: " << time1;
    std::cout << "\n\n";

    std::cout << "Test 2: Create time with parameters.\n";
    Time time2(12, 40, 32);
    std::cout << "Time: " << time2;
    std::cout << "\n\n";

    std::cout << "Test 3: Set time\n";
    time1.SetHours(10);
    time1.SetMinutes(30);
    time1.SetSeconds(0);
    std::cout << "Time: " << time1;
    std::cout << "\n\n";
}

ostream & operator<<(std::ostream & output, Time time) {
    output << std::right << std::setfill('0');
    output << std::setw(2) << time.GetHours() << ':' << std::setw(2) << time.GetMinutes() << ':'
           << std::setw(2) << time.GetSeconds();
    output << std::setfill(' ') << std::left;
    return output;
}
