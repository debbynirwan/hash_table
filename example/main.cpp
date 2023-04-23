#include <cassert>
#include <iostream>
#include <string>
#include <time.h>
#include <unordered_map>

#include "hash_table.hpp"

void profile_rehash(int n)
{
    clock_t start, end;
    double cpu_time_used;
    HashTable<int, int> table;
    std::unordered_map<int, int> uTable;

    for (int i = 0; i < n; i++) {
        start = clock();
        uTable.insert({ i, i * 5 });
        end = clock();
        cpu_time_used = end - start;
        std::cout << "unordered_map i: " << i << " time: " << cpu_time_used
                  << " size: " << uTable.bucket_count() << std::endl;
    }

    for (int i = 0; i < n; i++) {
        start = clock();
        table.Insert(i, i * 5);
        end = clock();
        cpu_time_used = end - start;
        std::cout << "hash_table i: " << i << " time: " << cpu_time_used
                  << " size: " << table.BucketCount() << std::endl;
    }
}

int main(int argc, char** argv)
{
    clock_t start, end;
    double cpu_time_used;

    HashTable<int, int> table;
    std::unordered_map<int, int> uTable;
    int j = 0;

    if (argc > 1) {
        j = atoi(argv[1]);
        if (argc > 2) {
            profile_rehash(j);
            return 0;
        }
    }

    uTable.reserve(static_cast<double>(j / uTable.max_load_factor()) + 1);
    table.Reserve(static_cast<double>(j / table.MaxLoadFactor()) + 1);

    start = clock();
    for (int i = 0; i < j; i++) {
        uTable.insert({ i, i * 5 });
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "unordered_map insert() cpu time for " << j << " elements: " << cpu_time_used
              << " us" << std::endl;

    start = clock();
    for (int i = 0; i < j; i++) {
        table.Insert(i, i * 5);
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "HashTable insert() cpu time for " << j << " elements: " << cpu_time_used << " us"
              << std::endl;

    start = clock();
    for (int i = 0; i < j; i++) {
        auto x = uTable.at(i);
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "unordered_map at() cpu time for " << j << " elements: " << cpu_time_used << " us"
              << std::endl;

    start = clock();
    for (int i = 0; i < j; i++) {
        auto x = table.At(i);
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "HashTable at() cpu time for " << j << " elements: " << cpu_time_used << " us"
              << std::endl;

    start = clock();
    for (int i = 0; i < j; i++) {
        uTable.erase(i);
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "unordered_map erase() cpu time for " << j << " elements: " << cpu_time_used
              << " us" << std::endl;

    start = clock();
    for (int i = 0; i < j; i++) {
        table.Remove(i);
    }
    end = clock();
    cpu_time_used = end - start;

    std::cout << "HashTable erase() cpu time for " << j << " elements: " << cpu_time_used << " us"
              << std::endl;

    return 0;
}
