#pragma once
#include<iostream>

class CheckerBoardNode {


private:
	int location_x;
	int location_y;
	int player_id;

public:
	CheckerBoardNode();

	//setters
	void setLocation(int location_x,int location_y);
	void setPlayer_id(int player_id);

	//getters
	int getLocation_x();
	int getLocation_y();
	int getPlayer_id();

};
