#include <iostream>
#include "CSVWrapper.h"
#include "Vector.h"

std::ostream & operator<<(std::ostream & output, const Vector<std::string> & data);

int main()
{

    CSVWrapper csv{};
    if (!csv.Open("data/TestData.csv"))
    {
        std::cout << "File could not be opened.\n";
        return -1;
    }

    Vector<std::string> headers_to_extract{};
    headers_to_extract.Insert(0, "WAST");
    headers_to_extract.Insert(1, "T");
    headers_to_extract.Insert(2, "SR");
    headers_to_extract.Insert(3, "S");

    Vector<int> columns_to_extract{};
    columns_to_extract.Insert(0, 0);
    columns_to_extract.Insert(1, 11);
    columns_to_extract.Insert(2, 13);
    columns_to_extract.Insert(3, 12);

    Vector<std::string> output{};

    csv.ExtractByHeaders();
    std::cout << "Test 1: Output via all headers\n";
    while (csv.GetLine(output))
    {
        std::cout << output;
    }
    std::cout << "\n\n";

    csv.ExtractByHeaders(headers_to_extract);
    std::cout << "Test 2: Output via select headers\n";
    while (csv.GetLine(output))
    {
        std::cout << output;
    }
    std::cout << "\n\n";

    csv.ExtractByColumns();
    std::cout << "Test 3: Output via all columns\n";
    while (csv.GetLine(output))
    {
        std::cout << output;
    }
    std::cout << "\n\n";

    csv.ExtractByColumns(columns_to_extract);
    std::cout << "Test 4: Output via select columns\n";
    while (csv.GetLine(output))
    {
        std::cout << output;
    }
    std::cout << "\n\n";

    std::cout << "Test 5: Check for end of file\n";
    std::cout << (csv.Eof() ? "True" : "False") << "\n\n";

    std::cout << "Test 6: Seek line 3 and output\n";
    csv.SeekLine(3);
    csv.GetLine(output);
    std::cout << output;
    std::cout << "\n\n";

    return 0;
}

std::ostream & operator<<(std::ostream & output, const Vector<std::string> & data)
{
    for (int i{0}; i < data.Size(); i++)
    {
        output << data[i] << ' ';
    }
    output << '\n';
    return output;
}
