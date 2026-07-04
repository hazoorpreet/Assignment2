#ifndef TIME_H
#define TIME_H

/** @brief Time class modeled after 24h digital clock time.
 *
 * @author Hazoorpreet Singh
 * @date 04/06/2026
 *
 */
class Time
{
public:

    /** @brief Constructor for time
     *
     * @param[in] hours Hour of a day (0 to 23), default 0
     * @param[in] minutes Minutes of the hour (0 to 59), default 0
     * @param[in] seconds Seconds of the minute (0 to 59), default 0
     */
    Time(int hours = 0, int minutes = 0, int seconds = 0);

    /** @brief Get Hours
     *
     * @return Hours
     */
    int GetHours() const;

    /** @brief Get Minutes
     *
     * @return Minutes
     */
    int GetMinutes() const;

    /** @brief Get Seconds
     *
     * @return Seconds
     */
    int GetSeconds() const;

    /** @brief Set Hours (0 to 23)
     *
     * @param[in] hours Hour of a day (0 to 23)
     */
    void SetHours(int hours);

    /** @brief Set Minutes (0 to 59)
     *
     * @param[in] minutes Minutes of the hour (0 to 59)
     */
    void SetMinutes(int minutes);

    /** @brief Set Seconds (0 to 59)
     *
     * @param[in] seconds Seconds of the minute (0 to 59)
     */
    void SetSeconds(int seconds);

    /** @brief Compare equality of times
     *
     * @param[in] other Other time to compare against
     */
     bool operator==(const Time & other);

private:
    int m_hours;
    int m_minutes;
    int m_seconds;
};

#endif // TIME_H
