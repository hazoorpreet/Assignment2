#include "DataRecord.h"

DataRecord::DataRecord(): m_solar_radiation{0}, m_speed{0}, m_temperature{0}, m_date{}, m_time{} {}
DataRecord::DataRecord(const Date & date, const Time & time, double solar_radiation, double speed, double temperature): m_solar_radiation{solar_radiation}, m_speed{speed}, m_temperature{temperature}, m_date{date}, m_time{time} {}

double DataRecord::GetSolarRadiation() const { return m_solar_radiation; }
double DataRecord::GetSpeed() const { return m_speed; }
double DataRecord::GetTemperature() const { return m_temperature; }
void DataRecord::GetDate(Date & date) const { date = m_date; }
void DataRecord::GetTime(Time & time) const { time = m_time; }

void DataRecord::SetSolarRadiation(double solar_radiation) { m_solar_radiation = solar_radiation; }
void DataRecord::SetSpeed(double speed) { m_speed = speed; }
void DataRecord::SetTemperature(double temperature) { m_temperature = temperature; }
void DataRecord::SetDate(const Date & date) { m_date = date; }
void DataRecord::SetTime(const Time & time) { m_time = time; }
