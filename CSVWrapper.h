#ifndef CSVWRAPPER_H
#define CSVWRAPPER_H
#include "Vector.h"
#include <string>
#include <fstream>

/** @brief CSVWrapper is an adapter class for CSV Files
 *
 * @author Hazoorpreet Singh
 * @date   19 July 2026
 */
class CSVWrapper
{
public:

    /** @brief Default constructor for CSV Wrapper
     *
     */
    CSVWrapper();

    /** @brief Open a file
     *
     * @param[in] file_name - Location of file to open
     * @retval True - Successfully opened.
     * @retval False - Not opened.
     */
    bool Open(const std::string & file_name);

    /** @brief Close file
     *
     */
    void Close();

    /** @brief Extract by specific column numbers (including headers for first line if applicable)
     *
     * @param[in] column_numbers - Column numbers to extract by
     */
    void ExtractByColumns(const Vector<int> & column_numbers);

    /** @brief Extract all columns (including headers for first line if applicable)
     *
     */
    void ExtractByColumns();

    /** @brief Extract by specific headers (excluding headers for first line)
     *
     * @param[in] headers - Headers to be extracted
     */
    void ExtractByHeaders(const Vector<std::string> & headers);

    /** @brief Extract all columns (excluding headers for first line if applicable)
     *
     */
    void ExtractByHeaders();

    /** @brief If file has reached end (or is closed)
     *
     * @retval True - File has reached end and cannot be extracted from anymore
     * @retval False - File has not reached end and can continue to be extracted from
     */
    bool Eof() const;

    /** @brief Seek a specific line in the file
     *
     * @param[in] line_num - Line number to seek (0 will be header line or first line if not applicable)
     * @retval True - Line ready to be extracted
     * @retval False - Line cannot be extracted as end of file has been reached
     */
    bool SeekLine(int line_num);

    /** @brief Extract a line of data from the CSV file
     *
     * @param[out] line_data - Vector to input line data in order of headers or column numbers selected
     * @retval True - File has reached end and cannot be extracted from anymore
     * @retval False - File has not reached end and can continue to be extracted from
     */
    bool GetLine(Vector<std::string> & line_data);

private:
    static constexpr int COL_NOT_FOUND{-1};
    Vector<int> m_extraction_columns;
    Vector<int> m_output_columns;
    std::ifstream m_file;

    void ExtractFileHeaders(Vector<std::string> & file_headers);
};

#endif // CSVWRAPPER_H
