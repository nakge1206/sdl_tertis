#include "definitions.h"
#include "game.h"
#include <time.h>

#ifdef __EMSCRIPTEN__
void run_loop() { game_loop(); }
#endif

int main(int argc, char **argv) {
#ifndef __EMSCRIPTEN__
  srand(time(NULL)); // seed the random number generator
#endif

  //init_game(game.c) 함수 호출. 실패하면 오류구문 출력
  if (init_game() != 0) {
    SDL_LogError(0, "Failed to start game\n");
    return 1;
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(run_loop, 0, 1);
#else
  //game_loop(game.c) 함수 호출 후, 1(게임종료)이면 루프탈출, -1이면 오류출력, 0이면 루프진행.
  while (1) {
    int res = game_loop();
    if (res != 0) {
      if (res < 0) {
        SDL_LogError(0, "예기치 못한 오류 발생\n");
      }
      break;
    }
  }
#endif

  //terminate_game(game.c, 게임리소스반환) 호출.
  if (terminate_game() != 0) {
    SDL_LogError(0, "종료과정에서 문제발생\n");
  };

  return 0;
}
