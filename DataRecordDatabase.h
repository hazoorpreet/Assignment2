#ifndef DATARECORDDATABASE_H
#define DATARECORDDATABASE_H

#include "DataRecord.h"
#include "Bst.h"
#include "Map.h"
#include "Date.h"
#include "Time.h"
#include "Vector.h"

/** @brief Database to hold DataRecords with no duplicate information and no duplicate data
 *
 * @author Hazoorpreet Singh
 * @date   19 July 2026
 */
class DataRecordDatabase{
private:

    /** @brief Stripped down DataRecord without year and month.
     *
     */
    class DatabaseRecord{
    public:

        /** @brief Default constructor for database record.
         *
         */
        DatabaseRecord();

        /** @brief Construct database record from Data Record.
         *
         * @param[in] data_record - DataRecord instance to copy.
         */
        DatabaseRecord(const DataRecord & data_record);

        /** @brief Get day of month of data record
         *
         */
        int GetDay() const;

        /** @brief Get time of data record
         *
         * @param[out] time - Time of data record
         */
        void GetTime(Time & time) const;

        /** @brief Get solar radiation of record
         *
         */
        double GetSolarRadiation() const;

        /** @brief Get wind speed of record
         *
         */
        double GetSpeed() const;

        /** @brief Get temperature of record
         *
         */
        double GetTemperature() const;

        /** @brief Set day of month of data record
         *
         * @param[in] day - Day of record
         */
        void SetDay(int day);

        /** @brief Set time of data record
         *
         * @param[in] time - Time of data record
         */
        void SetTime(const Time & time);

        /** @brief Set solar radiation of record
         *
         * @param[in] solar_radiation - Solar Radiation of record
         */
        void SetSolarRadiation(double solar_radiation);

        /** @brief Set wind speed of record
         *
         * @param[in] speed - Wind Speed of record
         */
        void SetSpeed(double speed);

        /** @brief Set temperature of record
         *
         * @param[in] temperature - Temperature of record
         */
        void SetTemperature(double temperature);

        /** @brief Compare database records - more than
         *
         * @param[in] other - Other Database Record to compare against.
         */
        bool operator>(const DatabaseRecord & other) const;

        /** @brief Compare database records - less than
         *
         * @param[in] other - Other Database Record to compare against.
         */
        bool operator<(const DatabaseRecord & other) const;

        /** @brief Compare database records - equal to
         *
         * @param[in] other - Other Database Record to compare against.
         */
        bool operator==(const DatabaseRecord & other) const;

    private:
        int m_day;
        Time m_time;
        double m_solar_radiation;
        double m_speed;
        double m_temperature;
    };
public:

    /** @brief Create empty data record database.
     *
     */
    DataRecordDatabase();

    /** @brief Insert DataRecord item into database.
     *
     * @param[in] data_record - DataRecord to insert
     * @retval True - Insertion successful
     * @retval False - Insertion unsuccessful
     */
    bool Insert(const DataRecord & data_record);

    /** @brief Get solar radiation for a month.
     *
     * @param[in] date - Month to get valid solar radiation records from, day is ignored.
     * @param[out] values - Vector to input values to.
     * @retval True - Month data found
     * @retval False - No data contained in month
     */
    bool GetMonthSolarRadiation(const Date & date, Vector<double> & values) const;

    /** @brief Get wind speed for a month.
     *
     * @param[in] date - Month to get valid wind speed records from, day is ignored.
     * @param[out] values - Vector to input values to.
     * @retval True - Month data found
     * @retval False - No data contained in month
     */
    bool GetMonthSpeed(const Date & date, Vector<double> & values) const;

    /** @brief Get temperature for a month.
     *
     * @param[in] date - Month to get valid temperature records from, day is ignored.
     * @param[out] values - Vector to input values to.
     * @retval True - Month data found
     * @retval False - No data contained in month
     */
    bool GetMonthTemperature(const Date & date, Vector<double> & values) const;

    /** @brief Get records for a month.
     *
     * @param[in] date - Month to get valid records from, day is ignored.
     * @param[out] values - Vector to input values to.
     * @retval True - Month data found
     * @retval False - No data contained in month
     */
    bool GetMonthRecords(const Date & date, Vector<DataRecord> & records) const;

    /** @brief Get which years are contained in database
     *
     * @param[out] years - Years contained in database in ascending order
     */
    void GetYears(Vector<int> & years) const;

    /** @brief Check if year data is contained in database
     *
     * @param[out] year - Year to check
     * @return If year exists in database or not
     */
    bool HasYear(int year) const;

    /** @brief Get database size
     *
     * @return Number of records in database
     */
    int Size();

    /** @brief Clear database data
     *
     */
    void Clear();

    /** @brief Database virtual destructor
     *
     */
    virtual ~DataRecordDatabase();

private:
    Map<int, Map<int,  Bst<DatabaseRecord>>> m_db; /// Database
    int m_size; /// Number of records in database
    Bst<int> m_years; /// Years in database

    // Collectors, pointers as it will have the same effect as copying
    // but takes less memory
    static Vector<double> * data_collector;

    static Vector<DataRecord> * record_collector;
    static const Date * record_collection_month;

    static Vector<int> * years_collector;

    // Collection functions CANNOT BE MULTITHREADED. They will conflict as they are pointing to the same collectors.

    /** @brief Collect valid solar radiation from database objects in database
     *
     * @param[in] database_record - Database Record to collect from
     */
    static void CollectSolarRadiation(const DatabaseRecord & database_record);

    /** @brief Collect valid wind speeds from database objects in database
     *
     * @param[in] database_record - Database Record to collect from
     */
    static void CollectSpeed(const DatabaseRecord & database_record);

    /** @brief Collect valid temperatures from database objects in database
     *
     * @param[in] database_record - Database Record to collect from
     */
    static void CollectTemperature(const DatabaseRecord & database_record);

    /** @brief Collect records from database objects in database
     *
     * @param[in] database_record - Database Record to collect from
     */
    static void CollectRecords(const DatabaseRecord & database_record);

    /** @brief Collect years in database
     *
     * @param[out] years - Years to collect
     */
    static void CollectYears(const int & years);

    /** @brief Walk a function through a given month
     *
     * @param[in] date - Month to walk
     * @param[in] func - Function to walk the month
     */
    bool WalkMonth(const Date & date, void (*func)(const DatabaseRecord &)) const;
};

#endif // DATARECORDDATABASE_H
