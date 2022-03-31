#target: dependency list
#	rule to build target from dependencies

all: main alloc prov

main: alloc.cpp prov-rep.cpp
	g++ alloc.cpp -o prov-rep.cpp -o main

alloc: alloc.cpp
	g++ alloc.cpp -o alloc

prov: prov-rep.cpp
	g++ prov-rep.cpp -o prov

clean:
	rm -f main alloc prov
