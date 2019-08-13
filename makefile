CXX 	= g++
FLAGS 	= -std=c++11
LIB		= -ljsoncpp
PROGS	= main


all  :$(PROGS)

main: *.cpp
	 $(CXX) $(FLAGS) -o $@ $^ $(LIB)

clean:
	rm -f $(PROGS)