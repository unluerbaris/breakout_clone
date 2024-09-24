build:
	g++ -std=c++17 ./*.cpp -lSDL2 -lSDL2_image -o breakout

run:
	./breakout

clean:
	rm breakout
