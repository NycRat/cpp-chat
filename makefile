# all: compile link
# compile:
# 	g++ -I src/include -c Client.cpp
# link:
# 	g++ client.o -o client -L src/lib -l sfml-network


# all: compile link
# compile:
# 	g++ -I src/include -c Server.cpp
# link:
# 	g++ server.o -o server -L src/lib -l sfml-network

all: compile link
compile:
	g++ -I src/include -c clientwindow.cpp
link:
	g++ clientwindow.o -o clientwindow -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-main -l sfml-network