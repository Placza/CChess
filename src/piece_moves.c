#include <raylib.h>
#include "piece_moves.h"
#include "utils.h"
#include "game.h"
#include <stdio.h>



static void add_valid_move(int x, int y)
{
  if (x > 7 || x < 0 || y > 7 || y < 0) return;
  game.valid_moves[game.valid_moves_top][0] = x;
  game.valid_moves[game.valid_moves_top][1] = y;
  game.valid_moves_top++;
}



static void check_valid_moves_pawn(int color)
{
  piece above = game.board[game.p_start_y - color][game.p_start_x];
  piece twice_above = game.board[game.p_start_y - 2*color][game.p_start_x];
  piece top_right = game.board[game.p_start_y - color][game.p_start_x + color];
  piece top_left = game.board[game.p_start_y - color][game.p_start_x - color];

  if (above == 0)
    add_valid_move(game.p_start_x, game.p_start_y - color);

  if (color == 1 && game.p_start_y == 6 || color == -1 && game.p_start_y == 1)
  {
    if (above == 0 && twice_above == 0)
      add_valid_move(game.p_start_x, game.p_start_y - 2*color);
  }

  if (is_enemy(top_right))
    add_valid_move(game.p_start_x + color, game.p_start_y - color); 
   
  if (is_enemy(top_left))
    add_valid_move(game.p_start_x - color, game.p_start_y - color); 
}




static void check_valid_moves_rook()
{
  for (int i = 1; i <= 7 - game.p_start_x; i++)
  {
    piece right = game.board[game.p_start_y][game.p_start_x + i];
    if (is_ally(right)) break;
    if (is_enemy(right))
    {
      add_valid_move(game.p_start_x + i, game.p_start_y);
      break;
    }
    add_valid_move(game.p_start_x + i, game.p_start_y);
  }

  for (int i = 1; i <= game.p_start_y; i++)
  {
    piece up = game.board[game.p_start_y - i][game.p_start_x];
    if (is_ally(up)) break;
    if (is_enemy(up))
    {
      add_valid_move(game.p_start_x, game.p_start_y - i);
      break;
    }
    add_valid_move(game.p_start_x, game.p_start_y - i);
  }

  for (int i = 1; i <= game.p_start_x; i++)
  {
    piece left = game.board[game.p_start_y][game.p_start_x - i];
    if (is_ally(left)) break;
    if (is_enemy(left))
    {
      add_valid_move(game.p_start_x - i, game.p_start_y);
      break;
    }
    add_valid_move(game.p_start_x - i, game.p_start_y);
  }

  for (int i = 1; i <= 7 - game.p_start_y; i++)
  {
    piece down = game.board[game.p_start_y + i][game.p_start_x];
    if (is_ally(down)) break;
    if (is_enemy(down))
    {
      add_valid_move(game.p_start_x, game.p_start_y + i);
      break;
    }
    add_valid_move(game.p_start_x, game.p_start_y + i);
  }
}





static void check_valid_moves_bishop()
{
  int top_r = min(7 - game.p_start_x, game.p_start_y);
  for (int i = 1; i <= top_r; i++)
  {
    piece top_r = game.board[game.p_start_y - i][game.p_start_x + i];
    if (is_ally(top_r)) break;
    if (is_enemy(top_r))
    {
      add_valid_move(game.p_start_x + i, game.p_start_y - i);
      break;
    }
    add_valid_move(game.p_start_x + i, game.p_start_y - i);
  }


  int bottom_r = min(7 - game.p_start_x, 7 - game.p_start_y);
  for (int i = 1; i <= bottom_r; i++)
  {
    piece bottom_r = game.board[game.p_start_y + i][game.p_start_x + i];
    if (is_ally(bottom_r)) break;
    if (is_enemy(bottom_r))
    {
      add_valid_move(game.p_start_x + i, game.p_start_y + i);
      break;
    }
    add_valid_move(game.p_start_x + i, game.p_start_y + i);
  }


  int top_l = min(game.p_start_x, game.p_start_y);
  for (int i = 1; i <= top_l; i++)
  {
    piece top_l = game.board[game.p_start_y - i][game.p_start_x - i];
    if (is_ally(top_l)) break;
    if (is_enemy(top_l))
    {
      add_valid_move(game.p_start_x - i, game.p_start_y - i);
      break;
    }
    add_valid_move(game.p_start_x - i, game.p_start_y - i);
  }


  int bottom_l = min(game.p_start_x, 7 - game.p_start_y);
  for (int i = 1; i <= bottom_l; i++)
  {
    piece bottom_l = game.board[game.p_start_y + i][game.p_start_x - i];
    if (is_ally(bottom_l)) break;
    if (is_enemy(bottom_l))
    {
      add_valid_move(game.p_start_x - i, game.p_start_y + i);
      break;
    }
    add_valid_move(game.p_start_x - i, game.p_start_y + i);
  }
}



