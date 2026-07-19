#ifndef DATE_H
#define DATE_H

/** @brief Modeled after Date information
 *
 * @author Hazoorpreet Singh
 * @date 5/07/2026
 *
 */
class Date
{
public:
    /** @brief Create an Empty Date
     *
     */
    Date();

    /** @brief Create a date with day, month, and year
     *
     * @param[in] day Day (1 to 31)
     * @param[in] month Month (1 to 12)
     * @param[in] year Year (Any positive integer)
     */
    Date(int day, int month, int year);

    /** @brief Get Day
     *
     * @return Day of Date
     */
    int GetDay() const;

    /** @brief Get Month
     *
     * @return Month of Date
     */
    int GetMonth() const;

    /** @brief Get Year
     *
     * @return Year of Date
     */
    int GetYear() const;

    /** @brief Set Day
     *
     * @param[in] day Day of Date (1 to 31)
     */
    void SetDay(int day);

    /** @brief Set Month
     *
     * @param[in] month Month of Date (1 to 12)
     */
    void SetMonth(int month);

    /** @brief Set Year
     *
     * @param[in] year Year of Date (Any positive integer)
     */
    void SetYear(int year);

    /** @brief Equality Comparison
     *
     * @param[in] other - Other date to compare against
     */
    bool operator==(const Date & other) const;

    /** @brief Less Than Comparison
     *
     * @param[in] other - Other date to compare against
     */
    bool operator<(const Date & other) const;

    /** @brief More Than Comparison
     *
     * @param[in] other - Other date to compare against
     */
    bool operator>(const Date & other) const;

    /** @brief More Than or Equal Comparison
     *
     * @param[in] other - Other date to compare against
     */
    bool operator>=(const Date & other) const;

    /** @brief Less Than or Equal Comparison
     *
     * @param[in] other - Other date to compare against
     */
    bool operator<=(const Date & other) const;


private:
    int m_day;
    int m_month;
    int m_year;
};

/** @brief
 *
 * @param[in] month Input stream object
 *
 * @return String containing the month name OR nullptr if invalid
 */
const char * MonthString(int month);

#endif
