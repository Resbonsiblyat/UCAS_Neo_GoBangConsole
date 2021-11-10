#include "GoBangManager.h"

GoBangManager::GoBangManager() {
    initBoard();
}

void GoBangManager::getNext(const char* temp) {
    int len = strlen(temp);///先求字符串的长度，便于循环赋值
    int i = 0, j = -1;
    value_of_next[0] = -1;
    while (i < len) 
        if (j == -1 || temp[i] == temp[j]) {
            value_of_next[++i] = ++j;
        }
        else j = value_of_next[j];
    
}

bool GoBangManager::bKMP(std::string a, std::string b) {
    int lena = a.size();
    int lenb = b.size();
    int i = 0, j = 0;
    while (i < lena && j < lenb) 
        if (j == -1 || a[i] == b[j]) {
            j++;
            i++;
        }
        else
            j = value_of_next[j];
    
    if (j == lenb)
        return true;
    else
        return false;
}

std:: string* GoBangManager::dirGenerator(int o_x, int o_y) {
    std::string* dir = new std::string[8];
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    //DIR1
    int dec = o_x > o_y ? o_y : o_x;
    int x = o_x - dec + 1;
    int y = o_y - dec + 1;

    int i = 0;
    while (x++ < SIZE && y++ < SIZE) {
        std::string buf;
        switch (checkerBoard.getCheckerBoardNode(x, y).getPlayer_id()) {

        case EMPTY:
            buf = "0";
            break;

        case WHITE:
            buf = "2";
            break;

        case BLACK:
            buf = "1";
            break;
        }

        dir[0].append(buf);

    }
    
    //DIR2
    dec = o_y + o_x - SIZE - 1;
    if (dec >= 0) {
        x = SIZE;
        y = dec + 1;
    }
    else {
        x = SIZE + dec;
        y = 1;
    }
    i = 0;
    while (x-- > 1 && y++ < SIZE) {
        std::string buf;
        switch (checkerBoard.getCheckerBoardNode(x, y).getPlayer_id()) {

        case EMPTY:
            buf = "0";
            break;

        case WHITE:
            buf = "2";
            break;

        case BLACK:
            buf = "1";
            break;
        }

        dir[1].append(buf);
    }


    //DIR3
    x = o_x;
    y = 1;
    while (y++ < SIZE) {
        std::string buf;
        switch (checkerBoard.getCheckerBoardNode(x, y).getPlayer_id()) {

        case EMPTY:
            buf = "0";
            break;

        case WHITE:
            buf = "2";
            break;

        case BLACK:
            buf = "1";
            break;
        }
        dir[2].append(buf);
    }

    //DIR4
    x = 1;
    y = o_y;
    while (x++ < SIZE) {
        std::string buf;
        switch (checkerBoard.getCheckerBoardNode(x, y).getPlayer_id()) {

        case EMPTY:
            buf = "0";
            break;

        case WHITE:
            buf = "2";
            break;

        case BLACK:
            buf = "1";
            break;
        }
        dir[3].append(buf);
    }

    for (int i = 4; i < 8; i++) 
        dir[i] = stringReverse(dir[i-4]);
    
    return dir;
}

std::string GoBangManager::stringReverse(std::string str) {
    std::string tmp = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        tmp += str.at(i);
    }
    return tmp;
}

int GoBangManager::referee(CheckerBoardNode checkerBoardNode) {
    
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    bool isBlack = checkerBoardNode.getPlayer_id() == BLACK ? true : false;

    int o_x = checkerBoardNode.getLocation_x();
    int o_y = checkerBoardNode.getLocation_y();

    std::string* dir = dirGenerator(o_x, o_y);
        
    if (isBlack) {
        //长连禁手判断
        bool tmpc[4] = { false }; 
        bool tag = false;
        getNext(OVERLINE_FH_STR.c_str());
        for (int i = 0; i < 4; i++) 
            if (bKMP(dir[i], OVERLINE_FH_STR)) {
                tmpc[i] = true;
                tag = true;
            }
        
        //黑棋先五判断获胜
        getNext(BLACK_WIN_STR.c_str());
        for (int i = 0; i < 4; i++) 
            if (tmpc[i] == false && bKMP(dir[i], BLACK_WIN_STR))
                return BLACK;
        if (tag) 
            return OVERLINE_FH;
        
        

        //三三禁手判断
        double Weight3 = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 2; j++) {
                Weight3 += DOUBLE_THREE_FH_WEIGHT[j] * iKMP(dir[i], DOUBLE_THREE_FH_STR[j]);
            }
        }
        if (Weight3 > 1.1) {
            return DOUBLE_THREE_FH;
        }

        //四四禁手判断
        double Weight4 = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                Weight4 += DOUBLE_FOUR_FH_WEIGHT[j] * iKMP(dir[i], DOUBLE_FOUR_FH_STR[j]);
            }
        }
        if (Weight4 > 1.1) {
            return DOUBLE_FOUR_FH;
        }
    }
    
    getNext(WHITE_WIN_STR.c_str());

    for(int i = 0; i < 4; i++)
        if (bKMP(dir[i], WHITE_WIN_STR))
            return WHITE;

    return EMPTY;
}

char* GoBangManager::StringToCharArr(std::string str) {
    char* arr = new char[str.length()];
    for (int i = 0; i < str.length(); i++) {
        arr[i] = str.at(i);
    }
    return arr;
}

