#ifndef INPUT_H
#define INPUT_H


typedef enum 
{
  INPUT_IDLE,
  INPUT_SELECTED
} input_state;



void handle_input();
input_state get_input_state();


#endif
