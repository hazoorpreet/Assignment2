#include "Time.h"

Time::Time(int hours, int minutes, int seconds): m_hours(hours), m_minutes(minutes), m_seconds(seconds) {}
int Time::GetHours() const
{
    return m_hours;
}
int Time::GetMinutes() const
{
    return m_minutes;
}
int Time::GetSeconds() const
{
    return m_seconds;
}
void Time::SetHours(int hours)
{
    m_hours = hours;
}
void Time::SetMinutes(int minutes)
{
    m_minutes = minutes;
}
void Time::SetSeconds(int seconds)
{
    m_seconds = seconds;
}

bool Time::operator==(const Time & other) const {
    return (m_hours == other.m_hours) && (m_minutes == other.m_minutes) && (m_seconds == other.m_seconds);
}

bool Time::operator<(const Time & other) const
{
    return ((m_hours < other.m_hours) || // year case
            ((m_hours == other.m_hours) && // if year is the same
             ((m_minutes < other.m_minutes) || // month case
              ((m_minutes == other.m_minutes) && (m_seconds < other.m_seconds)) // date case
             )
            )
           );
}

bool Time::operator>(const Time & other) const
{
    return ((m_hours > other.m_hours) || // year case
            ((m_hours == other.m_hours) && // if year is the same
             ((m_minutes > other.m_minutes) || // month case
              ((m_minutes == other.m_minutes) && (m_seconds > other.m_seconds)) // date case
             )
            )
           );
}

bool Time::operator>=(const Time & other) const {
    return (*this == other) || (*this > other);
}

bool Time::operator<=(const Time & other) const {
    return (*this == other) || (*this < other);
}
