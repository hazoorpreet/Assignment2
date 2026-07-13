#include "Date.h"
#include "Vector.h"
#include "DataRecord.h"
#include "DataLog.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "CSVWrapper.h"

void CSVToDataLog(CSVWrapper & csv_wrapper, std::string & file_name, DataLog & data_log);
void InputHeaderNames(Vector<std::string> & header_names);
double CalcTotalSolarRadiation(const DataLog & data_log);
double CalcMeanSpeed(const DataLog & data_log);
double CalcSDSpeed(const DataLog & data_log);
double CalcMeanTemperature(const DataLog & data_log);
double CalcSDTemperature(const DataLog & data_log);
void fillDataLog(CSVWrapper & csv_wrapper, DataLog & data_log);
bool stringToDate(const std::string & date_string, Date & date);
bool stringToTime(const std::string & time_string, Time & time);
void getMonthlyLogs(const DataLog & data_log, Vector<DataLog> & monthly_logs);
void extractYear(const Vector<DataLog> & monthly_logs, Vector<const DataLog *> & months, int selected_year);
void outputMonthWindSpeed(const Vector<DataLog> & monthly_logs, Date selected_month);
void outputMonthlyAirTemp(const Vector<DataLog> & monthly_logs, int selected_year);
void outputMonthlySolarRad(const Vector<DataLog> & monthly_logs, int selected_year);
void outputYearData(std::ostream & output, const Vector<DataLog> & monthly_logs, int selected_year);
void DisplayMenu();
int NumInput(const std::string & prompt, int minimum, int maximum);

const double DATA_EMPTY = -100; // unreasonably low value to indicate empty

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
    std::ifstream data_source;
    data_source.open("data/data_source.txt");
    if (!data_source)
    {
        std::cout << "File 'data/data_source.txt' could not be opened.\n";
        return 1;
    }

    std::ifstream data_file;
    std::string file_name;
    DataLog data_log{};
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

        std::cout << "Beginning to load data from file, please wait...\n";
        CSVToDataLog(csv_wrapper, file_name, data_log);
        csv_wrapper.Close();
        // Algorithm ends here

        // Additional Helpful information for usage of program
        std::cout << "Data Loaded:\n";
        std::cout << "Total Records: " << data_log.Size() << '\n';
        if (data_log.Size() > 0)
        {
            data_log.GetMinMonth(month);
            std::cout << "Min Month: " << MonthString(month.GetMonth()) << ' ' << month.GetYear() << '\n';
            data_log.GetMaxMonth(month);
            std::cout << "Max Month: " << MonthString(month.GetMonth()) << ' ' << month.GetYear() << '\n';
            std::cout << "\n\n";
        }
    }
    data_source.close();

    Vector<DataLog> monthly_logs;
    getMonthlyLogs(data_log, monthly_logs);
    data_log.Clear();

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

            outputMonthWindSpeed(monthly_logs, input_date);
            break;
        case MENU_AIR_TEMPERATURE:
            outputMonthlyAirTemp(monthly_logs, NumInput("Please enter a year (1-9999): ", 1, 9999));
            break;
        case MENU_SOLAR_RADIATION:
            outputMonthlySolarRad(monthly_logs, NumInput("Please enter a year (1-9999): ", 1, 9999));
            break;
        case MENU_YEAR_DATA:
            output.open("data/WindTempSolar.csv");
            if (!output)
            {
                std::cout << "Could not open output file \"data/WindTempSolar.csv\".";
                break;
            }
            outputYearData(output, monthly_logs, NumInput("Please enter a year (1-9999): ", 1, 9999));
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
         << "3. Total Solar Radiation for each month of a year.\n"
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

void CSVToDataLog(CSVWrapper & csv_wrapper, std::string & file_name, DataLog & data_log)
{
    Vector<std::string> headers_to_extract{HEADERS_SIZE};
    std::cout << "Please enter the headers for file " << file_name << "\n\n";
    InputHeaderNames(headers_to_extract);

    csv_wrapper.ExtractByHeaders(headers_to_extract);

    fillDataLog(csv_wrapper, data_log);
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

void fillDataLog(CSVWrapper & csv_wrapper, DataLog & data_log)
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

        data_log.AddRecord(data_record);
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
    catch (std::exception & e)
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
    catch (std::exception & e)
    {
        return false;
    }
    return true;
}

