#include "DataRecordDatabase.h"

Vector<double> * DataRecordDatabase::data_collector{nullptr};
Vector<DataRecord> * DataRecordDatabase::record_collector{nullptr};
const Date * DataRecordDatabase::record_collection_month{nullptr};


int DataRecordDatabase::Size() {return m_size;}

DataRecordDatabase::DataRecordDatabase(): m_db{}, m_size{} {};

void DataRecordDatabase::Clear() {
    m_db.Clear();
    m_size = 0;
}

bool DataRecordDatabase::Insert(const DataRecord & data_record) {
    Date date;
    data_record.GetDate(date);
    if (!m_db.Find(date.GetYear())) {
        m_db.Emplace(date.GetYear(), {});
    }

    if (!m_db[date.GetYear()].Find(date.GetMonth())) {
        m_db[date.GetYear()].Emplace(date.GetMonth(), {});
    }

    if (m_db[date.GetYear()][date.GetMonth()].Insert(data_record)) {
        m_size++;
        return true;
    }
    return false;
}


bool DataRecordDatabase::GetMonthSolarRadiation(const Date & date, Vector<double> & values) const {
    data_collector = &values;
    bool success{WalkMonth(date, DataRecordDatabase::CollectSolarRadiation)};
    data_collector = nullptr;
    return success;
}

bool DataRecordDatabase::GetMonthSpeed(const Date & date, Vector<double> & values) const {
    data_collector = &values;
    bool success{WalkMonth(date, DataRecordDatabase::CollectSpeed)};
    data_collector = nullptr;
    return success;
}

bool DataRecordDatabase::GetMonthTemperature(const Date & date, Vector<double> & values) const {
    data_collector = &values;
    bool success{WalkMonth(date, DataRecordDatabase::CollectTemperature)};
    data_collector = nullptr;
    return success;
}


bool DataRecordDatabase::GetMonthRecords(const Date & date, Vector<DataRecord> & records) const {
    record_collector = &records;
    record_collection_month = &date;
    bool success{WalkMonth(date, DataRecordDatabase::CollectRecords)};
    record_collector = nullptr;
    record_collection_month = nullptr;
    return success;
}

void DataRecordDatabase::CollectSolarRadiation(const DatabaseRecord & database_record) {
    double solar_radiation = database_record.GetSolarRadiation();
    if (solar_radiation >= DataRecord::MIN_VAL) {
        data_collector->Insert(data_collector->Size(), solar_radiation);
    }
}

void DataRecordDatabase::CollectSpeed(const DatabaseRecord & database_record) {
    double speed = database_record.GetSpeed();
    if (speed >= DataRecord::MIN_VAL) {
        data_collector->Insert(data_collector->Size(), speed);
    }
}

void DataRecordDatabase::CollectTemperature(const DatabaseRecord & database_record) {
    double temperature = database_record.GetTemperature();
    if (temperature >= DataRecord::MIN_VAL) {
        data_collector->Insert(data_collector->Size(), temperature);
    }
}

void DataRecordDatabase::CollectRecords(const DatabaseRecord & database_record) {
    Time time;
    database_record.GetTime(time);
    DataRecord data_record{{database_record.GetDay(), record_collection_month->GetMonth(), record_collection_month->GetYear()}, time,
                             database_record.GetSolarRadiation(), database_record.GetSpeed(), database_record.GetTemperature()};
    record_collector->Insert(record_collector->Size(), data_record);
}

bool DataRecordDatabase::WalkMonth(const Date & date, void (*func)(const DatabaseRecord &)) const {
    if (!m_db.Find(date.GetYear())) {
        return false;
    }

    if (!m_db[date.GetYear()].Find(date.GetMonth())) {
        return false;
    }

    m_db[date.GetYear()][date.GetMonth()].InOrder(func);
    return true;
}

DataRecordDatabase::~DataRecordDatabase() {}; // no action required as map and bst will clean themselves up.

DataRecordDatabase::DatabaseRecord::DatabaseRecord(): m_day{}, m_time{}, m_solar_radiation{}, m_speed{}, m_temperature{} {}

DataRecordDatabase::DatabaseRecord::DatabaseRecord(int day, const Time & time, double solar_radiation, double speed, double temperature): m_day{day}, m_time{time}, m_solar_radiation{solar_radiation}, m_speed{speed}, m_temperature{temperature} {}

DataRecordDatabase::DatabaseRecord::DatabaseRecord(const DataRecord & data_record): m_day{}, m_time{}, m_solar_radiation{data_record.GetSolarRadiation()}, m_speed{data_record.GetSpeed()}, m_temperature{data_record.GetTemperature()} {
    Date date;
    data_record.GetDate(date);
    m_day = date.GetDay();
    Time time;
    data_record.GetTime(time);
    m_time = time;
}

int DataRecordDatabase::DatabaseRecord::GetDay() const {
    return m_day;
}
void DataRecordDatabase::DatabaseRecord::GetTime(Time & time) const {
    time = m_time;
}
double DataRecordDatabase::DatabaseRecord::GetTemperature() const {
    return m_temperature;
}
double DataRecordDatabase::DatabaseRecord::GetSpeed() const {
    return m_speed;
}
double DataRecordDatabase::DatabaseRecord::GetSolarRadiation() const {
    return m_solar_radiation;
}

void DataRecordDatabase::DatabaseRecord::SetDay(int day) {
    m_day = day;
}
void DataRecordDatabase::DatabaseRecord::SetTime(const Time & time) {
    m_time = time;
}
void DataRecordDatabase::DatabaseRecord::SetTemperature(double temperature) {
    m_temperature = temperature;
}
void DataRecordDatabase::DatabaseRecord::SetSpeed(double speed) {
    m_speed = speed;
}
void DataRecordDatabase::DatabaseRecord::SetSolarRadiation(double solar_radiation) {
    m_solar_radiation = solar_radiation;
}

bool DataRecordDatabase::DatabaseRecord::operator<(const DatabaseRecord & other) const {
    return (m_day < other.m_day) || ((m_day == other.m_day) && (m_time < other.m_time));
}
bool DataRecordDatabase::DatabaseRecord::operator>(const DatabaseRecord & other) const {
    return (m_day > other.m_day) || ((m_day == other.m_day) && (m_time > other.m_time));
}
bool DataRecordDatabase::DatabaseRecord::operator==(const DatabaseRecord & other) const {
    return (m_day == other.m_day) && (m_time == other.m_time);
}
