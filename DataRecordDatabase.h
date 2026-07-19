#ifndef DATARECORDDATABASE_H
#define DATARECORDDATABASE_H

#include "DataRecord.h"
#include "Bst.h"
#include "Map.h"
#include "Date.h"
#include "Time.h"
#include "Vector.h"

class DataRecordDatabase{
private:
    class DatabaseRecord{
    public:
        DatabaseRecord();
        DatabaseRecord(int day, const Time & time, double solar_radiation, double speed, double temperature);
        DatabaseRecord(const DataRecord & data_record);
        int GetDay() const;
        void GetTime(Time & time) const;
        double GetSolarRadiation() const;
        double GetSpeed() const;
        double GetTemperature() const;

        void SetDay(int day);
        void SetTime(const Time & time);
        void SetSolarRadiation(double solar_radiation);
        void SetSpeed(double speed);
        void SetTemperature(double temperature);

        bool operator>(const DatabaseRecord & other) const;
        bool operator<(const DatabaseRecord & other) const;
        bool operator==(const DatabaseRecord & other) const;

    private:
        int m_day;
        Time m_time;
        double m_solar_radiation;
        double m_speed;
        double m_temperature;
    };
public:

    DataRecordDatabase();
    bool Insert(const DataRecord & data_record);
    bool GetMonthSolarRadiation(const Date & date, Vector<double> & values) const;
    bool GetMonthSpeed(const Date & date, Vector<double> & values) const;
    bool GetMonthTemperature(const Date & date, Vector<double> & values) const;
    bool GetMonthRecords(const Date & date, Vector<DataRecord> & records) const;
    void GetYears(Vector<int> & years) const;
    bool HasYear(int year) const;

    int Size();

    void Clear();

    virtual ~DataRecordDatabase();

private:
    Map<int, Map<int,  Bst<DatabaseRecord>>> m_db; /// Database
    int m_size; /// Number of records in database
    Bst<int> m_years;

    // Collectors, pointers as it will have the same effect as copying
    // but takes less memory
    static Vector<double> * data_collector;

    static Vector<DataRecord> * record_collector;
    static const Date * record_collection_month;

    static Vector<int> * years_collector;

    // Collection functions CANNOT BE MULTITHREADED. They will conflict as they are pointing to the same collectors.
    static void CollectSolarRadiation(const DatabaseRecord & database_record);
    static void CollectSpeed(const DatabaseRecord & database_record);
    static void CollectTemperature(const DatabaseRecord & database_record);
    static void CollectRecords(const DatabaseRecord & database_record);
    static void CollectYears(const int & years);
    bool WalkMonth(const Date & date, void (*func)(const DatabaseRecord &)) const;
};

#endif // DATARECORDDATABASE_H
