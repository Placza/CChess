#include <raylib.h>


#ifndef GAME_H
#define GAME_H


#define WINDOW_H 8*63 + 60
#define WINDOW_W 8*63 + 60



/* 
 * 
 * The game is the "stupid" part of the implementation of chess.
 * Its main purpuse is to keep track of the game state as well as expose the basic
 * functions to manipulate with the game state.
 *
 * The state is constructed of these components:
 * - board : an 8x8 2d array that keeps track of the position of each piece that are
 *           encoded as an enumeration where 0 is an empty square 
 * 
 * - game_state : stores if the game is ongoing, in check, in checkmate or if it's a
 *                stalemate; it determins who is in check or checkmate based on the 
 *                current turn
 *
 * - <color>_captured : 16 piece array that keeps track of which pieces were captured;
 *                      cares about the color
 * 
 * - <color>_captured_top : integer to display the top of the captured list for each
 *                          color
 *
 * - turn : integer (surprisingly) to keep track of who's turn it is; could be a 
 *          game manager thing though, will reconsider (?)
 *
 *
 *
 * The game exposes these functions to the rest of the game implementation: 
 * - init_game() : reset the state of the game to the starting state
 *
 * - move_piece(from, to) : moves one piece from one place to another while not caring
 *                          for validity or legality; does care if you try to move an
 *                          empty square to a non-empty square => returns 1 for good move
 *                          and -1 for a not good move
 *
 * - (~)capture_piece(piece) : internal function, will be called by move_piece if another
 *                             piece moves to an already occupied square; doesn't care about
 *                             color
 *
 */ 



typedef enum
{
  EMPTY,
  W_PAWN, W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING,
  B_PAWN, B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING,
  W_PAWN_GHOST, B_PAWN_GHOST,
} piece;



typedef enum  
{
  GS_ONGOING, GS_CHECK, GS_CHECKMATE, GS_STALEMATE
} game_state;



typedef struct
{
  piece board[8][8]; // defines the game board
  game_state state; // stores if the game is ongoing, check, checkmate or a stalemate

  piece w_captured[16]; // keeps track of white captured peaces
  int w_captured_top;
  piece b_captured[16]; // keeps track of black captured pecaes
  int b_captured_top; 

  int turn; // keeps track of which color's turn it is
} Game;


extern Game game;


void init_game(); // initializes the game state
int move_piece(int x0, int y0, int x1, int y1); // moves one piece from one square to another



#endif
