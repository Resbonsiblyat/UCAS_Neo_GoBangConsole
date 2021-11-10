#pragma once
#include "CheckerBoard.h"
#define BLACKtem 20
#define WHITEtem 21
#define LeftUpCorner 10
#define RightUpCorner 11
#define RightDownCorner 3
#define LeftDownCorner 4
#define LeftBoundary 5
#define UpBoundary 6
#define RightBoundary 7
#define DownBoundary 8
#define Center 9
#define DOUBLE_THREE_FH 23
#define DOUBLE_FOUR_FH 24
#define OVERLINE_FH 25




class GoBangManager {

private:
	const std::string WHITE_WIN_STR = "22222"; //°×Ó®
	const std::string BLACK_WIN_STR = "11111"; //ºÚÓ®
	const std::string OVERLINE_FH_STR = "111111"; //³¤Á¬½ûÊÖ
	const std::string DOUBLE_THREE_FH_STR[2] = { "01110", "011010" };
	const double DOUBLE_THREE_FH_WEIGHT[2] = { 0.5, 1 };
	const std::string DOUBLE_FOUR_FH_STR[4] = { "11101", "211110", "111102", "011110"};
	const double DOUBLE_FOUR_FH_WEIGHT[4] = { 1, 1, 1, 0.5 };

	int value_of_next[20]; //Next array for KMP
	int Board[SIZE][SIZE];
	CheckerBoardNode *lastNode = new CheckerBoardNode();

	//solution 1
	//bool DFS(int location_x,int location_y);

	std::string stringReverse(std::string str);
	std::string* dirGenerator(int o_x, int o_y);
	char* StringToCharArr(std::string str);
	int iKMP(std::string StrLong, std::string StrShort);
	//solution 2
	bool bKMP(std::string StrLong,std::string StrShort); // Param a is the main string , param b is the temp string 
	//for example  StrLong[] =  "000111002201012" and StrShort[] = "111". In this case, we can find b string in a so we get true as return.

	void getNext(const char* temp); // Update Next Array for KMP


	int referee(CheckerBoardNode checkerBoardNode); // Judge the result after every piece placed.
	void InitBoardArray();
	void refreshBoard();
	
public:
	GoBangManager();
    int placePiece(int location_x, int location_y,int player_id);
	void retract();
    int getPlayer_id(int location_x, int location_y);
    void initBoard();
	void setLastNode(int x, int y, int player);

	//Only for test
	void display();
	CheckerBoard getCheckerBoardInstance();
    bool isBoardEmpty();
};
