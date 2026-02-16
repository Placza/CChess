#include <raylib.h>
#include "game.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>


input_state state = INPUT_IDLE;



/*
 *
 *
 *
 * The input handler will keep track of the state of interaction of the player with the board. It will controll when the
 * game will display legal moves highlight, when the game will move a piece and where.
 *
 *
 *     
 *
 *
 */ 


int scroll_state;
int x_cord;
int y_cord;
bool is_promotion = 0;



input_state get_input_state()
{
  return state;
}



static void handle_mouse_pos()
{
  Vector2 mouse_pos = GetMousePosition(); 
  x_cord = (int) (mouse_pos.x - 30) / 63;
  y_cord = (int) (mouse_pos.y - 30) / 63;
}



static void handle_scrolling()
{
  Rectangle cell_bounds = { game.promotion_x * 63 + 30, game.promotion_y * 63 + 30, 63, 63 };
  if (CheckCollisionPointRec(GetMousePosition(), cell_bounds))
  {
    scroll_state += (int)GetMouseWheelMove();
    change_promotion(abs(scroll_state % 4));
  }
}


static void handle_promotion()
{
  if (is_promotion)
  {
    for (int i = 0; i < game.legal_moves_top; i++)
    {
      if (x_cord == game.legal_moves[i][0] && y_cord == game.legal_moves[i][1])
      {
        game.is_promotion = 1;
        game.promotion_x = x_cord;
        game.promotion_y = y_cord;
        break;
      }
    }
  }
  else
    game.is_promotion = 0;
}



void handle_input()                          
{
  handle_mouse_pos();
  handle_scrolling();
  handle_promotion();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    switch (state) 
    {
      case INPUT_IDLE:
        if (select_piece(x_cord, y_cord))
        {
          state = INPUT_SELECTED;
          is_promotion = is_to_be_promoted();
        }
        break;

      case INPUT_SELECTED:
        if (is_legal_move(x_cord, y_cord))
        {
          update_piece(x_cord, y_cord);
          state = INPUT_IDLE;
        }
        else if (is_ally_piece(x_cord, y_cord))
        {
          if (is_piece_selected(x_cord, y_cord))
          {
            deselect_piece();
            state = INPUT_IDLE;
            return;
          }
          deselect_piece();
          select_piece(x_cord, y_cord);
          state = INPUT_SELECTED;
          is_promotion = is_to_be_promoted();
        }
        else 
        {
          deselect_piece();
          state = INPUT_IDLE;
        }
    }     
  }
}
