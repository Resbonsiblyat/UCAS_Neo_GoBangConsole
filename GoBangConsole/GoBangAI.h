//#include <QDebug>
#include <QPoint>
#include <QMap>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

//�жϵķ���
#define RIGHT 0
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3

//���п��ܵ������Ȩ��
#define OTHER 0     //����
#define WIN 1       //1000000   5���ӣ�ȡʤ
#define LOSE 2      //-10000000 ����5���ӣ�ʧ��
#define FLEX4 3     //50000     ��4
#define flex4 4     //-100000   ���ֻ�4
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

enum gameResult { R_BLACK, R_WHITE, R_DRAW };//����Ӯ������Ӯ������

struct EVALUATION {
    int score;
    gameResult result;
    int STAT[8];//���沿�����εĸ���,�±�WIN=1Ϊ����5,LOSE=2Ϊ����5,FLEX4=3Ϊ�׻�4,BLOCK4=5Ϊ�׳�4,FLEX3=7Ϊ�׻�3
};
struct Points {
    QPoint pos[20];
    int score[20];//���ӷ�����ǰ��ʮ��0-19����
};
struct DECISION {
    QPoint pos;
    int eval;//��ֵ
};

class GoBangAI
{
public:
    int chesses[15][15] = {EMPTY};
    DECISION decision;
    int nodeNum = 0;

private:
    int stats[4][4][4][4][4][4];    //0 ��  1 ��    2 ��   3 �߽磬�洢����6��λ�õ����ӷֲ����
    Points points;                  //�������λ��

private:
    QPoint getXY(int row, int col, int dir, int rel);
    bool checkBound(int x, int y);
    QPoint findBestMoveGreedy(int player);                                      //����̰��
    int calcOnePosGreedy(int board[15][15], int row, int col, int player);      //��player(��ɫ���ɫ)̰��
    int statsScoreGreedy(int black, int white, int player);                     //�Ը����������player��ɫ̰��
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