cmake_minimum_required (VERSION 3.22)

# Change project name
set (PROJECT_NAME server)

project (${PROJECT_NAME} C CXX)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.79.0 REQUIRED COMPONENTS log log_setup)
find_package(Threads)

# Folder where the Coverage module is
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Source files folder
set (SRC_DIR src)

# Header files folder
set (INCL_DIR include)

# Core Header files folder
set (CORE_DIR core)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall -Werror")

include_directories(${Boost_INCLUDE_DIRS}
                    /usr/include
                    ${INCL_DIR}
                    ${CORE_DIR})

link_directories(${Boost_LIBRARY_DIRS})
# Important: Include all source files on this list in the right order
set (SOURCE
    ${SRC_DIR}/main.cc
    ${SRC_DIR}/server.cc
    ${CORE_DIR}/orderbook.cc
)

link_directories(/usr/local/lib)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

# Add the executable for the program
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME}
                       ${Boost_LIBRARIES} 
                       pthread
                       Threads::Threads)
