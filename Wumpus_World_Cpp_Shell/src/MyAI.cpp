//LAST SAVED AI score:-3
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
#include <map>
#include <vector>
#include <stack>
#include "MyAI.hpp"
#include <utility>
#include <array>

using namespace std;
MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	// std::string compass[dir] = "R";
	// bool worm = true;
	// bool arrow = true;
	// bool gold = false;
	// int num_moves = 0;
	// int position[] = {0,0};
	// int width = 6;
	// int height = 6;
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
	if(start) {
		start = false;
		std::cout<<"\n--\n";
		init_map();
	}

	update_map(stench,breeze);
	if (ERROR_CHECK) {
		std::cout<<"ST: "<<stench<<"\nBR: "<<breeze<<"\nGl: "<<glitter<<"\nBP: "<<bump<<"\nAH: "<<scream<<"\n";
		std::cout<<"POSIT: "<<position[0]<<","<<position[1]<<"\n\n";
	}

	num_moves++; // Necessary? Unused.

	if (glitter) {
		gold = true;
		return GRAB;
	}
	if(!gold && !bump) {
		if(steps.empty()) 
			steps.push({position[0],position[1]});
		if(!steps.empty() && (steps.top()[0]!=position[0] || 
			steps.top()[1]!=position[1])) {
			steps.push({position[0],position[1]});
		}
	}
	/* If AI has left home, set it true */
	if (position[0] != 0 && position[1] != 0)
		left_home = true;

	if(bump) {
		/* Has Hit the Right Wall, get max and turn LEFT*/
		if(compass[dir] == "R") {
			position[1] = position[1]-1;
			width = position[1];
			
			if (ERROR_CHECK)
				std::cout<<"WT: "<<width<<"\n";
			
			if(position[0] < height) 
				return turnLeft();
			return turnRight();
		}
		/* Left Wall. 
			SHOULD NOT HIT THIS WALL, IMPLREMENT 0 INDEX REALIZING
			cause duh there's wall
		*/
		else if(compass[dir] == "L") {
			position[1] = position[1] +1;
			return turnLeft();

		}
		/* Top Wall, get max height*/
		else if(compass[dir] == "U") {
			position[0] = position[0] - 1;
			height = position[0];

			if (ERROR_CHECK)
				std::cout<<"HT: "<<height<<"\n";
			
			if(position[1] < width) {
				return turnRight();
			}
			return turnLeft();
		}
		/* Bottom Wall. 
			SHOULD NOT HIT THIS WALL, IMPLEMENT 0 INDEX REALIZING
			cause duh there's wall
		*/
		else if (compass[dir] == "D") {
			position[0] = position[0] + 1;
			if(position[0] == 0 && position[1] == 0) 
				return CLIMB;
		}
	}
	/* ORIGIN, therefore CLIMB*/
	if(position[0] == 0 && position[1] == 0 && (breeze || left_home)) {
		return CLIMB;
	}
	/* SHOOT in front.
		smarter AI should hopefully know it it not facing a wall
		It should also mark the other part of the map as Wumpus if miss
	*/
	if(stench && arrow) {
		arrow = false;
		return SHOOT;
	}
	if(scream) {
		worm = false;
		return goForward();
	} else {
		std::cout << "NOT DEAD" << endl;

		// If facing up, no scream, then its on left or right
		// If you are next to a wall then won't go
		// world[{row,col}]["worm"] = -1;
	}



	if (gold) {

		if (steps.empty())
			return CLIMB;

		int bs[2] = {steps.top()[0], steps.top()[1]};
		
		/* Comparing the two positions. */
		string face_dir;
		if (ERROR_CHECK) {
			std::cout<<"POSIT: ["<<position[0]<<","<<position[1]<<"]\n";
			std::cout<<"BS: ["<<bs[0]<<","<<bs[1]<<"]\n";
		}

		/* Pop repeated steps. */
		while (bs[0] == position[0] && bs[1] == position[1]) {
			steps.pop();
			bs[0] = steps.top()[0];
			bs[1] = steps.top()[1];
			
			if (ERROR_CHECK)
				std::cout<<"BS: ["<<bs[0]<<","<<bs[1]<<"]\n";
		}
		
		if (ERROR_CHECK)
			std::cout<<"DIF: "<<(bs[0]-position[0])<<", "<<(bs[1]-position[1])<<"\n";
		
		/* Find direction of previous step */
		if (bs[0] - position[0] < 0)
			face_dir = "D";
		else if (bs[0] - position[0] > 0) 
			face_dir = "U";
		else if (bs[1] - position[1] <= -1)
			face_dir = "L";
		else if (bs[1] - position[1] >= 1) 
			face_dir = "R";
		else
			std::cout << "----------------Error----------------\n";

		/* When not facing the direction to go home, turn left */
		if (compass[dir] != face_dir) {
			return turnLeft();
		}
		else { /* Else go forward */
			steps.pop();
			return goForward();
		}
	}

	/* BREEZE
		If AI hits breeze, do something.
	*/
	if(breeze) {
		/* BOTTOM ROW
			If the current direction is right or up, turn left.
			If it is Left, go foward/home.
			PT[Y=0] = 0;
		*/
		if(position[0] == 0) { 
			if(compass[dir] == "L")
				return goForward();
			else 
				return turnLeft();


		}
	}

	// Check map and see where the last 0 was filled. 
	// If it moved up a level, turn left. And go left.


	return goForward();


	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

