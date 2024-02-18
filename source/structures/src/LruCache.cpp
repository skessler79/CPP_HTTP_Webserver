
#include "structures/include/LruCache.hpp"

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
    
    V get(K key) {
        if(!cache.contains(key))
            return -1;
        
        // Move found node to the tail of list
        auto itr = cache[key];
        node_list.splice(node_list.end(), node_list, itr);

        return itr->value;
    }
    
    void insert(K key, V value) {
        // If key already exist in the cache, then just move to tail of list
        if(get(key) != -1)
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