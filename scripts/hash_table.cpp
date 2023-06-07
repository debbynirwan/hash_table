#include "hash_table.hpp"
#include <unordered_map>
#include <pybind11/pybind11.h>
#include <time.h>

namespace py = pybind11;
using HashTableInt = HashTable<int, int>;
using HashTableIntDouble = HashTable<int, double>;
using unordered_mapInt = std::unordered_map<int, int>;

struct HashTableProfileInsertResults {
    HashTableIntDouble hash_table_time;
    HashTableIntDouble unordered_map_time;
};

HashTableProfileInsertResults ProfileInsert(const std::size_t n)
{
    clock_t start, end;
    double cpu_time_used;
    HashTableInt hash_table;
    unordered_mapInt unordered_map;
    HashTableProfileInsertResults result;

    for (std::size_t i = 0; i < n; i++) {
        start = clock();
        unordered_map.insert({ i, i * 5 });
        end = clock();
        cpu_time_used = end - start;
        result.unordered_map_time.Insert(i, cpu_time_used);
    }

    for (std::size_t i = 0; i < n; i++) {
        start = clock();
        hash_table.Insert(i, i * 5);
        end = clock();
        cpu_time_used = end - start;
        result.hash_table_time.Insert(i, cpu_time_used);
    }

    return result;
}

double MeasureInsert(HashTableInt& hash_table, const std::size_t n)
{
    clock_t start, end;

    start = clock();
    for (std::size_t i = 0; i < n; i++) {
        hash_table.Insert(i, i * 5);
    }
    end = clock();

    return (end - start);
}

double MeasureAt(HashTableInt& hash_table)
{
    clock_t start, end;
    int x;

    start = clock();
    for (std::size_t i = 0; i < hash_table.Size(); i++) {
        x = hash_table.At(i);
    }
    end = clock();

    x++;

    return (end - start);
}

double MeasureRemove(HashTableInt& hash_table, const std::size_t n)
{
    clock_t start, end;

    start = clock();
    for (std::size_t i = 0; i < n; i++) {
        hash_table.Remove(i);
    }
    end = clock();

    return (end - start);
}

double MeasureInsert(unordered_mapInt& unordered_map, const std::size_t n)
{
    clock_t start, end;

    start = clock();
    for (std::size_t i = 0; i < n; i++) {
        unordered_map.insert({ i, i * 5 });
    }
    end = clock();

    return (end - start);
}

double MeasureAt(unordered_mapInt& unordered_map)
{
    clock_t start, end;
    int x;

    start = clock();
    for (std::size_t i = 0; i < unordered_map.size(); i++) {
        x = unordered_map.at(i);
    }
    end = clock();

    x++;

    return (end - start);
}

double MeasureRemove(unordered_mapInt& unordered_map, const std::size_t n)
{
    clock_t start, end;

    start = clock();
    for (std::size_t i = 0; i < n; i++) {
        unordered_map.erase(i);
    }
    end = clock();

    return (end - start);
}

PYBIND11_MODULE(hash_table_cpp, m)
{
    py::class_<HashTableInt>(m, "HashTable")
        .def(py::init())
        .def("at", &HashTableInt::At)
        .def("insert", &HashTableInt::Insert)
        .def("size", &HashTableInt::Size)
        .def("remove", &HashTableInt::Remove);

    py::class_<HashTableIntDouble>(m, "HashTableIntDouble")
        .def(py::init())
        .def("at", &HashTableIntDouble::At)
        .def("insert", &HashTableIntDouble::Insert)
        .def("size", &HashTableIntDouble::Size)
        .def("remove", &HashTableIntDouble::Remove);

    py::class_<unordered_mapInt>(m, "unordered_map").def(py::init());

    py::class_<HashTableProfileInsertResults>(m, "HashTableProfileInsertResults")
        .def(py::init())
        .def_readwrite("hash_table_time", &HashTableProfileInsertResults::hash_table_time)
        .def_readwrite("unordered_map_time", &HashTableProfileInsertResults::unordered_map_time);

    m.def("profile_insert",
          static_cast<HashTableProfileInsertResults (*)(const std::size_t)>(&ProfileInsert));

    m.def("measure_insert", static_cast<double (*)(HashTableInt&, const std::size_t)>(&MeasureInsert));
    m.def("measure_insert", static_cast<double (*)(unordered_mapInt&, const std::size_t)>(&MeasureInsert));

    m.def("measure_at", static_cast<double (*)(HashTableInt&)>(&MeasureAt));
    m.def("measure_at", static_cast<double (*)(unordered_mapInt&)>(&MeasureAt));

    m.def("measure_remove", static_cast<double (*)(HashTableInt&, const std::size_t)>(&MeasureRemove));
    m.def("measure_remove", static_cast<double (*)(unordered_mapInt&, const std::size_t)>(&MeasureRemove));
}