Agent::Action MyAI::turnLeft()
{
	if (dir == 0)
		dir = 3;
	else
		dir--;
	return Agent::TURN_LEFT;
}

Agent::Action MyAI::turnRight()
{
	dir = (dir + 1) % 4;
	return TURN_RIGHT;
}

Agent::Action MyAI::goForward()
{
	if (compass[dir] == "R")
		position[1] = position[1] + 1;
	else if (compass[dir] == "L")
		position[1] = position[1] - 1;
	else if (compass[dir] == "U")
		position[0] = position[0] + 1;
	else if (compass[dir] == "D")
		position[0] = position[0] - 1;
	return FORWARD;

}

void MyAI::init_map()
{
	for(int row = 0; row < 6; row++) {
		for(int col = 0; col < 6; col++) {
			world[{row,col}]["worm"] = -1;
			world[{row,col}]["stench"] = -1;
			world[{row,col}]["breeze"] = -1;
			world[{row,col}]["pit"] = -1;
		}
	}

	if (ERROR_CHECK) {
		for (auto& x: world) {
	   		std::cout << " [" << x.first[0] << " "<<x.first[1]<<": ["
				<< "[W, "<<x.second["worm"] << "] [ST, "<<x.second["stench"]
				<< "] [BR, "<< x.second["breeze"] <<"] [PT, "<<x.second["pit"]<<"] ]";
		}
	 	std::cout << '\n';
	 }
}

void MyAI::update_map(bool stench, bool breeze)
{
	int s = 0; int b = 0;
	if(stench == true)
		s = 1;
	if(breeze == true)
		b = 1;

	world[{position[0], position[1]}]["worm"] = 0;
	world[{position[0], position[1]}]["stench"] = s;
	world[{position[0], position[1]}]["breeze"] = b;
	world[{position[0], position[1]}]["pit"] = 0;

	if (ERROR_CHECK) {
		for (auto& x: world) {
	   		std::cout << " [" << x.first[0] << " "<<x.first[1]<<": ["
				<< "[W,"<<x.second["worm"] << "] [ST,"<<x.second["stench"]
				<< "] [BR,"<< x.second["breeze"] <<"] [PT,"<<x.second["pit"]<<"] ]";
		}
		std::cout << '\n';
	}
}


// ======================================================================
// YOUR CODE ENDS
// ======================================================================
