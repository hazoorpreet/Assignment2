#include "CSVWrapper.h"
#include <sstream>
#include <limits>
#include <iostream>

CSVWrapper::CSVWrapper(): m_extraction_columns{0}, m_output_columns{0}, m_file{} {}

bool CSVWrapper::Open(const std::string & file_name) {
    if (m_file.is_open()) {
        return false;
    }

    // clear extraction to ready for new file
    m_extraction_columns.Clear();
    m_output_columns.Clear();

    m_file.clear();
    m_file.open(file_name);

    if (!m_file) {
        m_file.clear();
        return false;
    }
    return true;
}

void CSVWrapper::Close() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

void CSVWrapper::ExtractByColumns(const Vector<int> & column_numbers) {
    m_extraction_columns = column_numbers;
    m_output_columns.Clear();

    m_output_columns.Insert(0, 0);
    for (int i{1}; i < m_extraction_columns.Size(); i++)
    {
        int val = m_extraction_columns[i];
        for (int j{i - 1}; j >= -1; j--)
        {
            if (j <= -1)
            {
                m_extraction_columns[0] = val;
                m_output_columns.Insert(0, i);
                break;
            }
            else if (m_extraction_columns[j] > val)
            {
                m_extraction_columns[j + 1] = m_extraction_columns[j];
            }
            else
            {
                m_extraction_columns[j + 1] = val;
                m_output_columns.Insert(j + 1, i);
                break;
            }
        }
    }
}

void CSVWrapper::ExtractByColumns() {
    ExtractByHeaders();
    m_file.seekg(0, std::ios::beg);
}

void CSVWrapper::ExtractByHeaders() {
    Vector<std::string> file_headers;
    ExtractFileHeaders(file_headers);
    for (int i{file_headers.Size() - 1}; i >= 0; i--) {
        m_extraction_columns.Insert(0, i);
        m_output_columns.Insert(0, i);
    }
}

void CSVWrapper::ExtractByHeaders(const Vector<std::string> & headers) {
    Vector<std::string> file_headers;
    ExtractFileHeaders(file_headers);

    m_extraction_columns.Clear();
    m_output_columns.Clear();

    for (int i{0}; i < headers.Size(); i++)
    {
        int header_location{CSVWrapper::COL_NOT_FOUND};
        for (int j{0}; j < file_headers.Size(); j++)
        {
            if (file_headers[j].compare(headers[i]) == 0)
            {
                header_location = j;
                break;
            }
        }

        for (int j{i - 1}; j >= -1; j--)
        {
            if (j <= -1)
            {
                m_extraction_columns.Insert(0,header_location);
                m_output_columns.Insert(0, i);
                break;
            }

            if (m_extraction_columns[j] <= header_location)
            {
                m_extraction_columns.Insert(j + 1, header_location);
                m_output_columns.Insert(j + 1, i);
                break;
            }
        }
    }
}

void CSVWrapper::ExtractFileHeaders(Vector<std::string> & file_headers) {
    file_headers.Clear();
    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    std::string header_string;
    getline(m_file, header_string);
    std::stringstream header_stream{header_string};
    std::string header;
    while (getline(header_stream, header, ','))
    {
        file_headers.Insert(file_headers.Size(), header);
    }

    // correct for newline at the end
    std::string & final_header = file_headers[file_headers.Size() - 1];
    final_header = final_header.substr(0, final_header.length() - 1);
}

bool CSVWrapper::Eof() const {

    // if not open that means it is the end.
    if (!m_file.is_open()) {
        return true;
    }

    return m_file.eof();
}

bool CSVWrapper::SeekLine(int line_num) {
    // reset position
    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    // skip lines until line number
    for (int i{0}; (i < line_num) && !m_file.eof(); i++)
    {
        m_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // return false if reached end of file, otherwise return true.
    return !m_file.eof();
}

bool CSVWrapper::GetLine(Vector<std::string> & line_data) {
    if ((m_extraction_columns.Size() == 0)) {
        return false;
    }

    std::string csv_line;
    line_data.Clear();

    while (line_data.Size() < m_extraction_columns.Size()) {
        line_data.Insert(0,"");
    }

    if (getline(m_file, csv_line, '\n'))
    {
        if (csv_line.empty())
        {
            return false;
        }

        std::stringstream line_stream{csv_line};
        int prev_mapping{-1};
        for (int i{0}; i < m_extraction_columns.Size(); i++)
        {
            if (m_extraction_columns[i] == -1)
            {
                line_data[m_output_columns[i]] = "";
            }
            else
            {
                for (int j{prev_mapping + 1}; (j < m_extraction_columns[i]) && !line_stream.eof(); j++)
                {
                    line_stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
                }

                // return extracted data if line reaches end
                if (line_stream.eof()) {
                    return true;
                }

                // retrieve field
                getline(line_stream, line_data[m_output_columns[i]], ',');
                prev_mapping = m_extraction_columns[i];

                // correct in case of newline at the end
                if (line_data[m_output_columns[i]][line_data[m_output_columns[i]].length() - 1] == '\n')
                {
                    std::string & end_correction = line_data[m_output_columns[i]];
                    end_correction = end_correction.substr(0, end_correction.length() - 1);
                }
            }
        }
    } else {
        return false;
    }
    return true;
}
