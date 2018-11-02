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
	if(start)
	{
		start = false;
		std::cout<<"\n--\n";
		init_map();
	}
	update_map(stench,breeze);
	// std::cout<<"stench: "<<stench<<"\nbreeze: "<<breeze<<"\nglitter: "<<glitter<<"\nbump: "<<bump<<"\nscream: "<<scream<<"\n";
	// std::cout<<"Position: "<<position[0]<<","<<position[1]<<"\n\n";
	num_moves++;
	if (glitter)
	{
		gold = true;
		return GRAB;
	}
	if(!gold&&!bump)
	{
		if(steps.empty())
			steps.push({position[0],position[1]});
		if(!steps.empty()&&(steps.top()[0]!=position[0] || steps.top()[1]!=position[1]))
			steps.push({position[0],position[1]});
		//std::cout<<"XDXDXDXDXDXXD\n";
	}

	// if(next_pos[0]!= -1&&(position[0]!=next_pos[0]||position[1]!=next_pos[1]))
	// {
	// 	//we need to get there.
	// 	//follow the if gold algo
	// 	std::string face_dir;
	//
	// 	if(next_pos[1]-position[1]<0)
	// 	{
	// 		face_dir = "L";
	// 	}
	// 	else if(next_pos[1]-position[1]>0&&(position[1]<=width&&world[{position[0],position[1]+1}]["pit"]!=1))
	// 	{
	// 		face_dir = "R";
	// 	}
	// 	else
	// 	{
	// 		if(next_pos[0]-position[0]<0) //move down
	// 		{
	// 			face_dir = "D";
	// 		}
	// 		else if(next_pos[0]-position[0]>0)
	// 		{
	// 			face_dir = "U";
	// 		}
	// 		else
	// 		{
	// 			std::cout<<"-------------ERROR!!!\n";
	// 		}
	// 	}
	// 	if(compass[dir]!=face_dir)
	// 	{
	// 		return turnLeft();
	// 	}
	// 	else
	// 	{
	// 		return goForward();
	// 	}
	//
	// 	//   okay to now the direction is determined. now to figure
	// 	// out how to make it go in that direction.
	// 	// if(next_pos[1]-position[1]<0)
	// 	// {
	// 	// 	face_dir = "L";
	// 	// }
	// 	// else if(next_pos[1]-position[1]>0)
	// 	// {
	// 	// 	face_dir = "R";
	// 	// }
	// 	// else
	// 	// {
	// 	// 	std::cout<<"----------------Error\n";
	// 	//
	// 	// }
	//
	//
	// }
	// if(next_pos[0]==position[0] && next_pos[1]==position[1])
	// {
	// 	next_pos[0]=-1;
	// 	next_pos[1]=-1;
	// 	if(breeze)
	// 	{
	// 		if(position[1]<=width)
	// 			world[{position[0],position[1]+1}]["pit"] = 1;
	//
	// 	}
	// }
	if(bump)
	{
		//steps.pop();
		if(compass[dir] == "R")
		{
			position[1] = position[1]-1;
			width = position[1];
			std::cout<<"width: "<<width<<"\n";
			if(position[0]<height)
			{
				return turnLeft();
			}
			return turnRight();
		}
		else if(compass[dir] == "L")
		{
			position[1] = position[1] +1;
			return turnLeft();

		}
		else if(compass[dir] == "U")
		{
			position[0] = position[0]-1;
			height = position[0];
			std::cout<<"height: "<<height<<"\n";
			if(position[1]<width)
			{
				return turnRight();
			}
			return turnLeft();
		}
		else if(compass[dir] == "D")
		{
			position[0] = position[0]+1;
			if(position[0]==0 && position[1]==0)
			{
				return CLIMB;
			}
		}
	}
	if(position[0] ==0 && position[1] ==0 && breeze)
	{
		return CLIMB;
	}
	if(stench && arrow)
	{
		arrow = false;
		return SHOOT;
	}
	if(scream)
	{
		worm = false;
		return goForward();
	}

	if (gold)
	{
		//std::cout<<"got gold\n";

		/*----------------*/
		//new using stack positions

		// while(!steps.empty())
		// {
		// 	std::cout<<steps.top()[0]<<","<<steps.top()[1]<<" ";
		// 	steps.pop();
		// }
		// if(position[0] == 0 && position[1] == 0)
		// {
		// 	return CLIMB;
		// }
		if(steps.empty())
			return CLIMB;
		int bs[2] = {steps.top()[0],steps.top()[1]};
		//comparing the two positions.
		string face_dir;
		std::cout<<"position: ["<<position[0]<<","<<position[1]<<"]\n";
		std::cout<<"back step: ["<<bs[0]<<","<<bs[1]<<"]\n";
		while(bs[0]==position[0]&&bs[1]==position[1])
		{
			steps.pop();
			bs[0] = steps.top()[0];
			bs[1] = steps.top()[1];
			std::cout<<"back step: ["<<bs[0]<<","<<bs[1]<<"]\n";
		}
		std::cout<<"diff: "<<(bs[0]-position[0])<<", "<<(bs[1]-position[1])<<"\n";
		if(bs[0]-position[0]<0) //move down
		{
			face_dir = "D";
		}
		else if(bs[0]-position[0]>0)
		{
			face_dir = "U";
		}
		else if(bs[1]-position[1]<=-1)
		{
			face_dir = "L";
		}
		else if(bs[1]-position[1]>=1)
		{
			face_dir = "R";
		}
		else
		{
			std::cout<<"----------------Error\n";

		}
		//if facing rigt dir.
		if(compass[dir]!=face_dir)
		{
			return turnLeft();
		}
		else //is right direction
		{
			steps.pop();
			return goForward();
		}



		/*----------------*/


		//return back to origin.


	// 	if(position[1]>0)
	// 	{
	// 		if(compass[dir] != "L")
	// 		{
	// 			return turnLeft();
	// 		}
	// 		position[1] = position[1] -1;
	// 		return FORWARD;
	// 	}
	// 	if(position[0]>0)
	// 	{
	// 		if(compass[dir] !="D")
	// 		{
	//
	// 			return turnLeft();
	// 		}
	// 		position[0] = position[0]-1;
	// 		return FORWARD;
	// 	}
	// 	return CLIMB;
	// }

	}

	if(breeze)
	{
		if(position[0]==0)
		{
			//bottom row
			if(compass[dir]=="R" || compass[dir]=="U")
			{
				return turnLeft();
			}
			else if(compass[dir]=="L")
			{
				return goForward();
			}
			// next_pos[0]=position[0]+1;
			// next_pos[1] = position[1]-1;
			// return turnLeft();




		}
	}
	return goForward();










	// Print Command Menu
	// std::cout << "Press 'w' to Move Forward  'a' to 'Turn Left' 'd' to 'Turn Right'" << std::endl;
	// std::cout << "Press 's' to Shoot         'g' to 'Grab'      'c' to 'Climb'" << std::endl;
	//
	// std::cout<<"stench: "<<stench<<"\nbreeze: "<<breeze<<"\nglitter: "<<glitter<<"\nbump: "<<bump<<"\nscream: "<<scream<<"\n";
	// // Get Input
	// std::cout << "Please input: ";
	// char userInput;
	// std::cin >> userInput;
	// std::cin.ignore(9999, '\n');
	//
	// // Return Action Associated with Input
	// if ( userInput == 'w' )
	// 	return FORWARD;
	//
	// if ( userInput == 'a' )
	// 	return TURN_LEFT;
	//
	// if ( userInput == 'd' )
	// 	return TURN_RIGHT;
	//
	// if ( userInput == 's' )
	// 	return SHOOT;
	//
	// if ( userInput == 'g' )
	// 	return GRAB;
	//
	// return CLIMB;
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

