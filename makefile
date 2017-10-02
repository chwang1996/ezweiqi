all:
	g++ -g -std=gnu++11 *.cpp -o play_game -pthread
clean:
	rm play_game
