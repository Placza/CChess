#include <raylib.h>


#ifndef GAME_H
#define GAME_H


#define WINDOW_H 8*63 + 60
#define WINDOW_W 8*63 + 60


typedef enum
{
  EMPTY,
  W_PAWN, W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING,
  B_PAWN, B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING
} piece;



typedef enum  
{
  GS_ONGOING, GS_CHECK, GS_CHECKMATE, GS_STALEMATE
} game_state;



typedef struct
{
  piece board[8][8];
  game_state state;
  int valid_moves[64][2];
  int valid_moves_top;
  int legal_moves[64][2];
  int legal_moves_top;
  piece w_captured[16];
  int w_captured_top;
  piece b_captured[16];
  int b_captured_top;
  int turn;
  int selected;
  int p_start_x;
  int p_start_y;
  int p_end_x;
  int p_end_y;
} Game;


extern Game game;


void init_game();
bool select_piece(int x, int y);
void deselect_piece();
void update_piece(int x, int y);
bool has_selection();
bool is_legal_move(int x, int y);
bool is_selected_ally(int x, int y);
bool is_piece_selected(int x, int y);
bool is_ally_piece(int x, int y);


#endif
