//#include <QDebug>
#include <QPoint>
#include <QMap>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

//判断的方向
#define RIGHT 0
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3

//所有可能的情况及权重
#define OTHER 0     //其他
#define WIN 1       //1000000   5连子，取胜
#define LOSE 2      //-10000000 对手5连子，失败
#define FLEX4 3     //50000     活4
#define flex4 4     //-100000   对手活4
#define BLOCK4 5    //400
#define block4 6    //-100000
#define FLEX3 7     //400
#define flex3 8     //-8000
#define BLOCK3 9    //20
#define block3 10   //-40
#define FLEX2 11    //20
#define flex2 12    //-40
#define BLOCK2 13   //1
#define block2 14   //-2
#define FLEX1 15    //1
#define flex1 16    //-2

enum gameResult { R_BLACK, R_WHITE, R_DRAW };//黑棋赢，白棋赢，和棋

struct EVALUATION {
    int score;
    gameResult result;
    int STAT[8];//储存部分棋形的个数,下标WIN=1为白连5,LOSE=2为黑连5,FLEX4=3为白活4,BLOCK4=5为白冲4,FLEX3=7为白活3
};
struct Points {
    QPoint pos[20];
    int score[20];//落子分数，前二十从0-19排列
};
struct DECISION {
    QPoint pos;
    int eval;//估值
};

class GoBangAI
{
public:
    int chesses[15][15] = {EMPTY};
    DECISION decision;
    int nodeNum = 0;

private:
    int stats[4][4][4][4][4][4];    //0 空  1 黑    2 白   3 边界，存储连续6个位置的棋子分部情况
    Points points;                  //最佳落子位置

private:
    QPoint getXY(int row, int col, int dir, int rel);
    bool checkBound(int x, int y);
    QPoint findBestMoveGreedy(int player);                                      //单步贪心
    int calcOnePosGreedy(int board[15][15], int row, int col, int player);      //对player(黑色或白色)贪心
    int statsScoreGreedy(int black, int white, int player);                     //对给定的情况和player颜色贪心
    void init_stats();
    Points seekPoints(int board[15][15]);
    void copyBoard(int A[15][15], int B[15][15]);
    void reverseBoard(int A[15][15], int B[15][15]);
    EVALUATION evaluate(int board[15][15], bool needPrint = false);
    int analyse(int board[15][15], int depth, int alpha, int beta);

    bool analyse_kill(int board[15][15], int depth);
    QList<QPoint> seek_kill_points(int board[15][15]);

public:
    GoBangAI();

    QPoint AI_Move();
};