#pragma once
#include <iostream>
#include "CheckerBoardNode.h"
#include "CBException.h"

#include "ConsoleColor.h"

#include <stack>

#define WHITE 2
#define BLACK 1
#define EMPTY 0
#define BOARDER 3
#define SIZE 15

class CheckerBoard {

private:
	static CheckerBoard instance;
	const int size = SIZE;
	CheckerBoardNode** board;
	std::stack<CheckerBoardNode> steps;


	CheckerBoardNode* getRecentStep();


protected:
	CheckerBoard();

public:
	static CheckerBoard & getCheckerBoardInstance();
	void setCheckerBoardNode(int location_x, int location_y, int player_id);
	CheckerBoardNode getCheckerBoardNode(int location_x, int location_y);
	void recordStep(CheckerBoardNode checkerBoardNode);
	bool retract();
    void initBoard();
    bool isEmpty();

};
