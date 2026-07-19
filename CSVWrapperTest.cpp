#include <iostream>
#include "CSVWrapper.h"
#include "Vector.h"

std::ostream & operator<<(std::ostream & output, const Vector<std::string> & data);

int main() {
    Vector<std::string> headers_to_extract{};
    headers_to_extract.Insert(0, "WAST");
    headers_to_extract.Insert(1, "T");
    headers_to_extract.Insert(2, "SR");
    headers_to_extract.Insert(3, "S");

    CSVWrapper csv{};
    if (!csv.Open("data/MetData_Mar01-2015-Mar01-2016-ALL.csv")) {
        std::cout << "File could not be opened.\n";
        return -1;
    }

    csv.ExtractByHeaders(headers_to_extract);
    Vector<std::string> output{};

    std::cout << "Test 1: Output via headers\n";
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    std::cout << "\n\n";

    Vector<int> columns_to_extract{};
    columns_to_extract.Insert(0, 0);
    columns_to_extract.Insert(1, 11);
    columns_to_extract.Insert(2, 12);
    columns_to_extract.Insert(3, 13);
    csv.ExtractByColumns(columns_to_extract);
    std::cout << "Test 2: Output via columns\n";
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    csv.GetLine(output);
    std::cout << output;
    std::cout << "\n\n";


    std::cout << "Test 3: Seek line 3 and output\n";
    csv.SeekLine(3);
    csv.GetLine(output);
    std::cout << output;
    std::cout << "\n\n";

    return 0;
}

std::ostream & operator<<(std::ostream & output, const Vector<std::string> & data) {
    for (int i{0}; i < data.Size(); i++) {
        output << data[i] << ' ';
    }
    output << '\n';
    return output;
}
