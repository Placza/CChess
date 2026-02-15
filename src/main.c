#include <raylib.h>
#include "game.h"
#include "input.h"
#include "render.h"


int main(void)
{

  InitWindow(WINDOW_H, WINDOW_W, "Cchess");
  SetTargetFPS(60);

  load_assets();

  init_game();

  while (!WindowShouldClose())  
  {
    render_board();
    handle_input();
  }

  CloseWindow();

  return 0;
}
