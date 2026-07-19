#include "CSVWrapper.h"
#include "DataRecord.h"
#include "DataRecordDatabase.h"
#include "Date.h"
#include "Vector.h"
#include "VectorDataOperations.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

void CSVToDatabase(CSVWrapper & csv_wrapper, std::string & file_name, DataRecordDatabase & database);
void InputHeaderNames(Vector<std::string> & header_names);
void fillDatabase(CSVWrapper & csv_wrapper, DataRecordDatabase & database);
bool stringToDate(const std::string & date_string, Date & date);
bool stringToTime(const std::string & time_string, Time & time);
void outputMonthWindSpeed(const DataRecordDatabase & database, Date selected_month);
void outputMonthlyAirTemp(const DataRecordDatabase & database, int selected_year);
void outputsPCCComparisons(const DataRecordDatabase & database, int selected_month);
void outputYearData(std::ostream & output, const DataRecordDatabase & database, int selected_year);
void DisplayMenu();
int NumInput(const std::string & prompt, int minimum, int maximum);
template <typename T, typename U>
void GetCorrelatableObjectData(const Vector<T> & items, Vector<U> & data_a, Vector<U> & data_b, U(T::*get_data_a)() const, U(T::*get_data_b)() const, U min_val);

enum MENU: int
{
    MENU_MIN = 1,
    MENU_WIND_SPEED = 1,
    MENU_AIR_TEMPERATURE = 2,
    MENU_SPCC = 3,
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
    // set up output
    std::cout << std::fixed << std::setprecision(1);
    std::ifstream data_source;
    data_source.open("data/data_source.txt");
    if (!data_source)
    {
        std::cout << "File 'data/data_source.txt' could not be opened.\n";
        return 1;
    }

    std::ifstream data_file;
    std::string file_name;
    DataRecordDatabase database{};
    Date month;

    CSVWrapper csv_wrapper{};

    while (getline(data_source, file_name, '\n'))
    {
        while (std::isspace(file_name[file_name.size() - 1]))
        {
            file_name = file_name.substr(0, file_name.size() - 1);
        }

        if (!csv_wrapper.Open("data/" + file_name))
        {
            std::cout << "File data/" << file_name << " could not be opened.\n";
            continue;
        }

        CSVToDatabase(csv_wrapper, file_name, database);
        csv_wrapper.Close();

        std::cout << "Total Records: " << database.Size() << "\n\n";
    }
    data_source.close();

    bool repeat{true};
    Date input_date;
    std::ofstream output;

    while (repeat)
    {
        DisplayMenu();
        switch (NumInput("Please enter an option from the menu (1-5): ", MENU_MIN, MENU_MAX))
        {
        case MENU_WIND_SPEED:
            input_date.SetYear(NumInput("Please enter a year (1-9999): ", 1, 9999));
            input_date.SetMonth(NumInput("Please enter a month (1-12): ", 1, 12));

            outputMonthWindSpeed(database, input_date);
            break;
        case MENU_AIR_TEMPERATURE:
            outputMonthlyAirTemp(database, NumInput("Please enter a year (1-9999): ", 1, 9999));
            break;
        case MENU_SPCC:
            outputsPCCComparisons(database, NumInput("Please enter a month (1-12): ", 1, 12));
            break;
        case MENU_YEAR_DATA:
            output.open("data/WindTempSolar.csv");
            if (!output)
            {
                std::cout << "Could not open output file \"data/WindTempSolar.csv\".";
                break;
            }
            outputYearData(output, database, NumInput("Please enter a year (1-9999): ", 1, 9999));
            output.close();
            std::cout << "Data exported into data/WindTempSolar.csv\n\n";
            break;
        case MENU_EXIT:
            repeat = false;
            break;
        default:
            std::cout << "Something is incredibly wrong.";
            break;
        }
    }

    std::cout << "Thank you for using the program. Goodbye.\n";

    return 0;
}

void DisplayMenu()
{
    std::cout << "------------------ Menu ------------------\n"
         << "1. Wind Speed Average for a single month.\n"
         << "2. Air Temperature Average for each month of a year.\n"
         << "3. Sample Pearson Correlation Coefficient of data\n"
         << "4. Output all data for a year into a file.\n"
         << "5. Exit.\n"
         << "------------------------------------------\n";
}

