#include <raylib.h>
#include <stdio.h>
#include "game.h"
#include "game_renderer.h"
#include "resource.h"


int main(void)
{

  InitWindow(WINDOW_H, WINDOW_W, "Cchess");
  SetTargetFPS(60);

  load_assets();

  init_game();

  while (!WindowShouldClose())  
  {
    render_board();
    //handle_input();
  }

  CloseWindow();
  //unload_assets();

  return 0;
}
