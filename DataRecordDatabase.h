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

    int Size();

    void Clear();

private:
    Map<int, Map<int,  Bst<DatabaseRecord>>> m_db;
    int m_size;
    static Vector<double> * collector;

    static void CollectSolarRadiation(const DatabaseRecord & database_record);
    static void CollectSpeed(const DatabaseRecord & database_record);
    static void CollectTemperature(const DatabaseRecord & database_record);
    bool WalkMonth(const Date & date, void (*func)(const DatabaseRecord &)) const;
};

#endif // DATARECORDDATABASE_H
