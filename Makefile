MAIN = src/main.cpp

LIB = src/lib/server.cpp

HEADER = src/lib/headers/server.hpp

compile:
	g++ $(MAIN) $(LIB) $(HEADER) -o a.out -pthread