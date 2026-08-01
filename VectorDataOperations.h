#ifndef VECTORDATAOPERATIONS_H
#define VECTORDATAOPERATIONS_H
#include "Vector.h"
#include <cmath>
#include <stdexcept>

/** @brief Operations to be used on sets of data stored in Vectors
 *
 * @author Hazoorpreet Singh
 * @date 21/07/2026
 */
class VectorDataOperations
{
public:

    /** @brief Create an object with the same functions. Required for a valid class.
     *
     */
    VectorDataOperations();

    /** @brief Calculate total of all elements in a vector.
     *
     * @param[in] data - Vector double vector containing data
     */
    static double CalcTotal(const Vector<double> & data);

    /** @brief Calculate mean of all elements in a vector.
     *
     * @param[in] data - Vector double vector containing data
     */
    static double CalcMean(const Vector<double> & data);

    /** @brief Calculate standard deviation of all elements in a vector.
     *
     * @param[in] data - Vector double vector containing data
     */
    static double CalcSD(const Vector<double> & data);

    /** @brief Calculate sample Pearson Correlation Coefficient of two double vectors of equal size.
     *
     * @param[in] data_a - Vector double vector containing data
     * @param[in] data_b - Vector double vector of the same size as data_a containing data
     */
    static double CalcsPCC(const Vector<double> & data_a, const Vector<double> & data_b);

    /** @brief Calculate Mean Absolute Devaition of all elements in a vector.
     *
     * @param[in] data - Vector double vector containing data
     */
    static double CalcMAD(const Vector<double> & data);

    /** @brief Retrieve correlatable data from a vector of objects for sPCC.
     *
     * @param[in] items - Items containing objects
     * @param[out] data_a - Vector to hold first kind of data that will be correlated
     * @param[out] data_b - Vector to hold second kind of data that will be correlated
     * @param[in] get_data_a - Pointer to member function of objects in items that will retrieve items to be put in data_a.
     * @param[in] get_data_b - Pointer to member function of objects in items that will retrieve items to be put in data_b.
     * @param[in] flag_val - Flag value to compare against for validity
     * @param[in] flag_comparison - Pointer to comparison function that will be used to compare against the flag. If true, will skip value: bool func(data, flag)
     */
    template <typename T, typename U>
    static void GetCorrelatableObjectData(const Vector<T> & items, Vector<U> & data_a,
                                          Vector<U> & data_b, U(T::*get_data_a)() const, U(T::*get_data_b)() const,
                                          U flag_val, bool(*flag_comparison)(U data,U flag))
    {

        for (int i{0}; i < items.Size(); i++)
        {
            if (flag_comparison((items[i].*get_data_a)(), flag_val) || flag_comparison((items[i].*get_data_b)(), flag_val))
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
