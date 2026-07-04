#include "DataRecord.h"
#include <iostream>
#include <iomanip>

std::ostream & operator<<(std::ostream & output, Date date);
std::ostream & operator<<(std::ostream & output, Time time);
std::ostream & operator<<(std::ostream & output, DataRecord record);

int main() {
    std::cout << "Test 1: Default construction\n";
    DataRecord record1;
    std::cout << record1 << '\n';

    std::cout << "Test 2: Parameterized construction\n";
    DataRecord record2({5, 11, 2025}, {12, 40, 32}, 0.02, 14.4, 32.2);
    std::cout << record2 << '\n';

    std::cout << "Test 3: Setting values\n";
    record1.SetDate({14, 6, 2024});
    record1.SetTime({15, 20, 00});
    record1.SetSolarRadiation(0.04);
    record1.SetSpeed(17.24);
    record1.SetTemperature(27.4);
    std::cout << record1 << '\n';
}

std::ostream & operator<<(std::ostream & output, Date date) {
    output << std::right << std::setfill('0');
    output << std::setw(2) << date.GetDay() << '/' << std::setw(2) << date.GetMonth() << '/'
         << std::setw(2) << date.GetYear();
    output << std::setfill(' ') << std::left;
    return output;
}

std::ostream & operator<<(std::ostream & output, Time time) {
    output << std::right << std::setfill('0');
    output << std::setw(2) << time.GetHours() << ':' << std::setw(2) << time.GetMinutes() << ':'
           << std::setw(2) << time.GetSeconds();
    output << std::setfill(' ') << std::left;
    return output;
}


std::ostream & operator<<(std::ostream & output, DataRecord record) {
    Date date;
    Time time;
    record.GetDate(date);
    record.GetTime(time);
    output << "Date: " << date << '\n'
           << "Time: " << time << '\n'
           << "Solar Radiation (kWh/m\u00B2): " << record.GetSolarRadiation() << '\n'
           << "Wind Speed (km/h): " << record.GetSpeed() << '\n'
           << "Temperature (C): " << record.GetTemperature() << '\n';
    return output;
}