int GoBangManager::iKMP(std::string StrLong, std::string StrShort) {
    int count = 0;
    char* StrLongArr = StringToCharArr(StrLong);
    char* StrShortArr = StringToCharArr(StrShort);
    for (int i = 0; i < StrLong.length();) {
        int tmp = i;
        for (int j = 0; j < StrShort.length();) {
            if (StrLongArr[i] == StrShortArr[j]) {
                i++; j++;
                if (j == StrShort.length()) {
                    count += 1;
                    i = tmp + 1; j = 0;
                    break;
                }
            }
            else {
                i = tmp + 1; j = 0;
                break;
            }
        }
    }
    return count;
}

int GoBangManager::placePiece(int location_x, int location_y, int player_id) {
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    if (checkerBoard.getCheckerBoardNode(location_x, location_y).getPlayer_id() == EMPTY) {
        checkerBoard.setCheckerBoardNode(location_x, location_y, player_id);
        CheckerBoardNode checkerBoardNode = checkerBoard.getCheckerBoardNode(location_x, location_y);

        checkerBoard.recordStep(checkerBoardNode); //当前棋子压入栈

        //胜利逻辑，当前执子方checkerBoardNode.getPlayer_id() 获胜, 返回胜利者id，无人获胜则返回EMPTY
        
        return referee(checkerBoardNode);
       
    }
    else
        throw CBException("此处已经落子！");
}

void GoBangManager::retract() {
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    if(!checkerBoard.retract())
        throw CBException("无子可悔！");
    else if (!checkerBoard.retract()) {
        //说明是第一颗子黑棋落下后，白棋落子前选择悔棋，此时撤销黑子第一颗子，player_id设置为BLACK即可
    }
    //悔棋后双方各撤一子，所以无需更改player_id
}

int GoBangManager::getPlayer_id(int location_x, int location_y){
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    return checkerBoard.getCheckerBoardNode(location_x, location_y).getPlayer_id();
}

void GoBangManager::initBoard(){
    CheckerBoard& checkerBoard = CheckerBoard::getCheckerBoardInstance();
    checkerBoard.initBoard();
    this->InitBoardArray();
}


void GoBangManager::InitBoardArray(){

    int i, j;

    Board[0][0] = LeftUpCorner;
    Board[0][SIZE - 1] = RightUpCorner;
    Board[SIZE - 1][SIZE - 1] = RightDownCorner;
    Board[SIZE - 1][0] = LeftDownCorner;

    for (j = 1; j <= SIZE - 2; j++)
        Board[j][0] = LeftBoundary;

    for (i = 1; i <= SIZE - 2; i++)
        Board[0][i] = UpBoundary;


    for (j = 1; j <= SIZE - 2; j++)
        Board[j][SIZE - 1] = RightBoundary;


    for (i = 1; i <= SIZE - 2; i++)
        Board[SIZE - 1][i] = DownBoundary;


    for (j = 1; j <= SIZE - 2; j++)
        for (i = 1; i <= SIZE - 2; i++)
            Board[j][i] = Center;

}

void GoBangManager::refreshBoard() {
    for (int i = 1; i <= SIZE; i++) {
        for (int j = 1; j <= SIZE; j++) {

            int playerID = this->getCheckerBoardInstance().getCheckerBoardNode(i, j).getPlayer_id();
            
            if (playerID == BLACK)
                Board[i - 1][j - 1] = BLACK;
            else if (playerID == WHITE)
                Board[i - 1][j - 1] = WHITE;

          
        }
    }

    if (lastNode != NULL && lastNode->getPlayer_id() != EMPTY)
        if (lastNode->getPlayer_id() == BLACK)
            Board[lastNode->getLocation_x() - 1][lastNode->getLocation_y() - 1] = BLACKtem;
        else 
            Board[lastNode->getLocation_x() - 1][lastNode->getLocation_y() - 1] = WHITEtem;
}

void GoBangManager::setLastNode(int x, int y, int player) {
    this->lastNode->setLocation(x, y);
    this->lastNode->setPlayer_id(player);

}
//Only for test
void GoBangManager::display() {
    refreshBoard();
    char line = 'A';
    std::cout << std::endl;
    for (int j = 0; j <= SIZE - 1; j++)
    {
        std::cout.width(2);
        std::cout << SIZE - j << " " ;
        for (int i = 0; i <= SIZE - 1; i++)
        {
            switch (Board[j][i])
            {
            case LeftUpCorner:
                std::cout << "┏ ";
                break;

            case RightUpCorner:
                std::cout << "┓ ";
                break;

            case RightDownCorner:
                std::cout << "┛ ";
                break;

            case LeftDownCorner:
                std::cout << "┗ ";
                break;

            case LeftBoundary:
                std::cout << "┠ ";
                break;

            case UpBoundary:
                std::cout << "┯ ";
                break;

            case RightBoundary:
                std::cout << "┨ ";
                break;

            case DownBoundary: 
                std::cout << "┷ ";
                break;

            case Center: 
                std::cout << "┼ ";
                break;

            case BLACKtem:      // 黑子上一步
                std::cout << red << "▲" << yellow;
                break;

            case WHITEtem:      //白子上一步
                std::cout << green << "△" << yellow;
                break;

            case BLACK:      //黑子通常
                std::cout << red << "●" << yellow;
                break;

            case WHITE:
                std::cout << green << "○" << yellow;  //白子通常
                break;
            }
            if (i == SIZE - 1)
                std::cout << std::endl;
            
        }
    }
    std::cout << "   ";
    for (int i = 1; i <= SIZE; i++) {
        std::cout.width(2);
        std::cout << yellow << line++;
    }
    std::cout << std::endl;
}

bool GoBangManager::isBoardEmpty(){
    return CheckerBoard::getCheckerBoardInstance().isEmpty();
}

CheckerBoard GoBangManager::getCheckerBoardInstance() {
    return CheckerBoard::getCheckerBoardInstance();
}