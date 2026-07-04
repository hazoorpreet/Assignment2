#ifndef DATALOG_H
#define DATALOG_H
#include "Time.h"
#include "Date.h"
#include "Vector.h"
#include "DataRecord.h"

/** @brief DataLog class to hold data records.
 * @details DataLog class to hold data records. Data can only be
 * added or retrieved as it is made to aggregate data from CSVs.
 *
 * @author Hazoorpreet Singh
 * @date   22/06/2026
 */
class DataLog
{
public:

    /** @brief Constructor for data log.
     *
     */
    DataLog();


    /** @brief Get minimum month
     *
     * @param[out] month - Minimum month, day does not matter.
     */
    void GetMinMonth(Date & month) const;

    /** @brief Get maximum month
     *
     * @param[out] month - Maximum month, day does not matter.
     */
    void GetMaxMonth(Date & month) const;

    /** @brief Get Month data
     *
     * @param[out] other - Data log to enter data into
     * @param[out] month - Month to extract
     */
    void GetMonthData(DataLog & other, const Date & month) const;

    /** @brief Add a record to the log
     *
     * @param[in] record - Record of data, must have a valid date and time
     */
    bool AddRecord(const DataRecord & record);

    /** @brief Clear data
     *
     */
    void Clear();

    /** @brief Retrieve number of records
     *
     */
    int Size() const;

    /** @brief Retrieve mutable reference to log item
     *
     * @param[in] index Index of element to retrieve from 0 to the number of elements minus one
     * @exception std::out_of_range Thrown if value selected outside of vector size
     * @return Mutable reference to vector element
     */
    DataRecord &operator[](int index);

    /** @brief Retrieve immutable reference to log item
     *
     * @param[in] index Index of element to retrieve from 0 to the number of elements minus one
     * @exception std::out_of_range Thrown if value selected outside of vector size
     * @return immutable reference to vector element
     */
    const DataRecord &operator[](int index) const;

private:
    Date m_min_month;
    Date m_max_month;
    Vector<DataRecord> m_records;

    /** @brief Compares two months
     *
     * @param[in] month_a - First month, not considering the day
     * @param[in] month_b - Second month, not considering the day
     *
     * @retval 1 - Month 1 is later than Month 2
     * @retval 0 - Month 1 is equal to Month 2
     * @retval -1 - Month 1 is earlier than Month 2
     */
    static int month_compare(const Date & month_a, const Date & month_b);

    /** @brief Tests if record already in list
     *
     * @retval True - Record already in list
     * @retval False - Record not in list
     */
    bool in_list(const DataRecord & record);
};

#endif // DATALOG_H
