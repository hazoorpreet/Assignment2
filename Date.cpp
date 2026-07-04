#include "Date.h"

using namespace std;

Date::Date(): m_day(1), m_month(1), m_year(2000) {}

Date::Date(int day, int month, int year): m_day(day), m_month(month), m_year(year) {}

int Date::GetDay() const
{
    return m_day;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}

void Date::SetMonth(int month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

bool Date::operator==(const Date & other) {
    return (m_year == other.m_year) && (m_month == other.m_month) && (m_day == other.m_day);
 }

const char * MonthString(int month)
{
    switch (month)
    {
    case 1:
        return "January";
    case 2:
        return "Feburary";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return nullptr;
    }
}
