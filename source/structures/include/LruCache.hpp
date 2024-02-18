#pragma once

#include <unordered_map>
#include <list>
#include <cstdint>
#include <optional>

namespace SK
{
    template<typename K, typename V>
    struct Node
    {
        K key;
        V value;
    };

    template<typename K, typename V>
    class LruCache {
    public:
        LruCache(const uint32_t& capacity)
            : capacity(capacity)
        {
        }
        
        std::optional<V> get(K key)
        {
            auto itr = cache.find(key);

            if(itr == cache.end())
                return std::nullopt;
            
            // Move found node to the tail of list
            node_list.splice(node_list.end(), node_list, itr->second);
            return itr->second->value;
        }

        void insert(K key, V value)
        {
            auto result = get(key);

            // If key already exist in the cache, then just move to tail of list
            if(result.has_value())
            {
                cache[key]->value = value;
                return;
            }

            // Erase LRU node from cache and list when exceeding capacity
            if(cache.size() == capacity)
            {
                cache.erase(node_list.front().key);
                node_list.pop_front();
            }

            // Insert into list and update cache
            node_list.emplace_back(key, value);
            cache[key] = std::prev(node_list.end());
        }

    private:
        std::unordered_map<K, typename std::list<Node<K, V>>::iterator> cache;
        uint32_t capacity;
        std::list<Node<K, V>> node_list;
    };
}

