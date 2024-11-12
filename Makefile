MAIN = src/main.cpp

LIB = src/lib/server-socket-handler.cpp

HEADER = src/lib/headers/server-socket-handler.hpp

compile:
	g++ $(MAIN) $(LIB) $(HEADER) -o a.out -pthread