Includes = ./includes
CXX = g++
CFLAGS = -std=c++11 -g -lboost_serialization
OutputFileName= HuffMan.out
# Libs=#whatever libraries you need to provide to g++
HuffmanZip: FileHandler.o  HuffmanTree.o HuffmanZip.o
	$(CXX) $(CFLAGS) -o HuffmanZip HuffmanZip.o FileHandler.o HuffmanTree.o

HuffmanZip.o:HuffmanZip.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o HuffmanZip.o HuffmanZip.cpp

HuffmanTree.o: HuffmanTree.cpp 
	$(CXX) $(CFLAGS) -I $(Includes) -c -o HuffmanTree.o HuffmanTree.cpp 

FileHandler.o: FileHandler.cpp
	$(CXX) $(CFLAGS) -I $(Includes) -c -o FileHandler.o FileHandler.cpp
clean:
	rm *.o
runtests:
	$(CXX) ./test/sampleTest.cpp -DSTAND_ALONE -lboost_unit_test_framework -o tests
