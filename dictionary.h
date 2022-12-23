#pragma once

#include <string>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <stdexcept>

#include <stdint.h>

typedef uint32_t key_t;

#define REALLOC_FILL_FACTOR             0.75
#define INITIAL_SIZE                    5
#define HASH_STRING_SHIFT_VALUE         5

#define _T                              template <typename K, typename T>

_T class Dictionary {
    public:
        Dictionary();
        void    add(K key, T value);
        void    remove(K key);
        T       get(K key);
        size_t  count() { return _elementsCount; }

        void    printDebug();

        T operator[] (K key);
    private:
        typedef std::pair<const K, T> valueType_t;
        typedef std::list<valueType_t> valueNodes_t;

        std::vector<valueNodes_t> arrValues;
        size_t _elementsCount = 0;

        key_t hash(std::string stringKey);
        key_t hash(size_t intKey) { return intKey % arrValues.size(); }

        double getFillFactor() { return (double)count() / arrValues.size(); }

        void reallocMemory();
        bool isNeedToReallocMemory();


};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



_T Dictionary<K, T>::Dictionary() {
    arrValues.resize(INITIAL_SIZE);
}


_T key_t Dictionary<K, T>::hash(std::string stringKey) {
    key_t hash = 0;

    for (int i = 0; i < stringKey.length(); ++i)
        hash = (hash << HASH_STRING_SHIFT_VALUE) - hash + stringKey.at(i);

    return hash % arrValues.size();
}


_T void Dictionary<K, T>::remove(K key) { 
    key_t index = hash(key);
    valueNodes_t& cellNodes = arrValues[index];

    if (cellNodes.empty())
        throw std::invalid_argument("Element <" + std::string(key) + "> not exists" );

    auto it = cellNodes.begin();
    for (; it != cellNodes.end(); it++) {
        if (it->first != key) continue;

        cellNodes.erase(it);
        return;
    }

    throw std::invalid_argument("Element <" + std::string(key) + "> not exists" );
}


_T void Dictionary<K, T>::add(K key, T value) {
    if (isNeedToReallocMemory())
        reallocMemory();

    key_t index = hash(key);
    valueNodes_t& cellNodes = arrValues[index];

    // Update value if key exists
    if (!cellNodes.empty()) {
        auto it = cellNodes.begin();
        for (; it != cellNodes.end(); it++) {
            if (it->first != key) continue;

            it->second = value;
            return;
        }
    } 

    cellNodes.push_back(std::make_pair(key, value));
    _elementsCount++;
}


_T void Dictionary<K, T>::reallocMemory() {
    std::vector<valueNodes_t> oldArr(arrValues);

    arrValues.clear();
    arrValues.resize(oldArr.size() * 2 + 1);

    _elementsCount = 0;

    for (int i = 0; i < oldArr.size(); i++) {
        valueNodes_t& cellNodes = oldArr[i];

        for (auto it = cellNodes.begin(); it != cellNodes.end(); it++) 
            add(it->first, it->second);
        
        cellNodes.clear();
    }

    oldArr.clear();
}


_T T Dictionary<K, T>::get(K key) {
    key_t index = hash(key);
    valueNodes_t& cellNodes = arrValues[index];

    if (cellNodes.empty())
        throw std::invalid_argument("Element <" + std::string(key) + "> not exists" );

    auto it = cellNodes.begin();
    for (; it != cellNodes.end(); it++) {
        if (it->first == key) return it->second;
    }

    throw std::invalid_argument("Element <" + std::string(key) + "> not exists" );
}


_T bool Dictionary<K, T>::isNeedToReallocMemory() {
    return getFillFactor() >= REALLOC_FILL_FACTOR;
}


_T void Dictionary<K, T>::printDebug() {
    std::cout << "Elements count: " << count() << "\n"
              << "Real size: " <<  arrValues.size() << "\n"
              << "Fill factor: " << getFillFactor() << "\n";
    for (int i = 0; i < arrValues.size(); i++) {
        std::cout << i << "; ";

        valueNodes_t& cellNodes = arrValues[i];

        for (auto it = cellNodes.begin(); it != cellNodes.end(); it++) {
            std::cout << "(" << it->first << ", " << it->second << ") ";
        }

        std::cout << std::endl;
    }
}

_T T Dictionary<K, T>::operator [] (K key) {
    return get(key);
}