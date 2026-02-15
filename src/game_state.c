#include "game_state.h"
#include "game.h"
#include "legal_moves.h"
#include <stdio.h>
#include "utils.h"




void check_is_check()
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



