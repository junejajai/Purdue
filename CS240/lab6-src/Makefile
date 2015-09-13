
CXX = g++ -fPIC

all: HashTableVoidTest IRCServer IRCServer1

HashTableVoidTest: HashTableVoidTest.cc HashTableVoid.cc
	g++ -g -o HashTableVoidTest HashTableVoidTest.cc HashTableVoid.cc

IRCServer: IRCServer.cc
	g++ -g -o IRCServer IRCServer.cc HashTableVoid.cc
	git add -A  >> .local.git.out
	git commit -a -m "Make IRCServer" >> .local.git.out

IRCServer1: IRCServer1.cc
	g++ -g -o IRCServer1 IRCServer1.cc HashTableVoid.cc
clean:
	rm -f *.out
	rm -f *.o HashTableVoidTest IRCServer


