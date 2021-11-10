#include "CheckerBoard.h"

CheckerBoard CheckerBoard::instance;

CheckerBoard::CheckerBoard() {
	this->board = new CheckerBoardNode * [(int)(size + 2)];
	for (int i = 0; i < size + 2; i++) {
		board[i] = new CheckerBoardNode[(int)(size + 2)];
		/*
		for (int j = 0; j < size + 2; j++) {
			board[i][j].setLocation(i, j);
			board[i][j].setPlayer_id(-1);
		}*/
	}

	for (int i = 0; i < size + 2; i++) {
		board[0][i].setPlayer_id(BOARDER);
		board[16][i].setPlayer_id(BOARDER);
		board[i][16].setPlayer_id(BOARDER);
		board[i][0].setPlayer_id(BOARDER);
	}
}

void CheckerBoard::setCheckerBoardNode(int location_x, int location_y, int player_id) {
	if (location_x > 0 && location_y > 0 && location_x <= size && location_y <= size) {
		if (player_id != -1) {
			board[location_x][location_y].setLocation(location_x, location_y);
			board[location_x][location_y].setPlayer_id(player_id);
		}
		else throw CBException("落子选手错误");
	}
	else throw CBException("落子位置错误");
}

CheckerBoardNode CheckerBoard::getCheckerBoardNode(int location_x, int location_y) {
	if (location_x > 0 && location_y > 0 && location_x <= size && location_y <= size) {
		return board[location_x][location_y];
	}
	else throw CBException("读取当前位置棋子错误");
}

void CheckerBoard::recordStep(CheckerBoardNode checkerBoardNode) {
	steps.push(checkerBoardNode);
}

CheckerBoardNode* CheckerBoard::getRecentStep() {
	if (!steps.empty())
		return &steps.top();
	else 
		return nullptr;
}

bool CheckerBoard::retract() {

	CheckerBoardNode* temp = getRecentStep();
	if (temp == NULL)
		return false;
	int temp_x = temp->getLocation_x();
	int temp_y = temp->getLocation_y();
    board[temp_x][temp_y].setPlayer_id(EMPTY);
	steps.pop();
	return true;
}

void CheckerBoard::initBoard(){
    while(retract());
}

CheckerBoard& CheckerBoard::getCheckerBoardInstance() {
    return instance;
};

//Only for test


bool CheckerBoard::isEmpty(){
    return steps.empty();
}


