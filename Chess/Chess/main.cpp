#include <iostream>
#include "ChessGame.h"
int main(void)
{

	Man man;
	//Chess chess;
	Chess chess(19, 25, 30, 52.3);
	//Chess chess(19, 34, 28, 25.21);
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}

//#include<graphics.h>//����ͼ�ο�ͷ�ļ�
//#include <conio.h>
//int main()
//{
//	initgraph(400, 400);    //�������ڴ�СΪ640x480����
//	circle(200, 200, 100);    //��Բ��Բ��(200,200),�뾶100
//	outtextxy(170, 200, _T("���ض���"));
//	_getch();      //�����������,��ֹ����
//	closegraph();   //�رջ�ͼ����
//	return 0;
//}
