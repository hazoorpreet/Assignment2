#ifndef VECTORDATAOPERATIONS_H
#define VECTORDATAOPERATIONS_H
#include "Vector.h"
#include <cmath>
#include <stdexcept>

class VectorDataOperations {
public:
    static double CalcTotal(const Vector<double> & data);
    static double CalcMean(const Vector<double> & data);
    static double CalcSD(const Vector<double> & data);
    static double CalcsPCC(const Vector<double> & data_a, const Vector<double> & data_b);
    static double CalcMAD(const Vector<double> & data);
};

#endif // VECTORDATAOPERATIONS_H