static void check_valid_moves_knight()
{
  piece p;
  int pos_x;
  int pos_y;

  pos_x = game.p_start_x + 1;
  pos_y = game.p_start_y - 2;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);
      

  pos_x = game.p_start_x - 1;
  pos_y = game.p_start_y - 2;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);




  pos_x = game.p_start_x + 2;
  pos_y = game.p_start_y - 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x + 2;
  pos_y = game.p_start_y + 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);




  pos_x = game.p_start_x - 1;
  pos_y = game.p_start_y + 2;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x + 1;
  pos_y = game.p_start_y + 2;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);




  pos_x = game.p_start_x - 2;
  pos_y = game.p_start_y - 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x - 2;
  pos_y = game.p_start_y + 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);
}




static void check_valid_moves_queen()
{
  check_valid_moves_rook();
  check_valid_moves_bishop();
}





void check_valid_moves_king()
{
  piece p;
  int pos_x;
  int pos_y;

  if 
  (
      !game.w_king_moved 
  &&  !game.r_w_rook_moved
  &&  game.board[7][5] == 0
  &&  game.board[7][6] == 0
  )
    add_valid_move(6, 7);
  
  if 
  (
      !game.w_king_moved 
  &&  !game.l_w_rook_moved
  &&  game.board[7][3] == 0
  &&  game.board[7][2] == 0
  &&  game.board[7][1] == 0
  )
    add_valid_move(2, 7);


  if 
  (
      !game.b_king_moved 
  &&  !game.r_b_rook_moved
  &&  game.board[0][5] == 0
  &&  game.board[0][6] == 0
  )
    add_valid_move(6, 0);
  

  if 
  (
      !game.b_king_moved 
  &&  !game.l_b_rook_moved
  &&  game.board[0][3] == 0
  &&  game.board[0][2] == 0
  &&  game.board[0][1] == 0
  )
    add_valid_move(2, 0);



  pos_x = game.p_start_x;
  pos_y = game.p_start_y - 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x + 1;
  pos_y = game.p_start_y - 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x + 1;
  pos_y = game.p_start_y;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x + 1;
  pos_y = game.p_start_y + 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x;
  pos_y = game.p_start_y + 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x - 1;
  pos_y = game.p_start_y + 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x - 1;
  pos_y = game.p_start_y;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);


  pos_x = game.p_start_x - 1;
  pos_y = game.p_start_y - 1;
  p = game.board[pos_y][pos_x];
  if (!is_ally(p))
    add_valid_move(pos_x, pos_y);
}




void check_valid_moves(piece selected)
{

  switch (selected)
  {
    case W_PAWN:
      check_valid_moves_pawn(1);
      break;

    case B_PAWN:
      check_valid_moves_pawn(-1);
      break;

    case W_ROOK:
      check_valid_moves_rook();
      break;

    case B_ROOK:
      check_valid_moves_rook();
      break;

    case W_BISHOP:
      check_valid_moves_bishop();
      break;

    case B_BISHOP:
      check_valid_moves_bishop();
      break;

    case W_KNIGHT:
      check_valid_moves_knight();
      break;

    case B_KNIGHT:
      check_valid_moves_knight();
      break;

    case W_QUEEN:
      check_valid_moves_queen();
      break;

    case B_QUEEN:
      check_valid_moves_queen();
      break;

    case W_KING:
      check_valid_moves_king();
      break;

    case B_KING:
      check_valid_moves_king();
      break;

    default:
      break;
  }
}
