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
  if (!is_enemy(target)) return;    
  
  if (game.turn == 0)
  {
    if (target == W_PAWN_GHOST)
    {
      game.board[game.p_end_y - 1][game.p_end_x] = 0;
      game.w_captured[game.w_captured_top] = W_PAWN;
    }
    else
    {
      game.w_captured[game.w_captured_top] = target;
    }
    game.w_captured_top++; 
  }
  else
  {
    if (target == B_PAWN_GHOST)
    {
      game.board[game.p_end_y + 1][game.p_end_x] = 0;
      game.b_captured[game.b_captured_top] = B_PAWN;
    }
    else
    {
      game.b_captured[game.b_captured_top] = target;
    }
    game.b_captured_top++;
  }
}



void move_piece()
{
  for (int i = 0; i < game.legal_moves_top; i++)
  {
    if (
        game.legal_moves[i][0] == game.p_end_x 
    &&  game.legal_moves[i][1] == game.p_end_y
    )
    {
      check_capture();
      
      if (game.is_en_passant)
      {
        game.board[game.en_passant_y][game.en_passant_x] = 0;
        game.is_en_passant = 0;
      }

      if (game.board[game.p_start_y][game.p_start_x] == W_PAWN && game.p_start_y == 6 && game.p_end_y == 4)
      {
        game.en_passant_x = game.p_start_x;
        game.en_passant_y = game.p_start_y - 1;
        game.board[game.p_start_y - 1][game.p_start_x] = W_PAWN_GHOST;
        game.is_en_passant = 1;
      }

      if (game.board[game.p_start_y][game.p_start_x] == B_PAWN && game.p_start_y == 1 && game.p_end_y == 3)
      {
        game.en_passant_x = game.p_start_x;
        game.en_passant_y = game.p_start_y + 1;
        game.board[game.p_start_y + 1][game.p_start_x] = B_PAWN_GHOST;
        game.is_en_passant = 1;
      }


      if (game.board[game.p_start_y][game.p_start_x] == W_PAWN && game.p_start_y == 1)
        game.board[game.p_end_y][game.p_end_x] = game.w_promotion;
      else if (game.board[game.p_start_y][game.p_start_x] == B_PAWN && game.p_start_y == 6)
        game.board[game.p_end_y][game.p_end_x] = game.b_promotion;
      else 
      {
        game.board[game.p_end_y][game.p_end_x] = game.board[game.p_start_y][game.p_start_x];
      }
      game.board[game.p_start_y][game.p_start_x] = 0;
      game.turn ^= 1;
      return;
    }
  }
}



