#ifndef CSVWRAPPER_H
#define CSVWRAPPER_H
#include "Vector.h"
#include <string>
#include <fstream>

class CSVWrapper {
public:
    CSVWrapper();

    bool Open(const std::string & file_name);
    void Close();

    void ExtractByColumns(const Vector<int> & column_numbers);
    void ExtractByColumns();

    void ExtractByHeaders(const Vector<std::string> & headers);
    void ExtractByHeaders();

    bool Eof() const;

    bool SeekLine(int line_num);
    bool GetLine(Vector<std::string> & line_data);
private:
    static constexpr int COL_NOT_FOUND{-1};
    Vector<int> m_extraction_columns;
    Vector<int> m_output_columns;
    std::ifstream m_file;

    void ExtractFileHeaders(Vector<std::string> & file_headers);
};

#endif // CSVWRAPPER_H
