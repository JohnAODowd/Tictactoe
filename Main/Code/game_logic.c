// Tic-tac-toe Project

// Include definitions
#include "defines.h"

// Setup a two-dimensional 3x3 array. 
static char board[LED_CNT][LED_CNT] ={ {OFF, OFF, OFF}, {OFF, OFF, OFF}, {OFF, OFF, OFF} };
struct game_state {
  char state;
  char move_num;
  char yellow_player;
  char red_player;
} game_state;
void setupBoard() {
}
void invalidMove(){
}
char isFull(){
  // Return true if board is full, false otherwise
  if(game_state.move_num == BRD_FULL) return 1;
  else return NOT_OVER;
}
void clearBoard(){
  // Set the value of each position in the board to OFF.
  char i,j;
  for (i = 0; i < LED_CNT; i++){
    for (j = 0; j < LED_CNT; j++){
      board[i][j] = OFF;
    }
  }
  game_state.state = NOT_STRTD;
}
void new_game(int input){
  switch(input){
    case BACK:
        game_state.state = GM_LCKD;
        break;
    case ZERO:
        clearBoard();
  }
}
void getPlayerInput(int irSensorValue) {
	
	char player;
	if (game_state.move_num % PLYR_TURN == PLYR_TST){
		player = PLYR_ONE;
	} else {
		player = PLYR_TWO;
	}
	
	char valid_move = INVALID;
		switch(irSensorValue) {
		    // Setup cases for the return value IR Remote Sensor. 

		    case ZERO:
		    // Number 0 Returned 
		      clearBoard();
		      break;

		    case ONE:
		    // Number 1 Returned
		      if (!TOP_RIGHT) {
		      if (player) TOP_RIGHT = RED;
		      else TOP_RIGHT = YLW;
		      valid_move = VALID;
		      } else invalidMove(); 
		      break;

		    case TWO:
		    // Number 2 Returned
		      if(!TOP_MID){
		      if (player) TOP_MID = RED;
		      else TOP_MID = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case THREE:
		    // Number 3 Returned
		      if(!TOP_LEFT){
		      if (player) TOP_LEFT = RED;
		      else TOP_LEFT = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case FOUR:
		    // Number 4 Returned 
		      if(!MID_RIGHT){		
		      if (player) MID_RIGHT = RED;
		      else MID_RIGHT = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case FIVE:
		    // Number 5 Returned
		      if(!MID_MID){	
		      if (player) MID_MID = RED;
		      else MID_MID = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case SIX:
		    // Number 6 Returned
		      if(!MID_LEFT){
		      if (player) MID_LEFT = RED;
		      else MID_LEFT = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case SEVEN:
		    // Number 7 Returned
		      if(!BOT_RIGHT){	
		      if (player) BOT_RIGHT = RED;
		      else BOT_RIGHT = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case EIGHT:
		    // Number 8 Returned
		      if(!BOT_MID){	
		      if (player) BOT_MID = RED;
		      else BOT_MID = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;

		    case NINE:
		    // Number 9 Returned 
		      if(!BOT_LEFT){
		      if (player) BOT_LEFT = RED;
		      else BOT_LEFT = YLW;
		      valid_move = VALID;
		      } else invalidMove();
		      break;
		}
	if (valid_move) game_state.move_num ++;
}

char gameOver() {
	
	// Game is over when there is a draw or when there is a win.
	// Return 0 if not over, positive int otherwise.
	// Return -3 for RED Win.
	// Return 3 for YLW Win.
	// Return 1 for Draw.
        if(game_state.state == GM_LCKD) return game_state.state;
        if(game_state.state == NOT_STRTD) return game_state.state;
	// Check for win:
  	char winner;
	//  vertically:
	if      ((winner = TOP_RIGHT + MID_RIGHT + BOT_RIGHT) % WIN_MSK == WIN_TST); 
	else if ((winner = TOP_MID   + MID_MID   + MID_MID  ) % WIN_MSK == WIN_TST); 
	else if ((winner = TOP_LEFT  + MID_LEFT  + MID_LEFT ) % WIN_MSK == WIN_TST);
	//  horizontally:
	else if ((winner = TOP_RIGHT + TOP_MID + TOP_LEFT) % WIN_MSK == WIN_TST);
	else if ((winner = MID_RIGHT + MID_MID + MID_LEFT) % WIN_MSK == WIN_TST);
	else if ((winner = BOT_RIGHT + BOT_MID + BOT_LEFT) % WIN_MSK == WIN_TST);
	//  diagonally:
	else if ((winner = TOP_RIGHT + MID_MID + BOT_LEFT ) % WIN_MSK == WIN_TST);
	else if ((winner = TOP_LEFT  + MID_MID + BOT_RIGHT) % WIN_MSK == WIN_TST);
	else if ( isFull() ) {
		// Board full and not won - must be a Draw.
	    	winner = DRAW;

	  } else {
		  // Board is not full, so game is not over.
		  winner = NOT_OVER;
	}
        game_state.state = winner;
	char game_finish_state;
	if ((winner == YLW_WIN) || (winner == RED_WIN) || (winner == DRAW)) {
		game_finish_state = 1;
	} else if (winner == NOT_OVER){
		game_finish_state = -1;
	} 
	return game_finish_state;
}