double CalcTotalSolarRadiation(const DataLog & data_log)
{
    double total = 0;
    int sensor_errs = 0;
    for (int i = 0; i < data_log.Size(); i++)
    {
        if (data_log[i].GetSolarRadiation() < DataRecord::MIN_VAL)
        {
            sensor_errs++;
        }
        else
        {
            total += data_log[i].GetSolarRadiation();
        }
    }

    if ((data_log.Size() - sensor_errs) == 0)
    {
        return DATA_EMPTY;
    }

    return total;
}

double CalcMeanSpeed(const DataLog & data_log)
{
    double total = 0;
    int sensor_errs = 0;
    for (int i = 0; i < data_log.Size(); i++)
    {
        if (data_log[i].GetSpeed() < DataRecord::MIN_VAL)
        {
            sensor_errs++;
        }
        else
        {
            total += data_log[i].GetSpeed();
        }
    }

    if ((data_log.Size() - sensor_errs) == 0)
    {
        return DATA_EMPTY;
    }
    return total / (data_log.Size() - sensor_errs);
}

double CalcSDSpeed(const DataLog & data_log)
{
    double mean = CalcMeanSpeed(data_log);

    double processed_sum = 0;
    int sensor_errs = 0;
    for (int i = 0; i < data_log.Size(); i++)
    {
        if (data_log[i].GetSpeed() < DataRecord::MIN_VAL)
        {
            sensor_errs++;
        }
        else
        {
            processed_sum += (data_log[i].GetSpeed() - mean) * (data_log[i].GetSpeed() - mean);
        }
    }

    if ((data_log.Size() - sensor_errs) == 0)
    {
        return DATA_EMPTY;
    }
    return sqrt(processed_sum / ((data_log.Size() - sensor_errs) - 1));
}

double CalcMeanTemperature(const DataLog & data_log)
{
    double total = 0;
    int sensor_errs = 0;
    for (int i = 0; i < data_log.Size(); i++)
    {
        if (data_log[i].GetTemperature() < DataRecord::MIN_VAL)
        {
            sensor_errs++;
        }
        else
        {
            total += data_log[i].GetTemperature();
        }
    }

    if ((data_log.Size() - sensor_errs) == 0)
    {
        return DATA_EMPTY;
    }

    return total / (data_log.Size() - sensor_errs);
}

double CalcSDTemperature(const DataLog & data_log)
{
    double mean = CalcMeanTemperature(data_log);

    double processed_sum = 0;
    int sensor_errs = 0;
    for (int i = 0; i < data_log.Size(); i++)
    {
        if (data_log[i].GetTemperature() < DataRecord::MIN_VAL)
        {
            sensor_errs++;
        }
        else
        {
            processed_sum += (data_log[i].GetTemperature() - mean) * (data_log[i].GetTemperature() - mean);
        }
    }

    if ((data_log.Size() - sensor_errs) == 0)
    {
        return DATA_EMPTY;
    }
    return sqrt(processed_sum / ((data_log.Size() - sensor_errs) - 1));
}

void getMonthlyLogs(const DataLog & data_log, Vector<DataLog> & monthly_logs)
{
    Date min_month;
    Date max_month;
    data_log.GetMinMonth(min_month);
    data_log.GetMaxMonth(max_month);

    Date ret_month = min_month;
    DataLog month_log;
    while ((ret_month.GetMonth() <= max_month.GetMonth()) || (ret_month.GetYear() < max_month.GetYear()))
    {
        data_log.GetMonthData(month_log, ret_month);
        if (month_log.Size() > 0)
        {
            monthly_logs.Insert(monthly_logs.Size(), month_log);
        }

        if (ret_month.GetMonth() < 12)
        {
            ret_month.SetMonth(ret_month.GetMonth() + 1);
        }
        else
        {
            ret_month.SetMonth(1);
            ret_month.SetYear(ret_month.GetYear() + 1);
        }
    }
}

void extractYear(const Vector<DataLog> & monthly_logs, Vector<const DataLog *> & months, int selected_year)
{
    months.Clear();
    while (months.Size() < 12)
    {
        months.Insert(months.Size(), nullptr);
    }

    Date month;

    for (int i{0}; i < monthly_logs.Size(); i++)
    {

        monthly_logs[i].GetMinMonth(month);

        if ((month.GetYear() == selected_year) && (monthly_logs[i].Size() > 0))
        {
            months[month.GetMonth() - 1] = &(monthly_logs[i]);
        }
    }
}

