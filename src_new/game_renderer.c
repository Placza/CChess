#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "resource.h"
#include "game_renderer.h"



#define CELL_SIZE 63
#define FRAME_SIZE 30



static void render_pattern()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if ((i + j) % 2 == 0)
        DrawRectangle(
            j * CELL_SIZE + FRAME_SIZE, 
            i * CELL_SIZE + FRAME_SIZE,
            CELL_SIZE, CELL_SIZE,
            DARKGREEN);
      else
        DrawRectangle(
            j * CELL_SIZE + FRAME_SIZE,
            i * CELL_SIZE + FRAME_SIZE,
            CELL_SIZE, CELL_SIZE,
            WHITE);
    }
  }
}




static void render_frame()
{
  DrawRectangleLinesEx(
      (Rectangle){FRAME_SIZE - 6, FRAME_SIZE - 6, 8 * CELL_SIZE + 12, 8 * CELL_SIZE + 12},
      6.0f,
      BLACK);
}




static void render_piece(piece p, int x, int y, float scale, Color color)
{
  switch (p)
  {
    case W_KNIGHT:
      DrawTextureEx(assets.w_knight, (Vector2){x, y}, 0, scale, color);
      break;
    
    case W_PAWN:
      DrawTextureEx(assets.w_pawn, (Vector2){x, y}, 0, scale, color);
      break;
    
    case W_ROOK:
      DrawTextureEx(assets.w_rook, (Vector2){x, y}, 0, scale, color);
      break;

    case W_BISHOP:
      DrawTextureEx(assets.w_bishop, (Vector2){x, y}, 0, scale, color);
      break;
    
    case W_QUEEN:
      DrawTextureEx(assets.w_queen, (Vector2){x, y}, 0, scale, color);
      break;
    
    case W_KING:
      DrawTextureEx(assets.w_king, (Vector2){x, y}, 0, scale, color);
      break;


    case B_KNIGHT:
      DrawTextureEx(assets.b_knight, (Vector2){x, y}, 0, scale, color);
      break;

    case B_PAWN:
      DrawTextureEx(assets.b_pawn, (Vector2){x, y}, 0, scale, color);
      break;
      
    case B_ROOK:
      DrawTextureEx(assets.b_rook, (Vector2){x, y}, 0, scale, color);
      break;

    case B_BISHOP:
      DrawTextureEx(assets.b_bishop, (Vector2){x, y}, 0, scale, color);
      break;

    case B_QUEEN:
      DrawTextureEx(assets.b_queen, (Vector2){x, y}, 0, scale, color);
      break;

    case B_KING:
      DrawTextureEx(assets.b_king, (Vector2){x, y}, 0, scale, color);
      break;

    default:
      break;
  }
}




static void render_pieces()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      piece p = game.board[i][j];
      render_piece(
          p,
          j * CELL_SIZE + FRAME_SIZE,
          i * CELL_SIZE + FRAME_SIZE,
          0.5f,
          WHITE);
    } 
  }
}




void render_board()
{
  BeginDrawing();

    ClearBackground(RAYWHITE);
    render_pattern();
    render_frame();
    render_pieces();

  EndDrawing();
}

