#include "VectorDataOperations.h"
#include <stdexcept>

double VectorDataOperations::CalcTotal(const Vector<double> & data)
{
    double total{0};
    for (int i{0}; i < data.Size(); i++)
    {
        total += data[i];
    }

    return total;
}

double VectorDataOperations::CalcMean(const Vector<double> & data)
{
    return CalcTotal(data) / data.Size();
}

double VectorDataOperations::CalcSD(const Vector<double> & data) {
    double mean{CalcMean(data)};
    double processed_sum{0};

    for (int i{0}; i < data.Size(); i++)
    {
        processed_sum += (data[i] - mean) * (data[i] - mean);
    }

    return sqrt(processed_sum / (data.Size() - 1));
}

double VectorDataOperations::CalcsPCC(const Vector<double> & data_a, const Vector<double> & data_b) {
    if (data_a.Size() == data_b.Size()) {
        throw std::domain_error("Error: Samples are of different sizes.");
    }

    double mean_a{CalcMean(data_a)};
    double mean_b{CalcMean(data_b)};

    double processed_a{0};
    double processed_b{0};
    double processed_ab{0};
    double processing_a{};
    double processing_b{};

    for (int i{0}; i < data_a.Size(); i++) {
        processing_a = data_a[i] - mean_a;
        processing_b = data_b[i] - mean_b;
        processed_a += processing_a*processing_a;
        processed_b += processing_b*processing_b;
        processed_ab += processing_a*processing_b;
    }

    return processed_ab / (std::sqrt(processed_a) * std::sqrt(processed_b));

}

double VectorDataOperations::CalcMAD(const Vector<double> & data) {
    double mean{CalcMean(data)};
    double processed_sum{0};

    for (int i{0}; i < data.Size(); i++) {
        processed_sum += std::abs(data[i] - mean);
    }

    return processed_sum / data.Size();
}
