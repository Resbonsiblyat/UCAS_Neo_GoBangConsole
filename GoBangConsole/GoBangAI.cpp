#include "GoBangAI.h"

GoBangAI::GoBangAI()
{
    init_stats();
   
}

bool GoBangAI::checkBound(int x, int y) {
    if (x >= 0 && x < 15 && y >= 0 && y < 15)return true;
    else return false;
}
QPoint GoBangAI::getXY(int row, int col, int dir, int rel) {
    QPoint p;
    if (dir == RIGHT) {
        p.setX(row);
        p.setY(col + rel);
    }
    else if (dir == UP) {
        p.setX(row - rel);
        p.setY(col);
    }
    else if (dir == UPRIGHT) {
        p.setX(row - rel);
        p.setY(col + rel);
    }
    else if (dir == UPLEFT) {
        p.setX(row - rel);
        p.setY(col - rel);
    }
    return p;
}
int GoBangAI::calcOnePosGreedy(int board[15][15], int row, int col, int C_ME) {
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            QPoint start = getXY(row, col, RIGHT + i, j - 4);
            QPoint end = getXY(start.x(), start.y(), RIGHT + i, 4);
            if (checkBound(start.x(), start.y()) && checkBound(end.x(), end.y())) {
                int blackChess = 0;
                int whiteChess = 0;
                for (int k = 0; k < 5; ++k) {//���������5��λ�ý����ж�
                    QPoint tmp = getXY(start.x(), start.y(), RIGHT + i, k);
                    if (board[tmp.x()][tmp.y()] == BLACK)blackChess++;
                    if (board[tmp.x()][tmp.y()] == WHITE)whiteChess++;
                }
                sum += statsScoreGreedy(blackChess, whiteChess, C_ME);
            }
        }
    }
    return sum;
}
int GoBangAI::statsScoreGreedy(int black, int white, int C_ME) {
    //��5
    if (C_ME == BLACK && black == 5)return 9999999;
    if (C_ME == WHITE && white == 5)return 9999999;
    //ȫ��
    if (black == 0 && white == 0)return 7;
    //polluted
    else if (black >= 1 && white >= 1)return 0;
    else if (C_ME == BLACK) {
        if (black == 1 && white == 0)return 35;
        else if (black == 2 && white == 0)return 800;
        else if (black == 3 && white == 0)return 15000;
        else if (black == 4 && white == 0)return 800000;
        else if (black == 0 && white == 1)return 15;
        else if (black == 0 && white == 2)return 400;
        else if (black == 0 && white == 3)return 1800;
        else return 100000;
    }
    else {
        if (black == 1 && white == 0)return 15;
        else if (black == 2 && white == 0)return 400;
        else if (black == 3 && white == 0)return 1800;
        else if (black == 4 && white == 0)return 100000;
        else if (black == 0 && white == 1)return 35;
        else if (black == 0 && white == 2)return 800;
        else if (black == 0 && white == 3)return 15000;
        else return 800000;
    }
}
QPoint GoBangAI::findBestMoveGreedy(int C_ME) {
    int bestScore = 0;
    int bestRow = 0, bestCol = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (chesses[i][j] == EMPTY) {//�յ�λ��
                int score = calcOnePosGreedy(chesses, i, j, C_ME);
                if (bestScore < score) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    QPoint p(bestRow, bestCol);
    return p;
}
void GoBangAI::init_stats() {
    memset(stats, 0, sizeof(stats));//ȫ����Ϊ0
    //����5,aiӮ
    stats[2][2][2][2][2][2] = WIN;
    stats[2][2][2][2][2][0] = WIN;
    stats[0][2][2][2][2][2] = WIN;
    stats[2][2][2][2][2][1] = WIN;
    stats[1][2][2][2][2][2] = WIN;
    stats[3][2][2][2][2][2] = WIN;//�߽翼��
    stats[2][2][2][2][2][3] = WIN;
    //����5,ai��
    stats[1][1][1][1][1][1] = LOSE;
    stats[1][1][1][1][1][0] = LOSE;
    stats[0][1][1][1][1][1] = LOSE;
    stats[1][1][1][1][1][2] = LOSE;
    stats[2][1][1][1][1][1] = LOSE;
    stats[3][1][1][1][1][1] = LOSE;
    stats[1][1][1][1][1][3] = LOSE;
    //�׻�4
    stats[0][2][2][2][2][0] = FLEX4;
    //�ڻ�4
    stats[0][1][1][1][1][0] = flex4;
    //�׻�3
    stats[0][2][2][2][0][0] = FLEX3;
    stats[0][0][2][2][2][0] = FLEX3;
    stats[0][2][0][2][2][0] = FLEX3;
    stats[0][2][2][0][2][0] = FLEX3;
    //�ڻ�3
    stats[0][1][1][1][0][0] = flex3;
    stats[0][0][1][1][1][0] = flex3;
    stats[0][1][0][1][1][0] = flex3;
    stats[0][1][1][0][1][0] = flex3;
    //�׻�2
    stats[0][2][2][0][0][0] = FLEX2;
    stats[0][2][0][2][0][0] = FLEX2;
    stats[0][2][0][0][2][0] = FLEX2;
    stats[0][0][2][2][0][0] = FLEX2;
    stats[0][0][2][0][2][0] = FLEX2;
    stats[0][0][0][2][2][0] = FLEX2;
    //�ڻ�2
    stats[0][1][1][0][0][0] = flex2;
    stats[0][1][0][1][0][0] = flex2;
    stats[0][1][0][0][1][0] = flex2;
    stats[0][0][1][1][0][0] = flex2;
    stats[0][0][1][0][1][0] = flex2;
    stats[0][0][0][1][1][0] = flex2;
    //�׻�1
    stats[0][2][0][0][0][0] = FLEX1;
    stats[0][0][2][0][0][0] = FLEX1;
    stats[0][0][0][2][0][0] = FLEX1;
    stats[0][0][0][0][2][0] = FLEX1;
    //�ڻ�1
    stats[0][1][0][0][0][0] = flex1;
    stats[0][0][1][0][0][0] = flex1;
    stats[0][0][0][1][0][0] = flex1;
    stats[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:��5�кڸ���,y:��5�а׸���,ix:��5�кڸ���,iy:��5�а׸���
    for (p1 = 0; p1 < 4; ++p1) {
        for (p2 = 0; p2 < 3; ++p2) {
            for (p3 = 0; p3 < 3; ++p3) {
                for (p4 = 0; p4 < 3; ++p4) {
                    for (p5 = 0; p5 < 3; ++p5) {
                        for (p6 = 0; p6 < 4; ++p6) {
                            x = y = ix = iy = 0;

                            if (p1 == 1)x++;
                            else if (p1 == 2)y++;

                            if (p2 == 1) { x++; ix++; }
                            else if (p2 == 2) { y++; iy++; }

                            if (p3 == 1) { x++; ix++; }
                            else if (p3 == 2) { y++; iy++; }

                            if (p4 == 1) { x++; ix++; }
                            else if (p4 == 2) { y++; iy++; }

                            if (p5 == 1) { x++; ix++; }
                            else if (p5 == 2) { y++; iy++; }

                            if (p6 == 1)ix++;
                            else if (p6 == 2)iy++;

                            if (p1 == 3 || p6 == 3) {//�б߽�
                                if (p1 == 3 && p6 != 3) {//��߽�
                                    //�׳�4
                                    if (ix == 0 && iy == 4) {//���ұ��п�λ�ǻ�4Ҳû��ϵ����Ϊ��4Ȩ��Զ���ڳ�4���ټ��ϳ�4Ȩ�ر仯���Բ���
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (ix == 4 && iy == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (ix == 0 && iy == 3) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (ix == 3 && iy == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (ix == 0 && iy == 2) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (ix == 2 && iy == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                                else if (p6 == 3 && p1 != 3) {//�ұ߽�
                                   //�׳�4
                                    if (x == 0 && y == 4) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (x == 4 && y == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (x == 3 && y == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (x == 0 && y == 3) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (x == 2 && y == 0) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (x == 0 && y == 2) {
                                        if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                            stats[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                            }
                            else {//�ޱ߽�
                               //�׳�4
                                if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                }
                                //�ڳ�4
                                if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = block4;
                                }
                                //����3
                                if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                }
                                //����3
                                if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = block3;
                                }
                                //����2
                                if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                }
                                //����2
                                if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
                                    if (stats[p1][p2][p3][p4][p5][p6] == 0)
                                        stats[p1][p2][p3][p4][p5][p6] = block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

EVALUATION GoBangAI::evaluate(int board[15][15], bool needPrint) {
    //������Ȩ��
    int weight[17] = { 0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };

    int i, j, type;
    int stat[4][17];//ͳ��4��������ÿ������ĸ���
    memset(stat, 0, sizeof(stat));


    int A[17][17];//3��ʾ�߽�
    for (int i = 0; i < 17; ++i)A[i][0] = 3;
    for (int i = 0; i < 17; ++i)A[i][16] = 3;
    for (int j = 0; j < 17; ++j)A[0][j] = 3;
    for (int j = 0; j < 17; ++j)A[16][j] = 3;
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            A[i + 1][j + 1] = board[i][j];

    //����
    for (i = 1; i <= 15; ++i) {
        for (j = 0; j < 12; ++j) {
            type = stats[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            stat[0][type]++;
        }
    }
    //����
    for (j = 1; j <= 15; ++j) {
        for (i = 0; i < 12; ++i) {
            type = stats[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            stat[1][type]++;
        }
    }
    //����������
    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 12; ++j) {
            type = stats[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //����������
    for (i = 0; i < 12; ++i) {
        for (j = 5; j < 17; ++j) {
            type = stats[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
            stat[3][type]++;
        }
    }

    EVALUATION eval;
    memset(eval.STAT, 0, sizeof(eval.STAT));

    int score = 0;
    for (i = 1; i < 17; ++i) {
        score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//�����Ʒ�

        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//ͳ�����з����ϲ������͵ĸ���
        if (i == WIN)eval.STAT[WIN] = count;
        else if (i == LOSE)eval.STAT[LOSE] = count;
        else if (i == FLEX4)eval.STAT[FLEX4] = count;
        else if (i == BLOCK4)eval.STAT[BLOCK4] = count;
        else if (i == FLEX3)eval.STAT[FLEX3] = count;
    }

  
    eval.result = R_DRAW;

    //��Ӯ
    if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
    //��Ӯ
    else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

    eval.score = score;
    return eval;
}

Points GoBangAI::seekPoints(int board[15][15]) {
    bool B[15][15];//�������
    int worth[15][15];
    Points best_points;

    memset(B, 0, sizeof(B));
    for (int i = 0; i < 15; ++i) {//ÿ���ǿյ㸽��8����������3�����,����Խ������Ϊ����
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] != EMPTY) {
                for (int k = -3; k <= 3; ++k) {
                    if (i + k >= 0 && i + k < 15) {
                        B[i + k][j] = true;
                        if (j + k >= 0 && j + k < 15)B[i + k][j + k] = true;
                        if (j - k >= 0 && j - k < 15)B[i + k][j - k] = true;
                    }
                    if (j + k >= 0 && j + k < 15)B[i][j + k] = true;
                }
            }
        }
    }

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            worth[i][j] = -INT_MAX;
            if (board[i][j] == EMPTY && B[i][j] == true) {
                //board[i][j]=C_BLACK;
                worth[i][j] = calcOnePosGreedy(board, i, j, WHITE);
                //worth[i][j]=evaluate(board).score;
                //board[i][j]=C_NONE;
            }
        }
    }

    int w;
    for (int k = 0; k < 20; ++k) {
        w = -INT_MAX;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (worth[i][j] > w) {
                    w = worth[i][j];
                    QPoint tmp(i, j);
                    best_points.pos[k] = tmp;
                }
            }
        }

        int x = best_points.pos[k].x(), y = best_points.pos[k].y();
        board[x][y] = WHITE;
        best_points.score[k] = evaluate(board).score;
        board[x][y] = EMPTY;

        worth[best_points.pos[k].x()][best_points.pos[k].y()] = -INT_MAX;//�������һ��,������һ���λ�úͷ���
    }
    return best_points;
}

void GoBangAI::copyBoard(int(*A)[15], int(*B)[15]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j] == EMPTY)B[i][j] = EMPTY;
            else if (A[i][j] == BLACK)B[i][j] = BLACK;
            else B[i][j] = WHITE;
        }
    }
}
void GoBangAI::reverseBoard(int(*A)[15], int(*B)[15]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j] == EMPTY)B[i][j] = EMPTY;
            else if (A[i][j] == BLACK)B[i][j] = WHITE;
            else B[i][j] = BLACK;
        }
    }
}

int GoBangAI::analyse(int(*board)[15], int depth, int alpha, int beta) {
    EVALUATION EVAL = evaluate(board);
    if (depth == 0 || EVAL.result != R_DRAW) {//�ִ������/���ģ�����ӿ��Էֳ���Ӯ����ôֱ�ӷ��ؽ��������Ҫ������
        nodeNum += 1;
        if (depth == 0) {
            Points P;
            P = seekPoints(board);

            return P.score[0];//�������λ�ö�Ӧ����߷�
        }
        else return EVAL.score;
    }
    else if (depth % 2 == 0) {//max��,�ҷ�(��)����
       //qDebug()<<"�׷����ߣ�";

        Points P = seekPoints(board);

        for (int i = 0; i < 10; ++i) {
            //qDebug()<<"�׷�ģ����"<<P.pos[i].x()<<","<<P.pos[i].y();
            int sameBoard[15][15];
            copyBoard(board, sameBoard);

            sameBoard[P.pos[i].x()][P.pos[i].y()] = WHITE;//ģ�⼺������,������board,������ܸı�board����Ϣ
            int a = analyse(sameBoard, depth - 1, alpha, beta);
            if (a > alpha) {
                alpha = a;
                if (depth == 6) {
                    //qDebug() << "set decision:" << P.pos[i].x() << P.pos[i].y();

                    decision.pos.setX(P.pos[i].x());
                    decision.pos.setY(P.pos[i].y());
                    decision.eval = a;
                }
            }
            if (beta <= alpha)break;//��֦
        }
        return alpha;
    }
    else {

        int rBoard[15][15];
        reverseBoard(board, rBoard);
        Points P = seekPoints(rBoard);          //�����������λ��,��Ҫ��������ɫ��ת

        for (int i = 0; i < 10; ++i) {

            int sameBoard[15][15];
            copyBoard(board, sameBoard);

            sameBoard[P.pos[i].x()][P.pos[i].y()] = BLACK;

            int a = analyse(sameBoard, depth - 1, alpha, beta);

            if (a < beta)
                beta = a;
            if (beta <= alpha)
                break;
        }
        return beta;
    }
}

bool GoBangAI::analyse_kill(int(*board)[15], int depth) {
    EVALUATION EVAL = evaluate(board);
    if (depth == 0 || EVAL.result != R_DRAW) {
        if (depth == 0) {

            //�ִ������ʱ�ߵ�ǰ����÷���ߵ�λ��,��ʱ������û��ȡʤ�򷵻�false���䣩

            Points P;
            P = seekPoints(board);
            board[P.pos[0].x()][P.pos[0].y()] = WHITE;

            gameResult result = evaluate(board).result;
            if (result == R_WHITE)
                return true;
            else 
                return false;
        }
        else if (EVAL.result == R_WHITE)
            return true;
        else 
            return false;
    }
    else if (depth % 2 == 0) {
        if (depth == 16 || depth == 14) {
            Points P = seekPoints(board);
            for (int i = 0; i < 10; ++i) {
                int sameBoard[15][15];
                copyBoard(board, sameBoard);

                sameBoard[P.pos[i].x()][P.pos[i].y()] = WHITE;

                if (analyse_kill(sameBoard, depth - 1)) {
                    if (depth == 16) {
                        //qDebug() << "kill set decision:" << P.pos[i].x() << P.pos[i].y();

                        decision.pos.setX(P.pos[i].x());
                        decision.pos.setY(P.pos[i].y());
                        decision.eval = INT_MAX;//����һ��..
                    }
                    return true;
                }
            }
            return false;
        }
        else {
            QList<QPoint> pointList = seek_kill_points(board);

            if (pointList.length() == 0)
                return false;
            for (auto i : pointList) {
                int sameBoard[15][15];
                copyBoard(board, sameBoard);

                sameBoard[i.x()][i.y()] = WHITE;

                if (analyse_kill(sameBoard, depth - 1)) {
                    
                    return true;
                }
            }
            return false;
        }
    }
    else {
        int rBoard[15][15];
        reverseBoard(board, rBoard);
        Points P = seekPoints(rBoard);

        int sameBoard[15][15];
        copyBoard(board, sameBoard);
        sameBoard[P.pos[0].x()][P.pos[0].y()] = BLACK;
        //�����֦
        return analyse_kill(sameBoard, depth - 1);
    }
}

QList<QPoint> GoBangAI::seek_kill_points(int(*board)[15]) {
    QList<QPoint> pointList;

    Points P = seekPoints(board);

    int sameBoard[15][15];
    copyBoard(board, sameBoard);

    for (int i = 0; i < 20; ++i) {
        sameBoard[P.pos[i].x()][P.pos[i].y()] = WHITE;
        if (evaluate(sameBoard).STAT[WIN] > 0) 
            pointList.append(P.pos[i]);
        else if (evaluate(sameBoard).STAT[FLEX4] > evaluate(board).STAT[FLEX4])
            pointList.append(P.pos[i]);
        else if (evaluate(sameBoard).STAT[BLOCK4] > evaluate(board).STAT[BLOCK4])
            pointList.append(P.pos[i]);
        else if (evaluate(sameBoard).STAT[FLEX3] > evaluate(board).STAT[FLEX3]) 
            pointList.append(P.pos[i]);
        sameBoard[P.pos[i].x()][P.pos[i].y()] = EMPTY;
    }
    return pointList;
}

QPoint GoBangAI::AI_Move() {
    nodeNum = 0;

    //��ɱʧ��
    if (!analyse_kill(chesses, 16)) 
        analyse(chesses, 6, -INT_MAX, INT_MAX);

    //��ɱ�ɹ�
    return decision.pos;
}