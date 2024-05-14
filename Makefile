build:
	g++ -std=c++17 ./*.cpp -lSDL2 -lSDL2_gfx -o breakout

run:
	./breakout

clean:
	rm breakout
