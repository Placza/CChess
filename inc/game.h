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
 * - capture_piece(piece) : internal function, will be called by move_piece if another
 *                          piece moves to an already occupied square; doesn't care about
 *                          color
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
  piece board[8][8];
  game_state state;
  int valid_moves[64][2]; // (-) move to game manager
  int valid_moves_top; // (-) move to game manager (consider creating a structure for a po
                       // sition instead of storing an array of arrays
  int legal_moves[64][2]; // (-) move to game manager
  int legal_moves_top; // (-) move to game manager
  piece w_captured[16]; // (+) will keep it here
  int w_captured_top;  // (+) will keep it here
  piece b_captured[16]; // (+) will keep it here
  int b_captured_top; // (+) will keep it here

  piece w_promotion; // tricky, will have to inspect
  piece b_promotion; // same here

  int en_passant_x; // tricky
  int en_passant_y; // tricky
  bool is_en_passant; // tricky

  bool r_b_rook_moved; // tricky
  bool l_b_rook_moved; // tricky
  bool r_w_rook_moved; // tricky
  bool l_w_rook_moved; // tricky
  bool b_king_moved; // tricky
  bool w_king_moved; // tricky

  int promotion_x; // tricky
  int promotion_y; // tricky
  bool is_promotion; // tricky
                     //
                     //
                     //
                     // All the tricky fields could theoretically be moved to the
                     // game manager as they don't really describe the game state
                     // but are here to keep track of valid and legal moves that
                     // the game doesn't care about
                     //
                     //

  int turn; // (+) here
  int selected; // not sure what that is lol
  int p_start_x; // this is important for the game state, but then again not describes it
  int p_start_y; // same as p_start_x
  int p_end_x; // same as previous
  int p_end_y; // same as previous
} Game;


extern Game game;


void init_game(); // (+) keep here (IMPORTANT)
bool select_piece(int x, int y); // (-) if p_start and p_end are being move to the 
                                 // game manager, no point in keeping track of the
                                 // selected piece
void deselect_piece(); // (-) same as for select_piece
void update_piece(int x, int y); // (-) same reason
bool has_selection(); // (-) same
bool is_legal_move(int x, int y); // (-) def same
bool is_selected_ally(int x, int y); // (-) same
bool is_piece_selected(int x, int y); // (-) same
bool is_ally_piece(int x, int y); // (-) same
void change_promotion(int p); // (-) same (should be private) 
bool is_to_be_promoted(); // (-) same (should be private)



#endif