void outputMonthWindSpeed(const Vector<DataLog> & monthly_logs, Date selected_month)
{
    std::cout << MonthString(selected_month.GetMonth()) << ' ' << selected_month.GetYear() << ':';

    Date month;

    int month_index{-1};
    for (int i{0}; i < monthly_logs.Size(); i++)
    {

        monthly_logs[i].GetMinMonth(month);
        if (month.GetYear() == selected_month.GetYear() && month.GetMonth() == selected_month.GetMonth() && monthly_logs[i].Size() > 0)
        {
            month_index = i;
            break;
        }
    }

    if (month_index <= -1)
    {
        std::cout << " No Data\n\n";
        return;
    }

    double mean = CalcMeanSpeed(monthly_logs[month_index]);
    double sd = CalcSDSpeed(monthly_logs[month_index]);

    if (mean <= DATA_EMPTY)
    {
        std::cout << " No Data\n\n";
    }
    else
    {
        std::cout << "\nAverage speed: " << mean << " km/h"
             << "\nSample stdev: " << sd << "\n\n";
    }
}

void outputMonthlyAirTemp(const Vector<DataLog> & monthly_logs, int selected_year)
{
    std::cout << selected_year << '\n';

    Vector<const DataLog *> months{0};
    extractYear(monthly_logs, months, selected_year);

    for (int i{0}; i < months.Size(); i++)
    {

        if (months[i] == nullptr)
        {
            std::cout << MonthString(i + 1) << ": No Data\n";
            continue;
        }

        std::cout << MonthString(i + 1) << ": ";

        double mean = CalcMeanTemperature(*(months[i]));
        double sd = CalcSDTemperature(*(months[i]));

        if (mean <= DATA_EMPTY)
        {
            std::cout << "No Data\n";
        }
        else
        {
            std::cout << "average: " << mean << " degrees C"
                 << ", stdev: " << sd << '\n';
        }
    }
}

void outputMonthlySolarRad(const Vector<DataLog> & monthly_logs, int selected_year)
{
    std::cout << selected_year << '\n';

    Vector<const DataLog *> months{0};
    extractYear(monthly_logs, months, selected_year);

    for (int i{0}; i < months.Size(); i++)
    {

        if (months[i] == nullptr)
        {
            std::cout << MonthString(i + 1) << ": No Data\n";
            continue;
        }

        std::cout << MonthString(i + 1) << ": ";

        double total = CalcTotalSolarRadiation(*(months[i]));

        if (total <= DATA_EMPTY)
        {
            std::cout << "No Data\n";
        }
        else
        {
            std::cout << total << " kWh/m\u00B2\n";
        }
    }
}

void outputYearData(std::ostream & output, const Vector<DataLog> & monthly_logs, int selected_year)
{
    output << std::fixed << std::setprecision(1);
    output << selected_year << '\n';

    Vector<const DataLog *> months{0};
    extractYear(monthly_logs, months, selected_year);

    for (int i{0}; i <= 12; i++)
    {
        if (i == 12)
        {
            output << "No Data";
            return;
        }
        else if (months[i] != nullptr)
        {
            break;
        }
    }

    for (int i{0}; i < months.Size(); i++)
    {

        if (months[i] == nullptr)
        {
            continue;
        }

        output << MonthString(i + 1) << ",";

        double mean = CalcMeanSpeed(*(months[i]));
        double sd = CalcSDSpeed(*(months[i]));

        if (mean <= DATA_EMPTY)
        {
            output << " ,";
        }
        else
        {
            output << mean << '(' << sd << "),";
        }

        mean = CalcMeanTemperature(*(months[i]));
        sd = CalcSDTemperature(*(months[i]));

        if (mean <= DATA_EMPTY)
        {
            output << " ,";
        }
        else
        {
            output << mean << '(' << sd << "),";
        }

        double total = CalcTotalSolarRadiation(*(months[i]));

        if (total <= DATA_EMPTY)
        {
            output << " \n";
        }
        else
        {
            output << total << '\n';
        }
    }
}
