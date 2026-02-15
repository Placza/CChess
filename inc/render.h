#include <raylib.h>


#ifndef RENDER_H
#define RENDER_H
  


typedef struct
{
  Texture2D w_pawn;
  Texture2D w_knight;
  Texture2D w_rook;
  Texture2D w_bishop;
  Texture2D w_queen;
  Texture2D w_king;

  Texture2D b_pawn;
  Texture2D b_knight;
  Texture2D b_rook;
  Texture2D b_bishop;
  Texture2D b_queen;
  Texture2D b_king;
} Assets;



extern Assets assets;


void load_assets();


void render_board();



#endif
