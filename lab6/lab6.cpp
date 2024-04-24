#include <iostream>
#include <vector>
#include <memory>
#include <string_view>

template<typename T>
struct BucketNode {
    T value;
    std::string_view key;
    std::unique_ptr<BucketNode> next;

    BucketNode(std::string_view key_, T value_)
        : value(value_), key(key_), next(nullptr) {}
};

template<typename T>
struct HashTable {
    std::vector<std::unique_ptr<BucketNode<T>>> buckets;
    size_t (*hashFunc)(std::string_view key);

    HashTable(size_t capacity, size_t (*hashFunction)(std::string_view))
        : buckets(capacity), hashFunc(hashFunction) {}
};

template<typename T>
HashTable<T> createHashTable(size_t capacity, size_t (*hashFunction)(std::string_view)) {
    return HashTable<T>(capacity, hashFunction);
}

template<typename T>
size_t computeIndex(const HashTable<T>& table, std::string_view key) {
    size_t hash = table.hashFunc(key);
    size_t index = hash % table.buckets.size();
    return index;
}

template<typename T>
T* add(HashTable<T>& table, std::string_view key, T value) {
    size_t index = computeIndex(table, key);
    auto node = std::make_unique<BucketNode<T>>(key, value);
    if (table.buckets[index]) {
        node->next = std::move(table.buckets[index]);
    }
    table.buckets[index] = std::move(node);
    return &(table.buckets[index]->value);
}

template<typename T>
T* find(HashTable<T>& table, std::string_view key) {
    size_t index = computeIndex(table, key);
    BucketNode<T>* currentNode = table.buckets[index].get();
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return &currentNode->value;
        }
        currentNode = currentNode->next.get();
    }
    return nullptr;
}

template<typename T>
bool remove(HashTable<T>& table, std::string_view key) {
    size_t index = computeIndex(table, key);
    auto& bucket = table.buckets[index];
    BucketNode<T>* current = bucket.get();
    BucketNode<T>* previous = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                bucket = std::move(current->next);
            } else {
                previous->next = std::move(current->next);
            }
            return true;
        }
        previous = current;
        current = current->next.get();
    }
    return false;
}

// Hash function example
size_t simpleHash(std::string_view key) {
    size_t hash = 0;
    for (char c : key) {
        hash = 31 * hash + c;
    }
    return hash;
}

int main() {
    auto table = createHashTable<int>(10, simpleHash);

    add(table, "key1", 10);
    add(table, "key2", 20);
    add(table, "key1", 30);

    std::cout << "Value at key1: " << *find(table, "key1") << std::endl;  // Output: 30
    std::cout << "Value at key2: " << *find(table, "key2") << std::endl;  // Output: 20

    remove(table, "key1");
    std::cout << "Value at key1 after removal: " << (find(table, "key1") ? std::to_string(*find(table, "key1")) : "not found") << std::endl;  // Output: not found

    return 0;
}
