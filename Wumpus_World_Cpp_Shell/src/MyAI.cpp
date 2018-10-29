// ======================================================================
// FILE:        MyAI.cpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#include <iostream>
#include "MyAI.hpp"
using namespace std;

MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	init_map();
	steps.push({{0,0}});
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}
	
Agent::Action MyAI::getAction
(
	bool stench,
	bool breeze,
	bool glitter,
	bool bump,
	bool scream
)
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================


	print_menu(ERROR_CHECK, stench, breeze, glitter, bump, scream);

	// If the current position is not the (0,0), user has left spot.
	if ( curr_pos[0] != 0 && curr_pos[1] != 0 )
		world[{{0,0}}]["Left"] = 1;
	
	// If user is at (0,0) and has gotten the go home, has gold or has 
	// revisited the spot, climb.
	if ( curr_pos[0] == 0 && curr_pos[1] == 0)
		if ( go_home || has_gold || world[{{0,0}}]["Left"] == 1 ||
			 breeze )
			return CLIMB;

	// Allows function to go around the outer edge
	// Has some errors/issues ------------------------!!!!!!!!!!!!!!!!
	// if ( last_dir == 1 && curr_dir == 1 && last_pos[0] == curr_pos[0] ) {
	// 	if (ERROR_CHECK)
	// 		cout << "---------------------FACING UP---------------------" << endl;

	// 	if ( curr_pos[0] == max_dim[0] ) {
	// 		return updateDir('L');
	// 	}
	// 	else if ( curr_pos[0] == 0 ) {
	// 		return updateDir('R');
	// 	}
	// }

	if ( glitter ) {
		if (ERROR_CHECK)
			cout << "G" << endl;
		has_gold = 1;
		return GRAB;
	}
	// GO HOME
	if ( has_gold || breeze || go_home ) {
		go_home = 1;

		if ( breeze ) 
			world[curr_pos]["Breeze"] = 1;
			
		backtrack();

		// Need to fix if updating movement of AI (not in a box)
		if ( needed_dir == curr_dir ) {
			if (( curr_dir == 0 && curr_pos[0] > 0 ) ||
				 (curr_dir == 3 && curr_pos[1] > 0 ) ||
				 (curr_dir == 1 && curr_pos[1] < max_dim[1] ) ||
				 (curr_dir == 2 && curr_pos[0] < max_dim[0] )) {
				return updatePos();
			}
		}

		if ( needed_dir != -1 ) 
			return updateDir('L');

	}

	if ( bump ) {
		if (ERROR_CHECK)
			cout << "B" << endl;

		// Go back (cuz it went over)
		reversePos();

		// If you BUMPed the wall, update max dimensions.
		if ( curr_dir == 0 || curr_dir == 2
			&& curr_pos[0] != 0 )
			max_dim[0] = curr_pos[0];
		else if ( curr_dir == 1 || curr_dir == 3
			&& curr_pos[1] != 0 )
			max_dim[1] = curr_pos[1];

		return updateDir('L');
	}


	if ( stench ) {
		if (ERROR_CHECK)
			cout << "ST" << endl;

		world[curr_pos]["Stench"] = 1;

		if ( has_arrow == 0 ) {
			if (ERROR_CHECK)
				cout << "SH" << endl;
			has_arrow = 1;
			return SHOOT;
		} else if ( wumpus_dead ) {
			return updatePos();
		} else if ( has_arrow ) {
			return updatePos();
			// SAVE Wumpus location - should be the opposite of 
			// way you shot
		}

		if (ERROR_CHECK)
			cout << "S" << endl;
		return updateDir('L');
	}


	if ( scream ) {
		if (ERROR_CHECK)		
			cout << "AHH!!" << endl;
		wumpus_dead = 1;
	}
	// If wumpus is not dead and arrow has been shot, go home.
	// Will go forward by accident b/c scream appears one turn afterwards
	if ( wumpus_dead == 0 && has_arrow )
		go_home = 1;

	if (ERROR_CHECK)
		cout << "FORWARD" << endl;

	return updatePos();


	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================


