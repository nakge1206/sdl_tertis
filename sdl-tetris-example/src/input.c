#include "input.h"
#include "definitions.h"
#include <SDL_keycode.h>

//키보드에서 눌린 키의 키 코드를 받아 토큰 반환
static int handle_key_down(SDL_Keycode key_code) {
  switch (key_code) {
  case SDLK_ESCAPE:
    return QUIT;
  case SDLK_LEFT:
  case SDLK_a:
    return LEFT;
  case SDLK_RIGHT:
  case SDLK_d:
    return RIGHT;
  case SDLK_UP:
  case SDLK_w:
    return ROTATE;
  case SDLK_DOWN:
  case SDLK_s:
    return SOFT_DROP;
  case SDLK_SPACE:
    return HARD_DROP;
  }
  return ANY_INPUT;
}

//SDL_Event를 활용해, SDL_QUIT가 받아졌으면 QUIT를, 키보드가 눌렸다면 해당 키보드의 반환값을 반환.
int listen_for_input(int game_over) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return QUIT;
    }
    if (event.type == SDL_KEYDOWN) {
      return handle_key_down(event.key.keysym.sym);
    }
  }

  return NO_INPUT;
}
