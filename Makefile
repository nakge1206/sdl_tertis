.PHONY: run Main clean

#src내부 파일 추가
SRC = ./src/main.cpp ./src/sdl/Window.cpp
OBJ = main #결과물 이름
CXX = g++
CXXFLAGS = -I/Library/Frameworks/SDL2.framework/Headers -I./src/sdl #SDL2 헤더파일 경로
LDFLAGS = -F/Library/Frameworks -framework SDL2 -Wl,-rpath,/Library/Frameworks #SDL 링커 폴더경로


run: Main
	@echo "프로그램 실행 중..."
	./$(OBJ)

Main: $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OBJ)
	
	

clean:
	@echo "초기화 중..."
	rm -f $(OBJ)
	@echo "초기화 완료."