void MyAI::backtrack() {
	if ( !steps.empty() ) {
		if (ERROR_CHECK) {
			cout << "BACKTRACK" << endl;
			cout << steps.top()[0] << "," << steps.top()[1] << endl;
		}

		array<int,2> needed_pos = steps.top();

		// Pop off repeated steps from bumps.
		while ( needed_pos[0] == curr_pos[0] && needed_pos[1] == curr_pos[1] &&
			!steps.empty()) {
			steps.pop();

			if ( !steps.empty() )
				needed_pos = steps.top();
		}
		

		if ( needed_pos[0] - curr_pos[0] <= -1 ) 
			needed_dir = 0; // L
		else if ( needed_pos[1] - curr_pos[1] >= 1 ) 
			needed_dir = 1; // U
		else if ( needed_pos[0] - curr_pos[0] >= 1 ) 
			needed_dir = 2; // R
		else if ( needed_pos[1] - curr_pos[1] <= -1 ) 
			needed_dir = 3; // D
		

		if (ERROR_CHECK) {
			cout << "[x]: " << curr_pos[0] << "-" <<
			needed_pos[0] << ":" << (needed_pos[0] - curr_pos[0]) << endl;
			cout << "[y]: " << curr_pos[1] << "-" <<
			needed_pos[1] << ":" << (needed_pos[1] - curr_pos[1]) << endl;
		}

	}

	if (ERROR_CHECK)
		cout << "NeedDir: " << needed_dir << endl;
}

void MyAI::reversePos() {
	if (ERROR_CHECK)
		cout << "REVERSING POS" << endl;

	if (!steps.empty())
		steps.pop();

	if ( curr_dir == 0 ) { // COL - 1
		if ( curr_pos[0] > 0 && curr_pos[0] <= max_dim[0] )
	 		curr_pos[0]++; 
	}
	else if ( curr_dir == 1 ) { // COL - 1
		if ( curr_pos[1] >= 0 && curr_pos[1] < max_dim[1] )
			curr_pos[1]--; 
	}
	else if ( curr_dir == 2 ) { // ROW + 1
		if ( curr_pos[0] >= 0 && curr_pos[0] < max_dim[0] )
	 		curr_pos[0]--; 
	}
	else if ( curr_dir == 3 ) { // ROW - 1
	 	if ( curr_pos[1] > 0 && curr_pos[1] <= max_dim[1] )
			curr_pos[1]++;
	}	
}

Agent::Action MyAI::updatePos() {
	if (ERROR_CHECK)
		cout << "UPDATING POS" << endl;
	last_pos = curr_pos;

	if ( curr_dir == 0 ) { // L COL - 1
		if ( curr_pos[0] > 0 && curr_pos[0] <= max_dim[0] )
	 		curr_pos[0]--;
	}
	else if ( curr_dir == 1 ) { // U ROW + 1
		if ( curr_pos[1] >= 0 && curr_pos[1] < max_dim[1] )
			curr_pos[1]++;
	}
	else if ( curr_dir == 2 ) { // R COL - 1
		if ( curr_pos[0] >= 0 && curr_pos[0] < max_dim[0] )
	 		curr_pos[0]++;
	}
	else if ( curr_dir == 3 ) { // D ROW - 1
	 	if ( curr_pos[1] > 0 && curr_pos[1] <= max_dim[1] )
			curr_pos[1]--;
	}		

	if ( go_home == 0 )
		steps.push(curr_pos);
	return FORWARD;
}

Agent::Action MyAI::updateDir( char turn ) {
	if (ERROR_CHECK)
		cout << "UPDATING DIR" << endl;
	last_dir = curr_dir;

	if ( turn == 'L' )
		return turnLeft();
	else if ( turn == 'R' )
		return turnRight();
}

Agent::Action MyAI::turnLeft() {
	if ( curr_dir == 0 ) 
		curr_dir = 3;
	else
		curr_dir--;

	return TURN_LEFT;
}

Agent::Action MyAI::turnRight() {
	curr_dir = ( curr_dir + 1 ) % 4;
	return TURN_RIGHT;
}

void MyAI::init_map() {
	for ( int row = 0; row < 6; row++ ) {
		for (int col = 0; col < 6; col++ ) {
			array<int, 2> temp = {row, col};
			world[temp]["Wumpus"] = -1;
			world[temp]["Stench"] = -1;
			world[temp]["Breeze"] = -1;
			world[temp]["Pit"] = -1;
		}
	}
	world[{{0,0}}]["Left"] = 0;
}



// ======================================================================
// TESTING CODE
// ======================================================================


void MyAI::print_menu(bool print, bool stench, bool breeze, bool glitter, 
	bool bump, bool scream) {
	if (print == 1) {
		cout << "MaxDim: " << max_dim[0] << "," << max_dim[1] << endl;
		cout << "CurrDir: " << curr_dir << endl;
		cout << "CurrPos: " << curr_pos[0] << "," << curr_pos[1] << endl;
		cout << "Gold: " << has_gold << endl;
		cout << "Arrow: " << has_arrow << endl;
		cout << "DeadW: " << wumpus_dead << endl;
		cout << "BUMP: " << bump << endl;
		cout << "LastDir: " << last_dir << endl;
		cout << "GoHome: " << go_home << endl;
		
		if (!steps.empty())
			cout << "Stack: " << steps.top()[0] << "," << steps.top()[1] << endl;
	}
}

// ======================================================================
// YOUR CODE ENDS
// ======================================================================