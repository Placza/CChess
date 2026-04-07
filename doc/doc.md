## Client

The client app can be divided into these parts:
- **game**: the actual board and mechanism behind the game of chess; exposes a structure that the rest of the app can communicate with
- **renderer**: handles all the drawing and rendering for the app; reads from the rest of the app to update the display
- **input_manager**: handles all the input from the user; exposes a data structure from which the rest of the app can read
- **client**: manages the content of the user interface; exposes a data structure for storing the state of the app as well as exposes functions to switch the state of the app

The chess game can be divided into these parts:
- **game_state**: the "stupid" part of the game; only manages the current game state; reveals some basic functions for game state manipulation like moving the pieces without checking if the move is legal or valid
- **game_manager**: manages the game state; interacts with the game using the exposed game functions while also checking for the validity and legality of moves; manages the game externally by setting if it is check or check mate, triggers who's turn it is and so on; exposes functions to update the game state under regulated circumstances
- **game_input**: manages the input for the game; listenes to the external input structures and verifies if a given input is relavent for the board; uses the functions the game_manager exposes to update the game state	

The way the app communicates internally is as follows:


        
            
            ____________________      _______________________        _______________
            |                  |      |                     |        |             |
            |    User input    |----->|    Input manager    |------->|    Client   |
            |__________________|      |       (input)       |     -->|   (client)  |
                                      |_____________________|  (2)|  |_____________|
                                                 |                |         |
                                                 |                |         |
                                                 |                |         |
                                                 V                |         V
                                        ______________ (1)        |  __________________      _____________________
                                        |            |<-----------x  |                |      |                   |
                                        |    Game    |-------------->|    Renderer    |----->|    User output    |
                                        |   (game)   |               |________________|      |___________________|
                                        |____________|
            
            (1) The game changes the state of the app (when the game ends, change the state; display different thing if the player losses or wins) 
            (2) The app controls the game by reseting the game when it starts




The game itself communicates as follows:



    
                            ______________________    
                            |                    |<----->Client  
                            |        Game        |
                            |____________________|------->Renderer
                                ^           |
                                |           |
                                |           |
                    updates the |           | exposes the
                    game state  |           | game state
                                |           |
                                |           |
                                |           V
                            ______________________
                            |                    |
                            |    Game maanger    |
                            |____________________|
                                ^           |
                                |           |
                                |           |
         tells the game manager |           | exposes structures and functions
             what actions to do |           | to allow for the user to
                                |           | interatively controll the game
                                |           |
                                |           V
                            ______________________
                            |                    |    
                            |     Game input     |
                            |____________________|
                                      ^
                                      |
                                    Input
    
                                            




