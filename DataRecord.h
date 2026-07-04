#ifndef DATARECORD_H
#define DATARECORD_H

#include "Date.h"
#include "Time.h"

/** @brief DataLog class to hold logs for the program
 *
 * @details DataLog class to hold logs for the program. Any value < MIN_VAL is assumed empty.
 * @author Hazoorpreet Singh
 * @date   19/06/2026
 */
class DataRecord {
public:
    static constexpr double MIN_VAL{-40};

    /** @brief Default constructor for data records
     *
     */
    DataRecord();

    /** @brief Construct a data record with all required data
     *
     * @param[in] date - Date of record
     * @param[in] time - Time of record (Only Hour and Minutes)
     * @param[in] solar_radiation - Solar radiation at the time of recording (kWh/m^2)
     * @param[in] speed - Wind speed at the time of recording (km/h)
     * @param[in] temperature - Temperature at the time of recording (C)
     */
    DataRecord(const Date & date, const Time & time, double solar_radiation, double speed, double temperature);

    /** @brief Get recorded solar radiation
     *
     * @return Solar radiation at the time of recording (kWh/m^2)
     */
    double GetSolarRadiation() const;

    /** @brief Get recorded wind speed
     *
     * @return Wind speed at the time of recording (km/h)
     */
    double GetSpeed() const;

    /** @brief Get recorded temperature
     *
     * @return Temperature at the time of recording (C)
     */
    double GetTemperature() const;

    /** @brief Get date of recording
     *
     * @param[out] Date of record
     */
    void GetDate(Date & date) const;

    /** @brief Get time of recording
     *
     * @param[out] Time of record (Only Hour and Minutes)
     */
    void GetTime(Time & time) const;

    /** @brief Set recorded solar radiation
     *
     * @param[in] solar_radiation - Solar radiation at the time of recording (kWh/m^2)
     */
    void SetSolarRadiation(double solar_radiation);

    /** @brief Set recorded wind speed
     *
     * @param[in] sped - Wind speed at the time of recording (km/h)
     */
    void SetSpeed(double speed);

    /** @brief Set recorded temperature
     *
     * @param[in] temperature - Temperature at the time of recording (C)
     */
    void SetTemperature(double temperature);

    /** @brief Set date of recording
     *
     * @param[in] date - Date of record
     */
    void SetDate(const Date & date);

    /** @brief Set time of recording
     *
     * @param[in] time - Time of record
     */
    void SetTime(const Time & time);

private:
    double m_solar_radiation;
    double m_speed;
    double m_temperature;
    Date m_date;
    Time m_time;
};

#endif // DATARECORD_H
