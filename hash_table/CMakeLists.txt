add_library(hash_table INTERFACE)

target_include_directories(hash_table
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hash_table>
)

set_target_properties(hash_table PROPERTIES PUBLIC_HEADER "hash_table.h;hash_table.hpp")

include(GNUInstallDirs)

install(TARGETS hash_table
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hash_table)
