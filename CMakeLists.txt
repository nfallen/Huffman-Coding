cmake_minimum_required(VERSION 2.8.2)

#Project name

project(hello)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Werror -std=c++11 -pthread")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

find_package(Boost 1.58 COMPONENTS filesystem REQUIRED)
find_package(Protobuf 3.4.1 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Generate the C++ code from the .proto files.
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS encoding.proto)

# Specifies the source code files needed to create the executable.
# The header files needed will be automatically detected.
add_executable(huffman huffman.cc encode_utils.cc freq_node.cc inner_node.cc char_node.cc ${PROTO_SRCS} ${PROTO_HDRS})

# Link all libraries 
target_link_libraries(huffman ${Boost_LIBRARIES})
target_link_libraries(huffman ${PROTOBUF_LIBRARIES})
target_link_libraries(huffman gtest_main)