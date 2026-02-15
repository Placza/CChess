#include "legal_moves.h"
#include "game.h"
#include "piece_moves.h"
#include <stdio.h>
#include "utils.h"


static void simulate_piece(int new_x, int new_y);
int is_check();
int is_checkmate();



void check_legal_moves()
{
  piece selected = game.board[game.p_start_y][game.p_start_x];

  check_valid_moves(selected);

  for (int i = 0; i < game.valid_moves_top; i++)
  {
    int new_x = game.valid_moves[i][0];
    int new_y = game.valid_moves[i][1];
    simulate_piece(new_x, new_y);
  }
}




static void add_legal_moves(int x, int y)
{
  game.legal_moves[game.legal_moves_top][0] = x;
  game.legal_moves[game.legal_moves_top][1] = y;
  game.legal_moves_top++;
}





static void simulate_piece(int new_x, int new_y)
{
  piece p = game.board[new_y][new_x];

  game.board[new_y][new_x] = game.board[game.p_start_y][game.p_start_x];
  game.board[game.p_start_y][game.p_start_x] = 0;

  if (!is_check())
    add_legal_moves(new_x, new_y);

  game.board[game.p_start_y][game.p_start_x] = game.board[new_y][new_x];
  game.board[new_y][new_x] = p;
}






int is_checkmate()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      piece p = game.board[i][j];
      if (is_ally(p))
      {
        clear_cache();
        game.p_start_x = j;
        game.p_start_y = i;
        check_legal_moves(j, i);
        if (game.legal_moves_top > 0) return 0; 
      }
    }
  }
  return 1;
}





static void find_king(int* x, int* y)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if 
      (
          game.turn == 1 
      &&  game.board[i][j] == W_KING
      ||
          game.turn == 0
      &&  game.board[i][j] == B_KING
      )
      {
        *x = j;
        *y = i;
        return;
      }
    }
  }
}




int is_check()
{
  int king_x;
  int king_y;

  int knight_x;
  int knight_y;
  int cell_count;
  find_king(&king_x, &king_y);
  piece p;


  // Check for pawn
  if (game.turn == 1)
  {
    piece p1 = game.board[king_y - 1][king_x - 1];
    piece p2 = game.board[king_y - 1][king_x + 1];
    if (p1 == B_PAWN || p2 == B_PAWN) return 1;
  }
  else 
  {
    piece p1 = game.board[king_y + 1][king_x - 1];
    piece p2 = game.board[king_y + 1][king_x + 1];
    if (p1 == W_PAWN || p2 == W_PAWN) return 1;
  }


  // Check for knight
  knight_x = king_x + 1;
  knight_y = king_y - 2;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;


  
  knight_x = king_x - 1;
  knight_y = king_y - 2;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;
 


  knight_x = king_x - 2;
  knight_y = king_y + 1;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;



  knight_x = king_x - 2;
  knight_y = king_y - 1;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;




  knight_x = king_x + 1;
  knight_y = king_y + 2;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;



  knight_x = king_x - 1;
  knight_y = king_y + 2;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;



  knight_x = king_x + 2;
  knight_y = king_y - 1;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;


  
  knight_x = king_x + 2;
  knight_y = king_y + 1;
  p = game.board[knight_y][knight_x];
  if 
  (
      p == B_KNIGHT && game.turn == 1
  ||  p == W_KNIGHT && game.turn == 0
  ) return 1;



  // Check for king
  p = game.board[king_y - 1][king_x];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y - 1][king_x + 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y][king_x + 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y + 1][king_x + 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y + 1][king_x];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y + 1][king_x - 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y][king_x - 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;



  p = game.board[king_y - 1][king_x - 1];
  if 
  (
      p == B_KING && game.turn == 1
  ||  p == W_KING && game.turn == 0
  ) return 1;




  // Check for rook & queen
  for (int i = 1; i <= king_y; i++)
  {
    p = game.board[king_y - i][king_x];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_ROOK)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_ROOK)
        return 1;
    }
    if (p != 0) break;
  }
  
  
  for (int i = 1; i <= 7 - king_x; i++)
  {
    p = game.board[king_y][king_x + i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_ROOK)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_ROOK)
        return 1;
    }
    if (p != 0) break;
  }
  


  for (int i = 1; i <= 7 - king_y; i++)
  {
    p = game.board[king_y + i][king_x];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_ROOK)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_ROOK)
        return 1;
    }
    if (p != 0) break;
  }



  for (int i = 1; i <= king_x; i++)
  {
    p = game.board[king_y][king_x - i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_ROOK)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_ROOK)
        return 1;   
    }
    if (p != 0) break;
  }

  

  // Check for bishop & queen
  cell_count = min(7 - king_x, king_y);
  for (int i = 1; i <= cell_count; i++)
  {
    p = game.board[king_y - i][king_x + i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_BISHOP)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_BISHOP)
        return 1;
    }
    if (p != 0) break;
  }
  

  cell_count = min(7 - king_x, 7 - king_y);
  for (int i = 1; i <= cell_count; i++)
  {
    p = game.board[king_y + i][king_x + i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_BISHOP)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_BISHOP)
        return 1;
    }
    if (p != 0) break;
  }


  cell_count = min(king_x, 7 - king_y);
  for (int i = 1; i <= cell_count; i++)
  {
    p = game.board[king_y + i][king_x - i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_BISHOP)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_BISHOP)
        return 1;
    }
    if (p != 0) break;
  }


  cell_count = min(king_x, king_y);
  for (int i = 1; i <= cell_count; i++)
  {
    p = game.board[king_y - i][king_x - i];
    if (game.turn == 1)
    {
      if (p == B_QUEEN || p == B_BISHOP)
        return 1;
    }
    else 
    {
      if (p == W_QUEEN || p == W_BISHOP)
        return 1;
    }
    if (p != 0) break;
  }




  return 0;
}
