#include <raylib.h>
#include "game.h"
#include "input.h"
#include <stdio.h>


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



input_state get_input_state()
{
  return state;
}



void handle_input()                          
{
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    Vector2 mouse_pos = GetMousePosition(); 
    int x = (int) (mouse_pos.x - 30) / 63;
    int y = (int) (mouse_pos.y - 30) / 63;

    switch (state) 
    {
      case INPUT_IDLE:
        if (select_piece(x, y))
          state = INPUT_SELECTED;
        break;

      case INPUT_SELECTED:
        if (is_legal_move(x, y))
        {
          update_piece(x, y);
          state = INPUT_IDLE;
        }
        else if (is_ally_piece(x, y))
        {
          if (is_piece_selected(x, y))
          {
            deselect_piece();
            state = INPUT_IDLE;
            return;
          }
          deselect_piece();
          select_piece(x, y);
          state = INPUT_SELECTED;
        }
        else 
        {
          deselect_piece();
          state = INPUT_IDLE;
        }
    }     
  }
}