int NumInput(const std::string & prompt, int minimum, int maximum)
{
    int input{std::numeric_limits<int>::max()};

    do
    {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail() || (input < minimum || input > maximum))
        {
            std::cout << "Please input a number between " << minimum << " and " << maximum << " (inclusive).\n";
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (input < minimum || input > maximum);

    return input;
}

void CSVToDatabase(CSVWrapper & csv_wrapper, std::string & file_name, DataRecordDatabase & database)
{
    Vector<std::string> headers_to_extract{HEADERS_SIZE};
    std::cout << "Please enter the headers for file " << file_name << "\n\n";
    InputHeaderNames(headers_to_extract);

    csv_wrapper.ExtractByHeaders(headers_to_extract);

    fillDatabase(csv_wrapper, database);
}

void InputHeaderNames(Vector<std::string> & header_names)
{
    while (header_names.Size() < HEADERS_SIZE)
    {
        header_names.Insert(header_names.Size(), "");
    }

    std::cout << "Enter the header for Date & Time (Default: WAST): ";
    getline(std::cin, header_names[HEADERS_WAST]);
    if (header_names[HEADERS_WAST].empty())
    {
        header_names[HEADERS_WAST] = "WAST";
    }

    std::cout << "Enter the header for Solar Radiation (Default: SR): ";
    getline(std::cin, header_names[HEADERS_SOLAR_RADIATION]);
    if (header_names[HEADERS_SOLAR_RADIATION].empty())
    {
        header_names[HEADERS_SOLAR_RADIATION] = "SR";
    }

    std::cout << "Enter the header for Speed (Default: S): ";
    getline(std::cin, header_names[HEADERS_SPEED]);
    if (header_names[HEADERS_SPEED].empty())
    {
        header_names[HEADERS_SPEED] = "S";
    }

    std::cout << "Enter the header for Temperature (Default: T): ";
    getline(std::cin, header_names[HEADERS_TEMPERATURE]);
    if (header_names[HEADERS_TEMPERATURE].empty())
    {
        header_names[HEADERS_TEMPERATURE] = "T";
    }
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

void outputMonthWindSpeed(const DataRecordDatabase & database, Date selected_month)
{
    std::cout << MonthString(selected_month.GetMonth()) << ' ' << selected_month.GetYear() << ':';

    Vector<double> wind_speeds{};
    database.GetMonthSpeed(selected_month, wind_speeds);

    if (wind_speeds.Size() == 0) {
        std::cout << " No Data\n\n";
        return;
    }

    double mean = VectorDataOperations::CalcMean(wind_speeds);
    double sd = VectorDataOperations::CalcSD(wind_speeds);

    std::cout << "\nAverage speed: " << mean << " km/h"
              << "\nSample stdev: " << sd << "\n\n";
}

void outputMonthlyAirTemp(const DataRecordDatabase & database, int selected_year)
{
    std::cout << selected_year << '\n';

    Date month{};
    month.SetYear(selected_year);
    Vector<double> temperatures{};

    for (int i{1}; i <= 12; i++)
    {
        std::cout << MonthString(i) << ": ";
        month.SetMonth(i);
        database.GetMonthTemperature(month, temperatures);

        if (temperatures.Size() == 0)
        {
            std::cout << "No Data\n";
            continue;
        }

        double mean = VectorDataOperations::CalcMean(temperatures);
        double sd = VectorDataOperations::CalcSD(temperatures);
        std::cout << "average: " << mean << " degrees C"
                  << ", stdev: " << sd << '\n';
        temperatures.Clear();
    }
}


void outputsPCCComparisons(const DataRecordDatabase & database, int selected_month) {

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Sample Pearson Correlation Coefficient for " << MonthString(selected_month) << '\n';
    Vector<int> years;
    Vector<DataRecord> month_data;
    database.GetYears(years);
    for (int i{0}; i < years.Size(); i++) {
        database.GetMonthRecords({0, selected_month, years[i]}, month_data);
    }

    Vector<double> data_a{};
    Vector<double> data_b{};

    if (month_data.Size() == 0) {
        std::cout << "No data for this month.\n\n";
        return;
    }

    VectorDataOperations::GetCorrelatableObjectData(month_data, data_a, data_b, &DataRecord::GetSpeed, &DataRecord::GetTemperature, DataRecord::MIN_VAL);

    std::cout << "S_T: ";
    if (data_a.Size() == 0) {
        std::cout << "No correlative data.\n";
    } else {
        std::cout << VectorDataOperations::CalcsPCC(data_a, data_b) << '\n';
        data_a.Clear();
        data_b.Clear();
    }

    VectorDataOperations::GetCorrelatableObjectData(month_data, data_a, data_b, &DataRecord::GetSpeed, &DataRecord::GetSolarRadiation, DataRecord::MIN_VAL);

    std::cout << "S_R: ";
    if (data_a.Size() == 0) {
        std::cout << "No correlative data.\n";
    } else {
        std::cout << VectorDataOperations::CalcsPCC(data_a, data_b) << '\n';
        data_a.Clear();
        data_b.Clear();
    }

    VectorDataOperations::GetCorrelatableObjectData(month_data, data_a, data_b, &DataRecord::GetTemperature, &DataRecord::GetSolarRadiation, DataRecord::MIN_VAL);

    std::cout << "T_R: ";
    if (data_a.Size() == 0) {
        std::cout << "No correlative data.\n";
    } else {
        std::cout << VectorDataOperations::CalcsPCC(data_a, data_b) << '\n';
        data_a.Clear();
        data_b.Clear();
    }

    std::cout << std::fixed << std::setprecision(1);
}

void outputYearData(std::ostream & output, const DataRecordDatabase & database, int selected_year)
{
    output << std::fixed << std::setprecision(1);
    output << selected_year << '\n';
    if (!database.HasYear(selected_year)) {
        output << "No Data";
        return;
    }

    Date month{0,0,selected_year};

    Vector<double> solar_radiation{};
    Vector<double> wind_speeds{};
    Vector<double> temperatures{};

    for (int i{0}; i < 12; i++)
    {
        month.SetMonth(i + 1);
        database.GetMonthSolarRadiation(month, solar_radiation);
        database.GetMonthSpeed(month, wind_speeds);
        database.GetMonthTemperature(month, temperatures);

        // skip empty months
        if (!(solar_radiation.Size() || wind_speeds.Size() || temperatures.Size()))
        {
            continue;
        }

        output << MonthString(i + 1) << ",";

        double mean{};
        double sd{};
        if (wind_speeds.Size()) {
            mean = VectorDataOperations::CalcMean(wind_speeds);
            sd = VectorDataOperations::CalcSD(wind_speeds);
            output << mean << '(' << sd << "),";
            wind_speeds.Clear();
        } else {
            output << " ,";
        }

        if (temperatures.Size()) {
            mean = VectorDataOperations::CalcMean(temperatures);
            sd = VectorDataOperations::CalcSD(temperatures);
            output << mean << '(' << sd << "),";
            temperatures.Clear();
        } else {
            output << " ,";
        }

        if (solar_radiation.Size()) {
            output << VectorDataOperations::CalcTotal(solar_radiation) << '\n';
            solar_radiation.Clear();
        } else {
            output << " \n";
        }
    }
}
