#include "DataLog.h"
#include <iomanip>
#include <iostream>

std::ostream & operator<<(std::ostream & output, Date date);
std::ostream & operator<<(std::ostream & output, Time time);
std::ostream & operator<<(std::ostream & output, DataRecord record);
std::ostream & operator<<(std::ostream & output, DataLog logs);

int main() {
    std::cout << "Test 1: Create a data log\n";
    DataLog logs;
    std::cout << logs;
    std::cout << '\n';

    std::cout << "Test 2: Add records.\n";
    logs.AddRecord({{5, 11, 2025}, {12, 40, 32}, 0.02, 14.4, 32.2});
    logs.AddRecord({{14, 6, 2024}, {15, 20, 00}, 0.04, 17.24, 27.4});
    logs.AddRecord({{16, 6, 2024}, {13, 12, 00}, 0.03, 7.36, 25.4});
    std::cout << logs;
    std::cout << '\n';

    std::cout << "Test 3: Extract a specific month\n";
    DataLog month_logs;
    logs.GetMonthData(month_logs, {0, 6, 2024});
    std::cout << month_logs;
    std::cout << '\n';

    std::cout << "Test 4: Extract month not contained in logs\n";
    logs.GetMonthData(month_logs, {0, 8, 2024});
    std::cout << month_logs;
    std::cout << '\n';

    std::cout << "Test 5: Edit first entry\n";
    logs[0].SetTemperature(33.2);
    std::cout << logs[0];
    std::cout << '\n';

    std::cout << "Test 6: Clear records\n";
    logs.Clear();
    std::cout << logs;
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

std::ostream & operator<<(std::ostream & output, DataLog logs) {
    output << std::right << std::setfill('0');
    if (logs.Size() == 0) {
        output << "No logs contained. Size: 0\n";
        return output;
    }
    Date date;

    output << "Size: " << logs.Size() << '\n';
    logs.GetMinMonth(date);
    output << "Minimum Month: " << setw(2) << date.GetMonth() << '/' << date.GetYear() << '\n';
    logs.GetMaxMonth(date);
    output << "Maximum Month: " << setw(2) << date.GetMonth() << '/' << date.GetYear() << '\n';

    for (int i{0}; i < logs.Size(); i++) {
        output << "--- Entry: " << i + 1 << " ---\n";
        output << logs[i];
        output << "----------------\n";
    }
    output << std::setfill(' ') << std::left;
    return output;
}
