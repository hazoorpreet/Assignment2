#ifndef VECTORDATAOPERATIONS_H
#define VECTORDATAOPERATIONS_H
#include "Vector.h"
#include <cmath>
#include <stdexcept>

class VectorDataOperations
{
public:
    static double CalcTotal(const Vector<double> & data);
    static double CalcMean(const Vector<double> & data);
    static double CalcSD(const Vector<double> & data);
    static double CalcsPCC(const Vector<double> & data_a, const Vector<double> & data_b);
    static double CalcMAD(const Vector<double> & data);
    template <typename T, typename U>
    static void GetCorrelatableObjectData(const Vector<T> & items, Vector<U> & data_a,
                                          Vector<U> & data_b, U(T::*get_data_a)() const, U(T::*get_data_b)() const, U min_val)
    {

        for (int i{0}; i < items.Size(); i++)
        {
            if (((items[i].*get_data_a)() < min_val) || ((items[i].*get_data_b)() < min_val))
            {
                continue;
            }
            else
            {
                data_a.Insert(data_a.Size(), (items[i].*get_data_a)());
                data_b.Insert(data_b.Size(), (items[i].*get_data_b)());
            }
        }
    }
};

#endif // VECTORDATAOPERATIONS_H
