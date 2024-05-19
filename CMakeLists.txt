CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(test_task)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
include(cmake/build_prefix.cmake)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 20)

SET(APP_NAME ${PROJECT_NAME})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(JSON_PROJECT_PATH CACHE STRING "Path to nlohmann/json directory.")
LIST(APPEND CMAKE_PREFIX_PATH ${JSON_PROJECT_PATH})

find_package(json REQUIRED)
include_directories(${JSON_INCLUDE_DIRS})

SET(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${JSON_LIBRARIES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
