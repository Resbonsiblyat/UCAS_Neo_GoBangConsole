// GoBangConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "GoBangAI.h"
#include "GoBangManager.h"

GoBangManager* goBangManager;
GoBangAI* goBangAI;

int rounds = 0;
void init() {
    goBangManager = new GoBangManager();
    goBangAI = new GoBangAI();

    if (rounds == 2) {
        goBangAI->chesses[7][7] = WHITE;
        goBangManager->placePiece(8, 8, WHITE);
        goBangManager->setLastNode(8, 8, WHITE);
    }
}

int main()
{
    int playerScore = 0;
    int AIScore = 0;
    bool isBlack = true;
    while (rounds++ < 2) {
        init();
        if (rounds == 2)
            isBlack = false;
        while (1) {
            std::cout << green << "第" << rounds << "局\t输入坐标落子，例如H8（不区分大小写）表示天元处落子" << std::endl;
            std::cout << green << "当前玩家得分：" << red << playerScore << green << "\t当前AI得分：" << red << AIScore << std::endl;
            std::string playerColorStr = rounds == 1 ? "黑色" : "白色";
            std::string playerFS = rounds == 1 ? "先手" : "后手";
            std::string AIColorStr = rounds == 1 ? "白色" : "黑色";
            std::string AIFS = rounds == 1 ? "后手" : "先手";
            std::cout << yellow << "玩家执" << playerColorStr << red << "●" << yellow << playerFS << std::endl;
            std::cout << "AI执" << AIColorStr << green << "○" << yellow << AIFS << std::endl;
            std::cout << "  ";
            goBangManager->display();
            int x, y; char c_y;
             if (isBlack && rounds == 1) {
                std::cin >> c_y >> x;
                x = SIZE - x + 1;
                if (x < 1 || x > SIZE) {
                    std::cout << "请输入正确的行坐标" << std::endl;
                    system("pause");
                    system("cls");
                    continue;
                }
                
                if (c_y >= 'a' && c_y <= 'z')
                    y = c_y - 'a' + 1;
                else if (c_y >= 'A' && c_y <= 'Z')
                    y = c_y - 'A' + 1;
                else {
                    std::cout << "请输入正确的列坐标" << std::endl;
                    system("pause");
                    system("cls");
                    continue;
                }
                   
                goBangAI->chesses[x - 1][y - 1] = BLACK;
            }
            else if (isBlack && rounds == 2) {
                QPoint result = goBangAI->AI_Move();
                x = result.x();
                y = result.y();
                goBangAI->chesses[x][y] = WHITE;
                x++;
                y++;
            }
            else if (!isBlack && rounds == 1) {
                QPoint result = goBangAI->AI_Move();
                x = result.x();
                y = result.y();
                goBangAI->chesses[x][y] = WHITE;
                x++;
                y++;
            }
            else {
                std::cin >> c_y >> x;
                x = SIZE - x + 1;
                if (x < 1 || x > SIZE) {
                    std::cout << "请输入正确的行坐标" << std::endl;
                    system("pause");
                    system("cls");
                    continue;
                }
                if (c_y >= 'a' && c_y <= 'z')
                    y = c_y - 'a' + 1;
                else if(c_y >= 'A' && c_y <= 'Z')
                    y = c_y - 'A' + 1;
                else {
                    std::cout << "请输入正确的列坐标" << std::endl;
                    system("pause");
                    system("cls");
                    continue;
                }
                goBangAI->chesses[x - 1][y - 1] = BLACK;
            }

            try {
                int color;
                if (rounds == 1)
                    if (isBlack)
                        color = BLACK;
                    else
                        color = WHITE;
                else
                    if (isBlack)
                        color = WHITE;
                    else
                        color = BLACK;
                int result = goBangManager->placePiece(x, y, color);
                goBangManager->setLastNode(x, y, color);
                if (result != EMPTY) {
                    system("cls");
                    
                    goBangManager->display();

                    if (rounds == 2)
                        if (result == BLACK)
                            result = WHITE;
                        else if (result == WHITE)
                            result = BLACK;
                    
                        
                    if (result == BLACK) {
                        std::cout << "黑棋五连珠获胜！" << std::endl;
                        if (rounds == 1)
                            playerScore += 2;
                        else
                            AIScore += 2;
                        system("pause");
                        system("cls");
                        break;
                    }
                    else if (result == WHITE)
                        std::cout << "白棋五连珠获胜！" << std::endl;
                    else if (result == OVERLINE_FH)
                        std::cout << "长连禁手，白棋获胜！" << std::endl;
                    else if (result == DOUBLE_THREE_FH)
                        std::cout << "三三禁手，白棋获胜！" << std::endl;
                    else if (result == DOUBLE_FOUR_FH)
                        std::cout << "四四禁手，白棋获胜！" << std::endl;
                    
                    if (rounds == 2)
                        playerScore += 2;
                    else
                        AIScore += 2;
                    system("pause");
                    system("cls");
                    break;
                }
            }
            catch (CBException e) {
                std::cout << e.msg << std::endl;
                system("pause");
                system("cls");
                continue;
            }

            isBlack = !isBlack;
            system("cls");
        }
    }
        
    std::cout << green << "终局！玩家最终得分为：" << red << playerScore << green << "AI最终得分为： " << red << AIScore << std::endl;
    system("pause");
    return 0;
}


