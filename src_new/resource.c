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

  assets.board_background = LoadTexture("../assets/board-background.png");
}
