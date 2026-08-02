#include "Vector.h"
#include "VectorDataOperations.h"
#include <iostream>
#include <iomanip>

// Custom class only used for testing
class DoublePair
{
public:
    DoublePair(): m_a{0}, m_b{0} {};
    DoublePair(double a, double b): m_a{a}, m_b{b} {};
    double GetA() const
    {
        return m_a;
    };
    double GetB() const
    {
        return m_b;
    };
    void SetA(double a)
    {
        m_a = a;
    };
    void SetB(double b)
    {
        m_b = b;
    };
private:
    double m_a;
    double m_b;
};

int main ()
{
    std::cout << std::fixed << std::setprecision(2);
    Vector<double> vec{};
    vec.Insert(vec.Size(), 5);
    vec.Insert(vec.Size(), 10);
    vec.Insert(vec.Size(), 15);
    vec.Insert(vec.Size(), 20);
    vec.Insert(vec.Size(), 25);
    vec.Insert(vec.Size(), 35);

    std::cout << "Test 1: Test Total function\n"
              << "Total: " << VectorDataOperations::CalcTotal(vec) << "\n\n";

    std::cout << "Test 2: Test Mean function\n"
              << "Total: " << VectorDataOperations::CalcMean(vec) << "\n\n";

    std::cout << "Test 3: Test Standard Deviation function\n"
              << "Total: " << VectorDataOperations::CalcSD(vec) << "\n\n";

    std::cout << "Test 4: Test Mean Average Deviation function\n"
              << "Total: " << VectorDataOperations::CalcMAD(vec) << "\n\n";


    std::cout << "Test 5: Retrieve items from vector of objects, ignoring values that are flagged.\n";

    Vector<DoublePair> dpvec{};
    dpvec.Insert(dpvec.Size(), {5,8});
    dpvec.Insert(dpvec.Size(), {10,4});
    dpvec.Insert(dpvec.Size(), {15,15});
    dpvec.Insert(dpvec.Size(), {20,18});
    dpvec.Insert(dpvec.Size(), {25,40});
    dpvec.Insert(dpvec.Size(), {35,35});
    dpvec.Insert(dpvec.Size(), {35,-4});
    vec.Clear();
    Vector<double> vec2{};
    bool(*min_val_comparison)(double,double)
    {
        [](double data, double flag) -> bool {return data < flag;}
    };
    VectorDataOperations::GetCorrelatableObjectData<DoublePair,double>(dpvec,vec,vec2,&DoublePair::GetA,&DoublePair::GetB,0,min_val_comparison);
    std::cout << "Vector 1 Size: " << vec.Size() << '\n';
    std::cout << "Vector 2 Size: " << vec2.Size() << '\n';
    for (int i{0}; i < vec.Size(); i++)
    {
        std::cout << '(' << vec[i] << ',' << vec2[i] << ")\n";
    }
    std::cout << "\n\n";

    std::cout << "Test 6: Test sample Pearson Correlation Coefficient\n"
              << "sPCC: " << VectorDataOperations::CalcsPCC(vec, vec2) << '\n';
    return 0;
}
