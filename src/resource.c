#include <raylib.h>
#include "resource.h"




Assets assets;



void load_assets()
{
  assets.w_pawn = LoadTexture("../assets/white-pawn.png");
  assets.w_rook = LoadTexture("../assets/white-rook.png");
  assets.w_knight = LoadTexture("../assets/white-knight.png");
  assets.w_bishop = LoadTexture("../assets/white-bishop.png");
  assets.w_queen = LoadTexture("../assets/white-queen.png");
  assets.w_king = LoadTexture("../assets/white-king.png");
  
  assets.b_pawn = LoadTexture("../assets/black-pawn.png");
  assets.b_rook = LoadTexture("../assets/black-rook.png");
  assets.b_knight = LoadTexture("../assets/black-knight.png");
  assets.b_bishop = LoadTexture("../assets/black-bishop.png");
  assets.b_queen = LoadTexture("../assets/black-queen.png");
  assets.b_king = LoadTexture("../assets/black-king.png");

  assets.board_background = LoadTexture("../assets/board-background.jpg");
}


void unload_assets()
{
  UnloadTexture(assets.w_pawn);
  UnloadTexture(assets.w_rook);
  UnloadTexture(assets.w_knight);
  UnloadTexture(assets.w_bishop);
  UnloadTexture(assets.w_queen);
  UnloadTexture(assets.w_king);
  
  UnloadTexture(assets.b_pawn);
  UnloadTexture(assets.b_rook);
  UnloadTexture(assets.b_knight);
  UnloadTexture(assets.b_bishop);
  UnloadTexture(assets.b_queen);
  UnloadTexture(assets.b_king);

  UnloadTexture(assets.board_background);
}
