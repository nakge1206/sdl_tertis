.PHONY: run Main clean

run: Main
	@echo "Running program..."
	./main

Main: ./src/main.cpp
	@echo "Compiling main.cpp..."
	g++ ./src/main.cpp -I/Library/Frameworks/SDL2.framework/Headers \
	-F/Library/Frameworks -framework SDL2 -o main \
	-Wl,-rpath,/Library/Frameworks
	@echo "Compilation complete. Use './main' to execute."

clean:
	@echo "Cleaning up..."
	rm -f main
	@echo "Cleanup complete."