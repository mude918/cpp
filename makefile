FLAG = "-std=c++11"
OBJ = tree
$(OBJ):tree.o
	g++ -o tree tree.o $(FLAG)
tree.o:tree.cpp
	g++ -c tree.cpp
clean:
	rm  tree.o tree
