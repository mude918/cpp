FLAG = "-std=c++11"
BIN = main
OBJ = tree.o main.o
$(BIN):$(OBJ)
	g++ -o $(BIN) $(OBJ)  $(FLAG)
$OBJ:util.h
main.o:main.cpp
tree.o:tree.cpp
clean:
	rm  $(BIN) $(OBJ)
