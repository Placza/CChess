#include "game.h"




#ifndef PIECE_MOVES_H
#define PIECE_MOVES_H



void check_valid_moves_pawn(int color);
void check_valid_moves_rook();
void check_valid_moves_bishop();
void check_valid_moves_knight();
void check_valid_moves_queen();
void check_valid_moves_king();
void check_valid_moves(piece selected);


#endif 
