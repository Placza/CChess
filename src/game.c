#include "game.h"
#include "utils.h"
#include <raylib.h>
#include <stdio.h>
#include "piece_moves.h"
#include "legal_moves.h"
#include "game_state.h"


/*
 *
 *
 * The game will interact with the enviorment using an API.
 * The API contains these elements:
 * - void select_piece(int x, int y)
 * - void make_move(int x, int y)
 * - bool has_selection()
 *
 * 
 * */



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
    .selected = 0,
    .state = GS_ONGOING,
    .w_promotion = W_BISHOP,
    .b_promotion = B_BISHOP,
    .w_king_moved = 0,
    .b_king_moved = 0,
    .r_w_rook_moved = 0,
    .l_w_rook_moved = 0,
    .r_b_rook_moved = 0,
    .l_b_rook_moved = 0
  };
}





bool select_piece(int x, int y)
{
  game.p_start_x = x;
  game.p_start_y = y;

  piece p = game.board[y][x];
  if (is_ally(p))
    check_legal_moves();

  return is_ally(p);
}


void deselect_piece()
{
  clear_cache();
}


void update_piece(int x, int y)
{
  game.p_end_x = x;
  game.p_end_y = y;

  move_piece();
  check_is_check();

  clear_cache();
}



bool has_selection()
{
  piece p = game.board[game.p_start_y][game.p_start_x];
  return is_ally(p);
}



bool is_legal_move(int x, int y)
{
  for (int i = 0; i < game.legal_moves_top; i++)
  {
    if (game.legal_moves[i][0] == x && game.legal_moves[i][1] == y)
      return 1;
  }
  return 0;
}



bool is_piece_selected(int x, int y)
{
  return game.p_start_x == x && game.p_start_y == y;
}


bool is_ally_piece(int x, int y)
{
  piece p = game.board[y][x];
  return is_ally(p);
}
 

void change_promotion(int p)
{
  switch (p) 
  {
    case 0:
      if (game.turn == 1) game.w_promotion = W_BISHOP;
      else game.b_promotion = B_BISHOP;
      break;
    case 1:
      if (game.turn == 1) game.w_promotion = W_ROOK;
      else game.b_promotion = B_ROOK;
      break;
    case 2:
      if (game.turn == 1) game.w_promotion = W_KNIGHT;
      else game.b_promotion = B_KNIGHT;
      break;
    case 3:
      if (game.turn == 1) game.w_promotion = W_QUEEN;
      else game.b_promotion = B_QUEEN;
      break;
    default:
      break;
  }
}


bool is_to_be_promoted()
{
  piece p = game.board[game.p_start_y][game.p_start_x];
  if (p == W_PAWN && game.p_start_y == 1 || p == B_PAWN && game.p_start_y == 6) return 1;
  return 0;
}
