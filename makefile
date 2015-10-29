FLAG = "-std=c++11"
BIN = main
OBJ = tree.o main.o mystring.o
$(BIN):$(OBJ)
	g++ -o $(BIN) $(OBJ) $(FLAG)
$OBJ:util.h
main.o:main.cpp
	g++ -c main.cpp $(FLAG)
tree.o:tree.cpp
mystring.o:mystring.cpp
clean:
	rm  $(BIN) $(OBJ)
