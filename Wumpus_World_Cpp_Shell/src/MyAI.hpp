// ======================================================================
// FILE:        MyAI.hpp
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

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include <map>
#include <stack>
#include <string>
#include "Agent.hpp"

using namespace std;

class MyAI : public Agent
{
public:
	MyAI ( void );


	void reversePos();
	Action updatePos();
	Action turnLeft();
	Action turnRight();
	Action updateDir( char turn );
	void init_map();
	void backtrack();
	void print_menu( bool print, bool stench, bool breeze, bool glitter,
	bool bump, bool scream );

	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	);
	
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	
	bool has_gold = 0;
	bool has_arrow = 0;
	bool wumpus_dead = 0;
	bool go_home = 0;
	array<int,2> curr_pos = {{0, 0}}; // (R,C)
	array<int,2> last_pos = {{0, 0}};
	array<int,2> max_dim = {{5, 5}}; // include 0
	// array<int,4> curr_dir = {{0, 1, 2, 3}}
	int curr_dir = 2; // L, U, R, D
	int last_dir = -1;
	int needed_dir = -1;
	map< array<int,2>, map<std::string, int> > world;
	stack < array<int,2> > steps; // Use to go back to beginning
	const bool ERROR_CHECK = 1;


	
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif