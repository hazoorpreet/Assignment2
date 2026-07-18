#ifndef MAP_H
#define MAP_H

#include <map>

template <typename KT, typename VT>
class Map {
public:
    Map();

    Map(const Map & other);

    Map operator=(const Map & other);

    const VT & operator[](const KT & key) const;

    VT & operator[](const KT & key);

    bool Find(const KT & key) const;

    bool Emplace(const KT & key, const VT & value);

    void Erase(const KT & key);

    void Clear();

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
