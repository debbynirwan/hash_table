/*
 * Copyright 2023 Debby Nirwan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <cstdint>
#include <vector>

template <class Key, class Value> class HashTable {
    struct Node {
        Key key;
        Value value;
        std::size_t hash_code;
        Node* next;
    };

public:
    HashTable();
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);
    HashTable(HashTable&& other);
    HashTable& operator=(HashTable&& other);
    ~HashTable();

    Value At(const Key& key);
    void Insert(const Key& key, const Value& value);
    void Remove(const Key& key);
    std::size_t Size() const;
    void SetMaxLoadFactor(double loadFactor);
    double MaxLoadFactor() const;
    inline std::size_t BucketCount() const;
    void Reserve(const std::size_t n);

private:
    Node* PrepareInsertion(const Key& key);
    std::size_t HashCodeToIndex(const std::size_t hash_code, const std::size_t bucket_count);
    static bool PowerOfTwo(const std::size_t num);
    void Rehash(const std::size_t n);
    void ClearAll();
    void CopyTable(const HashTable& other);

    std::vector<Node*> m_table;
    double m_maxLoadFactor;
    std::hash<Key> m_hashFunc;
    std::size_t m_size;
    static constexpr double DEFAULT_LOAD_FACTOR = 0.75d;
};
