cmake_minimum_required(VERSION 2.8)

#Project name

project(hello)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Boost 1.58 COMPONENTS filesystem REQUIRED)

if (NOT Boost_FOUND)
	message(FATAL_ERROR "boost 1.58 not found")
endif()

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(huffman huffman.cc encode_utils.cc freq_node.cc inner_node.cc char_node.cc)
	target_link_libraries(huffman ${Boost_LIBRARIES})
endif()