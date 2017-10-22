set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Werror -std=c++11 -pthread")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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