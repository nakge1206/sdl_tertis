# SDL2_tetris
SDL2를 이용한 테트리스 대전게임

## 프로젝트 소개
C++를 이용하여 테트리스 대전게임을 구현.
게임 룰은 https://namu.wiki/w/테트리스/용어 해당링크의 가이드라인 룰을 따른다.

## 사용된 서브파티프로그램 정보 (25.01.06)
SDL2 : 2.30.11
https://github.com/libsdl-org/SDL/releases/tag/release-2.30.11

SDL2-image : 2.8.4
https://github.com/libsdl-org/SDL_image/releases

SDL2-ttl : 2.24.0
https://github.com/libsdl-org/SDL_ttf/releases

**1.8 todo : example 구조 파악 -> 반쯤 한 거 같음**

**1.9 todo : 윈도우, 렌더 설정 완료, 테트리미노 구현**

fuckfuckfuckfuck
1.16 현재상황 : 윈도우 창 크기에 따라 동적으로 폰트 및 크기를 바꾸려고 했는데 rect의 크기는
바꾸는걸 구현하였고, 폰트크기도 바꿀 수 있어보이는데, 하다보니까 메모리 할당이 너무 자주 일어나서 포기하기로함.

지금 뭐가 문제인지 종료할때 segmentation fault가 뜨는거 보니 소멸자에서 메모리 반환을 제대로 못한거 같음.

지금까지 이렇게 했으니까 화면크기 조정은 계속 하고 싶긴한데, 보니까 SDL_RendererSetLogicalSize
라고 하는 함수를 찾음. 기능은 실제 창을 조정해도 논리적인 화면크기를 설정하고 그에 따라 비율이 자동으로
변경된다는 점.
+
SDL_SetWindowMinimumSize(window, x, y); 이거도 참고해보면 좋을 듯 함

일단 다시 해야하는거는 화면비율은 960x540 (qHD 16:9)로 가정하고, LogicalSize로 설정하도록 할거임.

todo. 메인메뉴 및 클릭 기능 구현



