#include "CSVWrapper.h"
#include "DataRecord.h"
#include "Date.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "DataRecordDatabase.h"

void CSVToDatabase(CSVWrapper & csv_wrapper, DataRecordDatabase & database);
void InputHeaderNames(Vector<std::string> & header_names);
void fillDatabase(CSVWrapper & csv_wrapper, DataRecordDatabase & database);
bool stringToDate(const std::string & date_string, Date & date);
bool stringToTime(const std::string & time_string, Time & time);
std::ostream & operator<<(std::ostream & output, const DataRecord & data_record);

enum MENU: int
{
    MENU_MIN = 1,
    MENU_WIND_SPEED = 1,
    MENU_AIR_TEMPERATURE = 2,
    MENU_SOLAR_RADIATION = 3,
    MENU_YEAR_DATA = 4,
    MENU_EXIT = 5,
    MENU_MAX = 5
};

enum HEADERS: int
{
    HEADERS_WAST = 0, // Western Australia Standard Time
    HEADERS_SOLAR_RADIATION = 1,
    HEADERS_SPEED = 2,
    HEADERS_TEMPERATURE = 3,
    HEADERS_SIZE = 4
};

int main()
{
    std::cout << std::setprecision(2) << std::fixed;
    std::string file_name{"TestData.csv"};
    DataRecordDatabase database{};
    CSVWrapper csv{};

    std::cout << "Test 1: Loading data\n";

    if (!csv.Open("data/TestData.csv")) {
        std::cout << "File could not be opened.\n";
        return -1;
    }

    CSVToDatabase(csv, database);

    std::cout << "Database Size: " << database.Size() << "\n\n";
    Vector<double> values;

    std::cout << "Test 2: Extracting data (wind speed) for March 2015\n";
    std::cout << ((database.GetMonthSpeed({0, 3, 2015}, values)) ? "Successfully Extracted" : "Extraction Failed") << '\n';
    std::cout << "Size: " << values.Size() << "\n\n";

    std::cout << "Sample Values:\n";
    for (int i{0}; i < values.Size(); i++)
    {
        std::cout << values[i];
        if (i != values.Size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n\n";
    values.Clear();

    std::cout << "Test 3: Extracting data (solar radiation) for March 2015, skipping invalid input values\n";
    std::cout << ((database.GetMonthSolarRadiation({0, 3, 2015}, values)) ? "Successfully Extracted" : "Extraction Failed") << '\n';
    std::cout << "Size: " << values.Size() << "\n\n";

    std::cout << "Sample Values:\n";
    for (int i{0}; i < values.Size(); i++)
    {
        std::cout << values[i];
        if (i != values.Size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n\n";
    values.Clear();

    std::cout << "Test 4: Extracting data (temperature) for March 2015.\n";
    std::cout << ((database.GetMonthTemperature({0, 3, 2015}, values)) ? "Successfully Extracted" : "Extraction Failed") << '\n';
    std::cout << "Size: " << values.Size() << "\n\n";

    std::cout << "Values:\n";
    for (int i{0}; i < values.Size(); i++)
    {
        std::cout << values[i];
        if (i != values.Size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n\n";
    values.Clear();

    std::cout << "Test 5: Extract non-existent month data (solar radiation) for for March 3002\n";
    std::cout << ((database.GetMonthSolarRadiation({0, 4, 3002}, values)) ? "Successfully Extracted" : "Extraction Failed") << "\n\n";

    std::cout << "Test 6: Extract Records for March 2015\n";
    Vector<DataRecord> records;
    std::cout << ((database.GetMonthRecords({0, 3, 2015}, records)) ? "Successfully Extracted" : "Extraction Failed") << '\n';
    std::cout << "Size: " << records.Size() << "\n\n";
    std::cout << "Sample:\n";
    for (int i{0}; i < records.Size(); i ++)
    {
        std::cout << records[i] << '\n';
    }
    std::cout << '\n';

    return 0;
}


void CSVToDatabase(CSVWrapper & csv_wrapper, DataRecordDatabase & database)
{
    Vector<std::string> headers_to_extract{HEADERS_SIZE};
    headers_to_extract[HEADERS_WAST] = "WAST";
    headers_to_extract[HEADERS_TEMPERATURE] = "T";
    headers_to_extract[HEADERS_SPEED] = "S";
    headers_to_extract[HEADERS_SOLAR_RADIATION] = "SR";

    csv_wrapper.ExtractByHeaders(headers_to_extract);

    fillDatabase(csv_wrapper, database);
}

void fillDatabase(CSVWrapper & csv_wrapper, DataRecordDatabase & database)
{
    Vector<std::string> input_vector;
    DataRecord data_record;
    Date date;
    Time time;
    while (csv_wrapper.GetLine(input_vector))
    {
        // Date & Time input
        if (stringToDate(input_vector[HEADERS_WAST].substr(0, input_vector[HEADERS_WAST].find(' ')), date) &&
                stringToTime(input_vector[HEADERS_WAST].substr(input_vector[HEADERS_WAST].find(' ') + 1), time))
        {
            data_record.SetDate(date);
            data_record.SetTime(time);
        }
        else
        {
            continue; // invalid data means entry should be skipped as it cannot be placed
        }

        // convert units and enter
        // if conversions fail, enter number less than the minimum value.
        try
        {
            double solar_radiation = stod(input_vector[HEADERS_SOLAR_RADIATION]);
            if (solar_radiation < 100)   // skip values less than 100 W/m^2
            {
                data_record.SetSolarRadiation(DataRecord::MIN_VAL - 1);
            }
            else
            {
                data_record.SetSolarRadiation(solar_radiation / 6000); // W/m^2 to kWh/m^2
            }
        }
        catch (std::exception & e)
        {
            data_record.SetSolarRadiation(DataRecord::MIN_VAL - 1);
        }

        try
        {
            data_record.SetSpeed(stod(input_vector[HEADERS_SPEED]) * 3.6); // m/s to km/h
        }
        catch (std::exception & e)
        {
            data_record.SetSpeed(DataRecord::MIN_VAL - 1);
        }

        try
        {
            data_record.SetTemperature(stod(input_vector[HEADERS_TEMPERATURE]));
        }
        catch (std::exception & e)
        {
            data_record.SetTemperature(DataRecord::MIN_VAL - 1);
        }

        database.Insert(data_record);
    }
}

bool stringToDate(const std::string & date_string, Date & date)
{
    unsigned long div1 = date_string.find('/');
    unsigned long div2 = date_string.find('/', div1 + 1);

    if (div1 == std::string::npos || div2 == std::string::npos)
    {
        return false;
    }

    try
    {
        date.SetDay(stoi(date_string.substr(0, div1)));
        date.SetMonth(stoi(date_string.substr(div1 + 1, div2)));
        date.SetYear(stoi(date_string.substr(div2 + 1)));
    }
    catch (const std::exception & e)
    {
        return false;
    }
    return true;
}

bool stringToTime(const std::string & time_string, Time & time)
{
    unsigned long div = time_string.find(':');

    if (div == std::string::npos)
    {
        return false;
    }

    try
    {
        time.SetHours(stoi(time_string.substr(0, div)));
        time.SetMinutes(stoi(time_string.substr(div + 1)));
    }
    catch (const std::exception & e)
    {
        return false;
    }
    return true;
}

std::ostream & operator<<(std::ostream & output, const DataRecord & data_record)
{
    Date date{};
    data_record.GetDate(date);
    Time time{};
    data_record.GetTime(time);
    std::cout << std::setfill('0') << std::fixed << std::setprecision(2);
    std::cout << date.GetDay() << '/' << std::setw(2) << date.GetMonth() << '/' << date.GetYear() << ' ' << std::setw(2) << time.GetHours() << ':' << std::setw(2) << time.GetMinutes() << " - "
              << data_record.GetSolarRadiation() << ", " << data_record.GetSpeed() << ", " << data_record.GetTemperature();
    return output;
}
