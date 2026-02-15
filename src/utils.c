#include "utils.h"


int min(int x, int y)
{
  return x < y ? x : y;    
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



void clear_cache()
{
  game.valid_moves_top = 0;
  game.legal_moves_top = 0;
}

