#pragma once

#include <unordered_map>
#include <list>
#include <cstdint>

template<typename K, typename V>
class Node;

template<typename K, typename V>
class LRUCache {
public:
    LRUCache(const uint32_t& capacity);
    
    V get(K key);
    void insert(K key, V value);

private:
    std::unordered_map<K, typename std::list<Node<K, V>>::iterator> cache;
    uint32_t capacity;
    std::list<Node<K, V>> node_list;
};