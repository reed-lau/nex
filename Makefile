all:nex

nex:nex.cc
	g++ $< -o $@ -O2 -std=c++14 -luv
