FLAG = "-std=c++11"
BIN = main
OBJ = tree.o main.o mystring.o avl.o 
HEAD = util.h avl.h rb_tree.h skip_list.h hash_map.h
$(BIN):$(OBJ)
	g++ -o $(BIN) $(OBJ) $(FLAG)
$OBJ:$(HEAD)
main.o:main.cpp
	g++ -c main.cpp $(FLAG)
tree.o:tree.cpp
mystring.o:mystring.cpp
avl.o:avl.cpp
clean:
	rm  $(BIN) $(OBJ)