Agent::Action MyAI::turnLeft()
{
	if(dir == 0)
		dir = 3;
	else
		dir--;
	return Agent::TURN_LEFT;
}
Agent::Action MyAI::turnRight()
{
	dir =(dir+1)%4;
	return TURN_RIGHT;
}
Agent::Action MyAI::goForward()
{
	if(compass[dir] == "R")
		position[1] = position[1]+1;
	else if(compass[dir] == "L")
		position[1] = position[1] -1;
	else if(compass[dir] == "U")
		position[0] = position[0]+1;
	else if(compass[dir] == "D")
		position[0] = position[0]-1;
	return FORWARD;

}
void MyAI::init_map()
{
	for(int row = 0;row<6;row++)
	{
		for(int col = 0;col<6;col++)
		{

			world[{row,col}]["worm"]=-1;
			world[{row,col}]["stench"]=-1;
			world[{row,col}]["breeze"]=-1;
			world[{row,col}]["pit"]=-1;
		}
	}
	// for (auto& x: world){
 //   		std::cout << " [" << x.first[0] << " "<<x.first[1]<<": ["
	// 		<< "[worm, "<<x.second["worm"] << "] [stench, "<<x.second["stench"]
	// 		<< "] [breeze, "<< x.second["breeze"] <<"] [pit, "<<x.second["pit"]<<"] ]";
	// }
 // std::cout << '\n';
}
void MyAI::update_map(bool stench,bool breeze)
{
	int s=0; int b=0;
	if(stench==true)
		s=1;
	if(breeze == true)
		b=1;
	world[{position[0],position[1]}]["worm"]=0;
	world[{position[0],position[1]}]["stench"]=s;
	world[{position[0],position[1]}]["breeze"]=b;
	world[{position[0],position[1]}]["pit"]=0;
// 	for (auto& x: world){
//    		std::cout << " [" << x.first[0] << " "<<x.first[1]<<": ["
// 			<< "[w,"<<x.second["worm"] << "] [s,"<<x.second["stench"]
// 			<< "] [b,"<< x.second["breeze"] <<"] [p,"<<x.second["pit"]<<"] ]";
// 	}
// std::cout << '\n';

}


// ======================================================================
// YOUR CODE ENDS
// ======================================================================
