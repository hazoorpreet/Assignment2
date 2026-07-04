#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

/** @brief Vector class to contain and handle an arbitrary amount of objects.
 *
 * @author Hazoorpreet Singh
 * @date 07/06/2026
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
     * @param[in] n Number of values
     * @exception std::invalid_argument Thrown when invalid input (any value less than 0) is entered.
     */
    Vector(int n);

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
     * @retval True for successful deletion, False if non-existant index
     */
    bool Delete(int index);

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
    int m_size;
    T *m_elements;
    int m_allocation;
    static const int MIN_ALLOC = 10;

    /** @brief Resize according to elements needed to support
     *
     * @param[in] new_size New size to be set
     * @retval True - Sufficient space exists for new value
     * @retval False - Insufficient space for new value
     */
    bool Resize(int new_size);
};

template <typename T> Vector<T>::Vector() : Vector(0) {}

template <typename T> Vector<T>::Vector(int n) : m_size(n), m_elements(nullptr), m_allocation(MIN_ALLOC)
{
    if (n < 0)
    {
        throw std::invalid_argument("Size must be positive or 0");
    }

    // allocation size
    m_allocation = MIN_ALLOC;
    while (m_size >= (m_allocation / 2))
    {
        m_allocation *= 2;
    }

    // Create array
    m_elements = new T[m_allocation];

    // Confirm array created
    if (m_elements == nullptr)
    {
        m_allocation = 0;
        m_size = 0;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
    : m_size(other.m_size), m_elements(nullptr), m_allocation(other.m_allocation)
{
    m_elements = new T[m_allocation];

    for (int i = 0; i < m_size; i++)
    {
        m_elements[i] = other[i];
    }
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (m_elements != nullptr)
    {
        delete[] m_elements;
    }
    m_size = other.m_size;
    m_allocation = other.m_allocation;

    if (other.m_elements != nullptr)
    {
        m_elements = new T[m_allocation];
    }
    else
    {
        m_elements = nullptr;
    }

    for (int i = 0; i < m_size; i++)
    {
        m_elements[i] = other[i];
    }
    return *this;
}

template <typename T> int Vector<T>::Size() const
{
    return m_size;
}

template <typename T> Vector<T>::~Vector()
{
    if (m_elements != nullptr)
    {
        delete[] m_elements;
    }
}

template <typename T> T &Vector<T>::operator[](int index)
{
    if (index >= m_size || index < 0)
    {
        throw std::out_of_range(
            "Index failed: "
            "Query must be in range 0 to Vector<T>::Size() - 1 & "
            "will not work when vector is empty.");
    }

    return m_elements[index];
}

template <typename T> const T &Vector<T>::operator[](int index) const
{
    if (index >= m_size || index < 0)
    {
        throw std::out_of_range(
            "Index failed: "
            "Query must be in range 0 to Vector<T>::Size() - 1 & "
            "will not work when vector is empty.");
    }

    return m_elements[index];
}

template <typename T> bool Vector<T>::Delete(int index)
{
    if (index >= Size() || index < 0)
    {
        return false;
    }

    m_size--;
    for (int i{index}; index < m_size; i++)
    {
        m_elements[i] = m_elements[i + 1];
    }
    return true;
}

template <typename T> void Vector<T>::Clear()
{
    if (m_elements != nullptr)
    {
        delete[] m_elements;
        m_elements = nullptr;
    }
    m_size = 0;
    m_allocation = 0;
}

template <typename T> bool Vector<T>::Insert(int index, const T &data)
{

    if (index < 0 || index > m_size)
    {
        return false;
    }

    if (!Resize(m_size + 1))
    {
        return false;
    }

    for (int i{m_size - 2}; i >= index; i--)
    {
        m_elements[i + 1] = m_elements[i];
    }

    m_elements[index] = data;
    return true;
}

template <typename T> bool Vector<T>::Resize(int new_size)
{
    // if allocation is sufficient, simply return
    if (new_size <= (m_allocation / 2))
    {
        m_size = new_size;
        return true;
    }

    // otherwise, resize
    int temp_allocation;
    if (m_allocation)
    {
        temp_allocation = m_allocation;
    }
    else
    {
        temp_allocation = MIN_ALLOC;
    }

    while(new_size >= (temp_allocation / 2))
    {
        temp_allocation *= 2;
    }

    // resize & confirm
    T * temp_elements{nullptr};
    temp_elements = new T[temp_allocation];
    if (temp_elements == nullptr)
    {
        if (new_size <= m_allocation)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // copy elements
    for (int i{0}; i < m_size; i++)
    {
        temp_elements[i] = m_elements[i];
    }

    // set
    if (m_elements != nullptr)
    {
        delete[] m_elements;
    }
    m_size = new_size;
    m_elements = temp_elements;
    m_allocation = temp_allocation;
    return true;
}

#endif // VECTOR_H
