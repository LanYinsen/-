#pragma once
#include <graphics.h>
#include <easyx.h>
#include <vector>
#include<graphics.h>
using namespace std;

// λ�ã��� ��
struct ChessPos
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

typedef enum
{
	CHESS_WHITE = -1, // ����
	CHESS_BLACK = 1   // ����
} chess_kind_t;       // ��������

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init(); // ���̵ĳ�ʼ��

	bool clickBoard(int x, int y, ChessPos* pos); // �Ƿ���Ч���

	void chessDown(ChessPos* pos, chess_kind_t kind); // ����

	int getGradeSize(); // ��ȡ���̵Ĵ�С��13��15��19��

	int getChessData(ChessPos* pos);
	int getChessData(int row, int col); // ��ȡָ��λ���Ǻ��廹�ǰ��廹�ǿհ�

	bool checkOver(); // ����Ƿ����
private:
	IMAGE chessBlackImg; //��������
	IMAGE chessWhiteImg; //��������

	int gradeSize; //���̴�С��13��15��17��19��
	int margin_x; //���̵����߽�
	int margin_y; //���̵Ķ����߽�
	float chessSize;//���ӵĴ�С

	//�洢��ǰ��ֵ����ӷ������� 0���հף�   1�����ӣ�   -1�����ӣ�
	//chessMap[3][5] ��ʾ���̵ĵ�3�е�5�е��������
	vector<vector<int>> chessMap;

	//��ʾ���ڸ�˭���壨���ӣ�
	bool playerFlag;//true: ������

	void updataGameMap(ChessPos* pos);
	bool checkWin();//ʤ���ѷ֣�����true
	ChessPos lastPos;//������ӵ�λ��

};
