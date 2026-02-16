#include <raylib.h>
#include "render.h"
#include "game.h"
#include "input.h"
#include <stdio.h>
#include "resource.h"



#define CELL_SIZE 63
#define FRAME_SIZE 30


static void render_background()
{
  DrawTextureEx(assets.board_background, (Vector2){0, 0}, 0, 2.f, WHITE);
}


static void render_pattern()
{
  for(int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if ((i + j) % 2 == 0)
        DrawRectangle(j * CELL_SIZE + FRAME_SIZE, i * CELL_SIZE + FRAME_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN);
      else
        DrawRectangle(j * CELL_SIZE + FRAME_SIZE, i * CELL_SIZE + FRAME_SIZE, CELL_SIZE, CELL_SIZE, WHITE);  
    }
  }
}


static void render_frame()
{

  DrawRectangleLinesEx((Rectangle){FRAME_SIZE - 6, FRAME_SIZE - 6, 8 * CELL_SIZE + 12, 8 * CELL_SIZE + 12}, 6.0f, BLACK);  
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
      render_piece(p, j * CELL_SIZE + FRAME_SIZE, i * CELL_SIZE + FRAME_SIZE, 0.5f, WHITE);
    }
  }

}



static void render_selection()
{
  if (get_input_state() == INPUT_SELECTED)
    DrawRectangle(game.p_start_x * CELL_SIZE + FRAME_SIZE, game.p_start_y * CELL_SIZE + FRAME_SIZE, CELL_SIZE, CELL_SIZE, ORANGE);
}



static void render_legal_moves()
{
  for (int i = 0; i < game.legal_moves_top; i++)
  {
    DrawRectangle(game.legal_moves[i][0] * CELL_SIZE + FRAME_SIZE, game.legal_moves[i][1] * CELL_SIZE + FRAME_SIZE, CELL_SIZE, CELL_SIZE, (Color){0, 100, 255, 200});
  }
}


static void render_captured_pieces()
{
  for (int i = 0; i < game.w_captured_top; i++)
  {
    piece p = game.w_captured[i];
    render_piece(p, i * 20 + FRAME_SIZE, CELL_SIZE * 8 + FRAME_SIZE, 0.2f, WHITE);
  }
  for (int i = 0; i < game.b_captured_top; i++)
  {
    piece p = game.b_captured[i];
    render_piece(p, i * 20 + FRAME_SIZE, 0, 0.2f, WHITE);
  }
}



static void render_promotion()
{
  if (game.is_promotion)
    render_piece(game.w_promotion, game.promotion_x * CELL_SIZE + FRAME_SIZE, game.promotion_y * CELL_SIZE + FRAME_SIZE, 0.5f, (Color){255, 255, 255, 100});
}



void render_board()
{
  BeginDrawing();
  
    ClearBackground(RAYWHITE);
    render_background();
    render_pattern();
    render_frame();
    render_selection();
    render_legal_moves();
    render_pieces();
    render_promotion();
    render_captured_pieces();

  EndDrawing();
}
