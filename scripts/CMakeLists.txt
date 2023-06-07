find_package(pybind11 REQUIRED)
find_package(Python3 REQUIRED)

pybind11_add_module(hash_table_cpp hash_table.cpp)

target_link_libraries(hash_table_cpp PRIVATE
                    hash_table)

include(GNUInstallDirs)

install(TARGETS hash_table_cpp
    COMPONENT python
    RUNTIME DESTINATION "${Python3_SITEARCH}"
    LIBRARY DESTINATION "${Python3_SITEARCH}"
    ARCHIVE DESTINATION "${Python3_SITEARCH}")
