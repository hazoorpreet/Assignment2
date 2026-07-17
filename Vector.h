#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

/** @brief Vector class to contain and handle an arbitrary amount of objects.
 *
 * @author Hazoorpreet Singh
 * @date 07/07/2026
 */
template <typename T> class Vector
{
public:
    /** @brief Create empty Vector
     *
     */
    Vector();

    /** @brief Create vector with zero-initialized values
     *
     * @param[in] size Number of values
     * @exception std::invalid_argument Thrown when invalid input (any value less than 0) is entered.
     */
    Vector(int size);

    /** @brief Vector copy constructor
     *
     * @param[in] other Other vector of same type to copy from.
     */
    Vector(const Vector<T> &other);

    /** @brief Vector copy assignment
     *
     * @param[in] other Other vector of same type to copy from.
     * @return Self as a deep copy of other vector
     */
    Vector<T> &operator=(const Vector<T> &other);

    /** @brief Vector Destructor
     *
     */
    virtual ~Vector();

    /** @brief Retrieve number of elements in Vector
     *
     */
    int Size() const;

    /** @brief Retrieve mutable reference to vector element
     *
     * @param[in] index Index of element to retrieve from 0 to the number of elements minus one
     * @exception std::out_of_range Thrown if value selected outside of vector size
     * @return Mutable reference to vector element
     */
    T &operator[](int index);

    /** @brief Retrieve constant reference to vector element (for constant vectors)
     *
     * @param[in] index Index of element to retrieve from 0 to the number of elements minus one
     * @exception std::out_of_range Thrown if value selected outside of vector size
     * @return Constant reference to vector element
     */
    const T &operator[](int index) const;

    /** @brief Delete a value from the vector
     *
     * @param[in] index Index of element to pop from 0 to the number of elements minus one
     */
    void Delete(int index);

    /** @brief Clear vector of all values
     *
     */
    void Clear();

    /** @brief Insert a value at a specific index, pushing everything else forward.
     *
     * @param[in] index Index of value to be inserted. Must be between 0 and current size.
     * @param[in] data Data to be entered into the index.
     * @return True if successfully inserted, false if unsuccessful due to insufficient space.
     */
    bool Insert(int index, const T &data);

private:
    std::vector<T> m_vector;
};

template <typename T> Vector<T>::Vector() : m_vector(0) {}

template <typename T> Vector<T>::Vector(int size) : m_vector(size) {}

template <typename T>
Vector<T>::Vector(const Vector<T> &other): m_vector(other.m_vector) {}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    m_vector = other.m_vector;
    return *this;
}

template <typename T> int Vector<T>::Size() const
{
    return m_vector.size();
}

template <typename T> Vector<T>::~Vector() {}

template <typename T> T &Vector<T>::operator[](int index)
{
    return m_vector[index];
}

template <typename T> const T &Vector<T>::operator[](int index) const
{
    return m_vector[index];
}

template <typename T> void Vector<T>::Delete(int index)
{
    m_vector.erase(m_vector.begin() + index);
}

template <typename T> void Vector<T>::Clear()
{
    m_vector.clear();
}

template <typename T> bool Vector<T>::Insert(int index, const T &data)
{
    if (index > Size() or index < 0) {
        return false;
    } else if (index == Size()) {
        m_vector.push_back(data);
    } else {
        m_vector.insert(m_vector.begin() + index, data);
    }
    return true;
}

#endif // VECTOR_H
