#ifndef MAP_H
#define MAP_H

#include <map>
#include "Vector.h"

/** @brief Minimal but complete Map class wrapper
 *
 * @author Hazoorpreet Singh
 * @date 21/07/2026
 */
template <typename KT, typename VT>
class Map {
public:

    /** @brief Create empty constructor
     *
     */
    Map();

    /** @brief Create Map from another Map
     *
     * @param[in] other - Other map to copy
     */
    Map(const Map & other);

    /** @brief Copy Map from another Map
     *
     * @param[in] other - Other map to copy
     */
    Map operator=(const Map & other);

    /** @brief Read item from map by key
     *
     * @param[in] key - Key to retrieve item
     */
    const VT & operator[](const KT & key) const;

    /** @brief Modify item from map by key
     *
     * @param[in] key - Key to retrieve item
     */
    VT & operator[](const KT & key);

    /** @brief Check if key exists in map
     *
     * @param[in] key - Key to check for
     * @retval True - Key found
     * @retval False - Key not found
     */
    bool Find(const KT & key) const;

    /** @brief Emplace a new key into the map
     *
     * @param[in] key - Key to emplace value
     * @param[in] Value to emplace
     * @retval True - Value successfully emplaced at key
     * @retval False - Value could not be emplaced at key as key already exists
     */
    bool Emplace(const KT & key, const VT & value);

    /** @brief Erase key/value from map
     *
     * @param[in] key - Key to erase
     */
    void Erase(const KT & key);

    /** @brief Clear map
     *
     */
    void Clear();

    /** @brief Virtual destructor of map
     *
     */
    virtual ~Map();

private:
    std::map<KT,VT> m_map;
};

template <typename KT, typename VT>
Map<KT,VT>::Map(): m_map{} {}

template <typename KT, typename VT>
Map<KT,VT>::Map(const Map & other): m_map{other.m_map} {}

template <typename KT, typename VT>
Map<KT,VT> Map<KT,VT>::operator=(const Map & other) {
    m_map = other.m_map;
    return *this;
}

template <typename KT, typename VT>
const VT & Map<KT,VT>::operator[](const KT & key) const {
    return m_map.at(key);
}

template <typename KT, typename VT>
VT & Map<KT,VT>::operator[](const KT & key) {
    return m_map.at(key);
}

template <typename KT, typename VT>
bool Map<KT,VT>::Find(const KT & key) const {
    return m_map.find(key) != m_map.end();
}

template <typename KT, typename VT>
bool Map<KT,VT>::Emplace(const KT & key, const VT & value) {
    return m_map.emplace(key, value).second;
}

template <typename KT, typename VT>
void Map<KT,VT>::Erase(const KT & key) {
    m_map.erase(key);
}

template <typename KT, typename VT>
void Map<KT,VT>::Clear() {
    m_map.clear();
}

template <typename KT, typename VT>
Map<KT,VT>::~Map() {}

#endif // MAP_H
