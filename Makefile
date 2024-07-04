.DEFAULT_GOAL := test-eg
.PHONY: clean eg test-eg

eg: clean
	g++ -fdiagnostics-path-format=inline-events -std=c++20 -o eg main.cpp rt.cpp startfile.cpp -DDEBUG_MODE

test-eg: eg
	./eg

clean:
	clear
	rm -f eg
