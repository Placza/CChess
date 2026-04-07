## Client

The client app can be divided into these parts:

The chess game can be divided into these parts:
	- game_state: the "stupid" part of the game; only manages the current game state; reveals some basic functions for game state manipulation like moving the pieces without checking if the move is legal or valid
	- game_manager: manages the game state; interacts with the game using the exposed game functions while also checking for the validity and legality of moves; manages the game externally by setting if it is check or check mate, triggers who's turn it is and so on; exposes functions to update the game state under regulated circumstances
	- game_input: manages the input for the game; listenes to the external input structures and verifies if a given input is relavent for the board; uses the functions the game_manager exposes to update the game state	
