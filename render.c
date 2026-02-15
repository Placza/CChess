#include <raylib.h>
#include "render.h"
#include "game.h"
#include "input.h"
#include <stdio.h>


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
}


void render_pattern()
{

  ClearBackground(RAYWHITE);

  for(int i = 0; i < 63; i++)
  {
    for (int j = 0; j < 63; j++)
    {
      if ((i + j) % 2 == 0)
        DrawRectangle(j * 63, i * 63, 63, 63, DARKGREEN);
      else
        DrawRectangle(j * 63, i * 63, 63, 63, WHITE);  
    }
  }

}



void render_pieces()
{

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      switch (game.board[i][j]) 
      {
        case W_KNIGHT:
          DrawTextureEx(assets.w_knight, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case W_PAWN:
          DrawTextureEx(assets.w_pawn, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case W_ROOK:
          DrawTextureEx(assets.w_rook, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case W_BISHOP:
          DrawTextureEx(assets.w_bishop, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case W_QUEEN:
          DrawTextureEx(assets.w_queen, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case W_KING:
          DrawTextureEx(assets.w_king, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;



        case B_KNIGHT:
          DrawTextureEx(assets.b_knight, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case B_PAWN:
          DrawTextureEx(assets.b_pawn, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case B_ROOK:
          DrawTextureEx(assets.b_rook, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case B_BISHOP:
          DrawTextureEx(assets.b_bishop, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case B_QUEEN:
          DrawTextureEx(assets.b_queen, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        case B_KING:
          DrawTextureEx(assets.b_king, (Vector2){j * 63, i * 63}, 0, 0.5f, WHITE);
          break;

        default:
          break;
      }
    }
  }

}



void render_selection()
{
  if (get_input_state() == INPUT_SELECTED)
    DrawRectangle(game.p_start_x * 63, game.p_start_y * 63, 63, 63, ORANGE);
}



void render_legal_moves()
{
  for (int i = 0; i < game.legal_moves_top; i++)
  {
    DrawRectangle(game.legal_moves[i][0] * 63, game.legal_moves[i][1] * 63, 63, 63, (Color){0, 100, 255, 200});
  }
}



void render_board()
{
  BeginDrawing();
  
    render_pattern();
    render_selection();
    render_legal_moves();
    render_pieces();

  EndDrawing();
}
