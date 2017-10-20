cmake_minimum_required(VERSION 2.8)

#Project name

project(hello)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Werror -std=c++11 -pthread")

find_package(Boost 1.58 COMPONENTS filesystem REQUIRED)
find_package(Protobuf 3.4.1 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS encoding.proto)
add_executable(huffman huffman.cc encode_utils.cc freq_node.cc inner_node.cc char_node.cc ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(huffman ${Boost_LIBRARIES})
target_link_libraries(huffman ${PROTOBUF_LIBRARIES})
