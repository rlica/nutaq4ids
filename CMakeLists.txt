cmake_minimum_required(VERSION 3.16)

project(nutaq4ids)

find_package(ROOT REQUIRED)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        ${ROOT_INCLUDE_DIRS}
)
add_executable(n4i src/nutaq4ids.cc)

target_compile_features(n4i PRIVATE cxx_std_17)
target_link_libraries(n4i PRIVATE ${ROOT_LIBRARIES})
