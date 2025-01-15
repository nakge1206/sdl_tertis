.PHONY: run Main clean

#소스파일 경로
SRC = ./src/main.cpp ./src/system/Window.cpp ./src/system/menu/MenuButton.cpp \
./src/system/menu/Particle.cpp \
./src/system/menu/TotalMenu.cpp ./src/system/sdl/SDL_font.cpp
#HDR = ./src/sdl/menuSample.h ./src/sdl/window_menu.h
#HDR = ./src/Menu/MenuButton.h ./src/sdl/Particle.h
OBJ = main #결과물 이름

#컴파일러, 플래그
CXX = g++

CXXFLAGS = -I/Library/Frameworks/SDL2.framework/Headers \
		-I/Library/Frameworks/SDL2_ttf.framework/Headers \
		-I./src/sdl #SDL2 헤더파일 경로

LDFLAGS = -F/Library/Frameworks \
		-framework SDL2 -framework SDL2_ttf -lm -Wl,-rpath,/Library/Frameworks #SDL 링커 폴더경로


run: Main
	@echo "프로그램 실행 중..."
	./$(OBJ)

Main: $(SRC) $(HDR)
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OBJ)
	
	

clean:
	@echo "초기화 중..."
	rm -f $(OBJ)
	@echo "초기화 완료."