#include <list>
#include <functional>
#include <iostream>

const size_t SET_SIZE = 10000;

template <class KeyType>
class HashNode
{
public:
    HashNode() = default;
    void add_key(const KeyType &key)
    {
        if (!has_key(key))
        {
            keys.push_back(key);
        }
    }
    void remove_key(const KeyType &key)
    {
        keys.remove(key);
    }
    std::list<KeyType> get_keys() const
    {
        return keys;
    }
    bool has_key(const KeyType &key)
    {
        return std::find(keys.begin(), keys.end(), key) != keys.end();
    }
    size_t get_key_id(const KeyType &key)
    {
        auto it = keys.begin();
        for (size_t id = 0; it != keys.end(); ++it, id++)
        {
            if (*it == key)
            {
                return id;
            }
        }
        throw std::invalid_argument("Unknown key");
    }
    KeyType get_key_by_id(size_t id) const
    {
        auto it = keys.begin();
        for (int i = 0; i < id; ++it)
            ;
        return *it;
    }

private:
    std::list<KeyType> keys{};
};

template <class KeyType>
class HashSet
{
public:
    HashSet() = default;
    class iterator
    {
    public:
        friend class HashSet;
        iterator &operator++()
        {
            if (obj.nodes[hash].get_keys().size() >= index_in_list)
            {
                for (size_t current_hash = hash + 1; current_hash < SET_SIZE; current_hash++)
                {
                    if (obj.nodes[current_hash].get_keys().size() != 0)
                    {
                        hash = current_hash;
                        index_in_list = 0;
                        return *this;
                    }
                }
                hash = SET_SIZE;
                index_in_list = 0;
                return *this;
            }
            else
            {
                index_in_list++;
                return *this;
            }
        }
        KeyType operator*()
        {
            return obj.nodes[hash].get_key_by_id(index_in_list);
        }
        bool operator==(const iterator &other)
        {
            return hash == other.hash && index_in_list == other.index_in_list;
        }
        bool operator!=(const iterator &other)
        {
            return !(*this == other);
        }

    private:
        iterator(size_t hash, size_t index_in_list, HashSet const &obj) : hash{hash}, index_in_list{index_in_list}, obj{obj} {}
        HashSet const &obj;
        size_t hash{};
        size_t index_in_list{};
    };
    iterator begin()
    {
        for (size_t current_hash = 0; current_hash < SET_SIZE; current_hash++)
        {
            if (nodes[current_hash].get_keys().size() != 0)
            {
                return iterator(current_hash, 0, *this);
            }
        }
        return end();
    }
    iterator end()
    {
        return iterator(SET_SIZE, 0, *this);
    }
    iterator find(const KeyType &key)
    {
        size_t hash = my_hash(key);
        return nodes[hash].has_key(key) ? iterator(hash, nodes[hash].get_key_id(key), *this) : end();
    }
    void insert(const KeyType &key)
    {
        size_t hash = my_hash(key);
        nodes[hash].add_key(key);
    }
    void erase(const KeyType &key)
    {
        size_t hash = my_hash(key);
        nodes[hash].remove_key(key);
    }

private:
    size_t my_hash(const KeyType &key)
    {
        return std::hash<KeyType>{}(key) % SET_SIZE;
    }
    HashNode<KeyType> nodes[SET_SIZE]{};
};

int main()
{
    HashSet<std::string> set;
    set.insert("10");
    set.insert("50");
    set.insert("alabala");
    std::cout << (set.find("10") != set.end()) << " "
              << (set.find("20") != set.end()) << " "
              << (set.find("alabala") != set.end()) << " "
              << std::endl;
    for(auto it = set.begin(); it!=set.end(); ++it)
    {
        std::cout<<*it<<std::endl;
    }
    return 0;
}