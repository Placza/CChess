#include "game.h"
#include "utils.h"
#include <raylib.h>
#include <stdio.h>



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
    .state = GS_ONGOING
  };

}



void add_valid_move(int x, int y)
{
  if (x > 7 || x < 0 || y > 7 || y < 0) return;
  game.valid_moves[game.valid_moves_top][0] = x;
  game.valid_moves[game.valid_moves_top][1] = y;
  game.valid_moves_top++;
}



void add_legal_moves(int x, int y)
{
  game.legal_moves[game.legal_moves_top][0] = x;
  game.legal_moves[game.legal_moves_top][1] = y;
  game.legal_moves_top++;
}




bool is_ally(piece p)
{
  if (game.turn == 1)
  {
    return p >= W_PAWN && p <= W_KING;
  }
  else
  {
    return p >= B_PAWN && p <= B_KING;
  }
}



bool is_enemy(piece p)
{
  if (game.turn == 1)
  {
    return p >= B_PAWN && p <= B_KING;
  }
  else
  {
    return p >= W_PAWN && p <= W_KING;
  }
}




void check_valid_moves_pawn(int color)
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





void check_valid_moves_rook()
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



void check_valid_moves_bishop()
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




void check_valid_moves_knight()
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



void check_valid_moves_queen()
{
  check_valid_moves_rook();
  check_valid_moves_bishop();
}



void check_valid_moves_king()
{
  piece p;
  int pos_x;
  int pos_y;


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



void find_king(int* x, int* y)
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



void check_legal_moves(int x, int y);
void clear_cache();


bool is_checkmate()
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




void check_is_chess()
{
  if (is_check())
  {
    if (is_checkmate())
    {
      printf("Checkmate! %d\n", game.turn);   
      game.state = GS_CHECKMATE;
    }
    else
    {

      printf("Check %d!\n", game.turn);
      game.state = GS_CHECK;
    }
  }
  else 
  {
    printf("Not check %d!\n", game.turn);
    game.state = GS_ONGOING;
  }
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




void check_capture()
{
  piece target = game.board[game.p_end_y][game.p_end_x];
  if (is_enemy(target))
    printf("captured: %d\n", target);
}



void move_piece()
{
  for (int i = 0; i < game.valid_moves_top; i++)
  {
    if (
        game.legal_moves[i][0] == game.p_end_x 
    &&  game.legal_moves[i][1] == game.p_end_y
    )
    {
      check_capture();
      game.board[game.p_end_y][game.p_end_x] = game.board[game.p_start_y][game.p_start_x];
      game.board[game.p_start_y][game.p_start_x] = 0;
      game.turn ^= 1;
      return;
    }
  }
}



void simulate_piece(int old_x, int old_y, int new_x, int new_y)
{
  piece p = game.board[new_y][new_x];

  game.board[new_y][new_x] = game.board[old_y][old_x];
  game.board[old_y][old_x] = 0;

  if (!is_check())
    add_legal_moves(new_x, new_y);

  game.board[old_y][old_x] = game.board[new_y][new_x];
  game.board[new_y][new_x] = p;
}





void check_legal_moves(int x, int y)
{
  piece selected = game.board[y][x];

  check_valid_moves(selected);

  for (int i = 0; i < game.valid_moves_top; i++)
  {
    int new_x = game.valid_moves[i][0];
    int new_y = game.valid_moves[i][1];
    simulate_piece(x, y, new_x, new_y);
  }
}



void clear_cache()
{
  game.valid_moves_top = 0;
  game.legal_moves_top = 0;
}



bool select_piece(int x, int y)
{
  game.p_start_x = x;
  game.p_start_y = y;

  piece p = game.board[y][x];
  if (is_ally(p))
    check_legal_moves(x, y);

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
  check_is_chess();

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
  
