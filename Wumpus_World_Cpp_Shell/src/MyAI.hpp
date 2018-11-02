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

#include "Agent.hpp"
#include <map>
#include <vector>
#include <array>
#include <stack>

using namespace std;
class MyAI : public Agent
{
public:
	MyAI ( void );

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
	int dir = 0; //index of the compas array. +1 to turn_right. remember to mod.
	std::string compass[4] = {"R","D","L","U"};
	bool worm = true;
	bool arrow = true;
	bool gold = false;
	int num_moves = 0;
	int position[2] = {0,0}; // Current Y,X Position
	int width = 6;
	int height = 6;
	bool left_home = false;
	//std::map<int[2],std::map<std::string,int>> world;
	map<array<int,2>,std::map<std::string,int>> world;
	stack<array<int,2>> steps;
	bool start = true;
	int next_pos[2] = {-1,-1};

	// Turn on if want to print comments
	const bool ERROR_CHECK = true;


	Action turnLeft();
	Action goForward();
	Action turnRight();
	void init_map();
	void update_map(bool stench,bool breeze);

	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif
