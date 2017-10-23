set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Werror -std=c++11 -pthread")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost 1.58 COMPONENTS filesystem REQUIRED)
find_package(Protobuf 3.4.1 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories("${gtest_SOURCE_DIR}/include")

# Generate the C++ code from the .proto files.
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS encoding.proto)

# Specifies the source code files needed to create the executable.
# The header files needed will be automatically detected.
add_executable(char_node_test char_node_test.cc char_node.cc freq_node.cc ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(inner_node_test inner_node_test.cc inner_node.cc char_node.cc freq_node.cc ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(huffman huffman.cc encode_decode.cc freq_node.cc inner_node.cc char_node.cc ${PROTO_SRCS} ${PROTO_HDRS})

#Link libraries to test executable
target_link_libraries(char_node_test gtest_main)
target_link_libraries(inner_node_test gtest_main)
target_link_libraries(char_node_test ${PROTOBUF_LIBRARIES})
target_link_libraries(inner_node_test ${PROTOBUF_LIBRARIES})

# Execute tests
add_test(NAME char_node COMMAND ../bin/char_node_test)
add_test(NAME inner_node COMMAND ../bin/inner_node_test)

# Link all libraries 
target_link_libraries(huffman ${Boost_LIBRARIES})
target_link_libraries(huffman ${PROTOBUF_LIBRARIES})
target_link_libraries(huffman gtest_main)