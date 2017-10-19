CPPFLAGS = -Wall -g -Werror -std=c++11
LLIBFLAGS = -L/usr/local/Cellar/boost/1.65.1/
LDLIBS = -lboost_filesystem -lboost_system

huffman: huffman.o encode_utils.o freq_node.o inner_node.o char_node.o
	g++ $(LDFLAGS) -g -o huffman huffman.o encode_utils.o freq_node.o inner_node.o char_node.o $(LDLIBS)

tests: tests.o encode_utils.o freq_node.o inner_node.o char_node.o
	g++ $(LDFLAGS) -g -o tests tests.o encode_utils.o freq_node.o inner_node.o char_node.o $(LDLIBS)

encode_utils.o: encode_utils.h encode_utils.cc freq_node.h inner_node.h char_node.h
	g++ $(CPPFLAGS) -c encode_utils.cc

tests.o: tests.cc freq_node.h inner_node.h char_node.h
	g++ $(CPPFLAGS) -c tests.cc

huffman.o: huffman.cc encode_utils.h freq_node.h
	g++ $(CPPFLAGS) -c huffman.cc

inner_node.o: freq_node.h inner_node.h inner_node.cc
	g++ $(CPPFLAGS) -c inner_node.cc

char_node.o: freq_node.h char_node.h char_node.cc
	g++ $(CPPFLAGS) -c char_node.cc

freq_node.o: freq_node.h freq_node.cc
	g++ $(CPPFLAGS) -c freq_node.cc

clean: 
	rm -f huffman tests encode_utils.o tests.o huffman.o inner_node.o char_node.o freq_node.o