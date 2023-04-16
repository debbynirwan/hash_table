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

#include "hash_table.h"
#include <stdexcept>

template <class Key, class Value>
HashTable<Key, Value>::HashTable()
    : m_table()
    , m_loadFactor(DEFAULT_LOAD_FACTOR)
    , m_hashFunc()
    , m_size(0)
{
}

template <class Key, class Value> HashTable<Key, Value>::~HashTable()
{
    for (int i = 0; i < m_table.size(); i++) {
        Node* current_node = m_table[i];
        Node* tmp_node = nullptr;

        while (current_node != nullptr) {
            tmp_node = current_node;
            current_node = current_node->next;
            delete tmp_node;
        }
    }
}

template <class Key, class Value> Value HashTable<Key, Value>::At(const Key& key)
{
    if (m_size == 0)
        throw std::out_of_range("table is empty");

    std::size_t hash_code = m_hashFunc(key);
    std::size_t index = HashCodeToIndex(hash_code, BucketCount());
    Node* node = m_table[index];

    while (node != nullptr) {
        if (node->key == key)
            break;
        node = node->next;
    }

    if (node == nullptr)
        throw std::out_of_range("invalid key");

    return node->value;
}

template <class Key, class Value>
void HashTable<Key, Value>::Insert(const Key& key, const Value& value)
{
    Node* node = PrepareInsertion(key);

    if (node != nullptr) {
        node->value = value;
        return;
    }

    std::size_t hash_code = m_hashFunc(key);
    std::size_t index = HashCodeToIndex(hash_code, BucketCount());
    node = m_table[index];

    Node* newNode = new Node { key, value, hash_code, nullptr };

    if (node == nullptr) {
        m_table[index] = newNode;
    } else {
        while (node->next != nullptr)
            node = node->next;
        node->next = newNode;
    }
    m_size++;
}

template <class Key, class Value> void HashTable<Key, Value>::Remove(const Key& key)
{
    if (m_size == 0)
        return;

    std::size_t hash_code = m_hashFunc(key);
    std::size_t index = HashCodeToIndex(hash_code, BucketCount());
    Node* node = m_table[index];
    Node* prev_node = nullptr;

    while (node != nullptr) {
        if (node->key == key) {
            if (prev_node != nullptr)
                prev_node->next = node->next;
            else
                m_table[index] = node->next;

            delete node;
            break;
        }
        prev_node = node;
        node = node->next;
    }
}

template <class Key, class Value> std::size_t HashTable<Key, Value>::Size() const { return m_size; }

template <class Key, class Value> void HashTable<Key, Value>::SetLoadFactor(double loadFactor)
{
    if (loadFactor > 0)
        m_loadFactor = loadFactor;
}

template <class Key, class Value>
typename HashTable<Key, Value>::Node* HashTable<Key, Value>::PrepareInsertion(const Key& key)
{
    if (m_size != 0) {
        std::size_t hash_code = m_hashFunc(key);
        std::size_t index = HashCodeToIndex(hash_code, BucketCount());
        Node* node = m_table[index];

        while (node != nullptr) {
            if (node->key == key)
                return node;
            node = node->next;
        }
    }

    if (m_size + 1 > BucketCount() * m_loadFactor || BucketCount() == 0) {
        std::size_t size = (BucketCount() == 0) ? 1 : 2 * (m_size + 1) / m_loadFactor;
        Rehash(size);
    }

    return nullptr;
}

template <class Key, class Value>
std::size_t HashTable<Key, Value>::HashCodeToIndex(const std::size_t hash_code,
                                                   const std::size_t bucket_count)
{
    return (hash_code < bucket_count) ? hash_code : hash_code % bucket_count;
}

template <class Key, class Value> bool HashTable<Key, Value>::PowerOfTwo(const std::size_t num)
{
    return ((num & (num - 1)) == 0);
}

template <class Key, class Value> std::size_t HashTable<Key, Value>::BucketCount() const
{
    return m_table.size();
}

template <class Key, class Value> void HashTable<Key, Value>::Rehash(const std::size_t n)
{
    std::vector<Node*> newTable(n);
    for (int i = 0; i < n; i++)
        newTable[i] = nullptr;

    if (m_table.size() != 0) {
        for (int i = 0; i < BucketCount(); i++) {
            Node* current_node = m_table[i];

            while (current_node != nullptr) {
                Node* tmp_node = current_node;
                current_node = current_node->next;
                tmp_node->next = nullptr;

                std::size_t index = HashCodeToIndex(tmp_node->hash_code, n);

                Node* current_slot_node = newTable[index];
                if (current_slot_node == nullptr) {
                    newTable[index] = tmp_node;
                } else {
                    while (current_slot_node->next != nullptr)
                        current_slot_node = current_slot_node->next;
                    current_slot_node->next = tmp_node;
                }
            }
        }
    }

    m_table = newTable;
}
