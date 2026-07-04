#include "DataLog.h"

DataLog::DataLog(): m_min_month{0, 0, -1}, m_max_month{0, 0, -1}, m_records{0} {}
void DataLog::GetMinMonth(Date & month) const
{
    month = m_min_month;
}
void DataLog::GetMaxMonth(Date & month) const
{
    month = m_max_month;
}
void DataLog::GetMonthData(DataLog & other, const Date & month) const
{
    other.Clear();
    Date record_date;
    for (int i{0}; i < m_records.Size(); i++)
    {
        m_records[i].GetDate(record_date);
        if (month_compare(month, record_date) == 0)
        {
            // Insert directly due to already being deduplicated
            other.m_records.Insert(other.Size(), m_records[i]);
        }
    }
}
bool DataLog::AddRecord(const DataRecord & record)
{
    if (in_list(record)) {
        return false;
    }

    if (!m_records.Insert(m_records.Size(), record))
    {
        return false;
    }

    Date date;
    record.GetDate(date);

    if (m_min_month.GetYear() == -1)
    {
        m_min_month = date;
        m_max_month = date;
    }
    else if (month_compare(date, m_min_month) == -1)
    {
        m_min_month = date;
    }
    else if (month_compare(date, m_max_month) == 1)
    {
        m_max_month = date;
    }
    return true;
}

void DataLog::Clear()
{
    m_records.Clear();
    m_min_month.SetYear(-1);
    m_max_month.SetYear(-1);
}

int DataLog::Size() const
{
    return m_records.Size();
}

DataRecord & DataLog::operator[](int index)
{
    return m_records[index];
}

const DataRecord & DataLog::operator[](int index) const
{
    return m_records[index];
}

int DataLog::month_compare(const Date & month_a, const Date & month_b)
{
    if (month_a.GetYear() > month_b.GetYear())
    {
        return 1;
    }
    else if (month_a.GetYear() < month_b.GetYear())
    {
        return -1;
    }
    else if (month_a.GetMonth() > month_b.GetMonth())
    {
        return 1;
    }
    else if (month_a.GetMonth() < month_b.GetMonth())
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

bool DataLog::in_list(const DataRecord & record) {
    Date record_date;
    Time record_time;
    record.GetDate(record_date);
    record.GetTime(record_time);
    Date existing_date;
    Time existing_time;
    for (int i{0}; i < m_records.Size(); i++) {
        m_records[i].GetDate(existing_date);
        m_records[i].GetTime(existing_time);
        if ((existing_date == record_date) && (existing_time == record_time)) {
            return true;
        }
    }
    return false;
}

