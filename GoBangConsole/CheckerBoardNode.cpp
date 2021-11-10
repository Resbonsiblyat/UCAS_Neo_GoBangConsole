#include "CheckerBoardNode.h"

CheckerBoardNode::CheckerBoardNode() {
	//initialize
	location_x = 0;
	location_y = 0;
	player_id = 0;
}

void CheckerBoardNode::setLocation(int location_x, int location_y) {
	this->location_x = location_x;
	this->location_y = location_y;
}

void CheckerBoardNode::setPlayer_id(int player_id) {
	this->player_id = player_id;
}

int CheckerBoardNode::getLocation_x() {
	return this->location_x;
}

int CheckerBoardNode::getLocation_y() {
	return this->location_y;
}

int CheckerBoardNode::getPlayer_id() {
	return this->player_id;
}
