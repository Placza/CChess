#include "game.h"
#include <stdio.h>




Game game;

void init_game(void)
{
  game = (Game){
    .board = {
      {B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK},
      {B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN},
      {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK}
    },
    .turn = 1,
    .state = GS_ONGOING,
    .w_captured = {0},
    .b_captured = {0},
    .w_captured_top = -1,
    .b_captured_top = -1,
  };
}




int move_piece(int x0, int y0, int x1, int y1)
{
  piece p0 = game.board[y0][x0];
  
  if (p0 == EMPTY) return -1;

  game.board[y1][x1] = p0;
  game.board[y0][x0] = EMPTY;
  
  return 1;  
}



void capture_piece(int color, piece p)
{
  if (color == 0)
  {
    game.b_captured_top++;
    game.b_captured[game.b_captured_top] = p;
  }
  else
  {
    game.w_captured_top++;
    game.w_captured[game.w_captured_top] = p;
  }
}



