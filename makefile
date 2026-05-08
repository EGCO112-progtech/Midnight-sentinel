all: compile
compile: main.cpp
	g++ main.cpp AlertList.cpp BaseEvent.cpp Disaster.cpp ForestManager.cpp Mission.cpp Project.cpp -o game.exe
run: compile
	./game.exe
clean: main
	rm -f game.exe