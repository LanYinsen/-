#include "Chess.h"
#include<math.h>
#include<mmsystem.h>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}


Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//������Ϸ����
	initgraph(1000, 995, EW_SHOWCONSOLE);
	//initgraph(800, 800);
	//��ʾ����
	loadimage(0, "chess.png");
	//���ſ�ʼ��ʾ��
	mciSendString("play start.mp3", 0, 0, 0);//???

	//���غ���Ͱ�������ӵ�ͼƬ
	loadimage(&chessBlackImg, "black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "white.png", chessSize, chessSize, true);

	//��������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}

	}
	playerFlag = true;
} // ���̵ĳ�ʼ��

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosy = margin_y + chessSize * row;

	int offset = chessSize * 0.4;//��ֵ
	//int offset = chessSize * 0.5;//��ֵ
	int len;
	bool ret = false;//�Ƿ���Ч���

	//�ж�����
	do
	{
		//���Ͻ��ж� ���꣨leftTopPosX��leftTopPosy��
		len = sqrt(pow((x - leftTopPosX), 2) + pow((y - leftTopPosy), 2));
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;  //��Ч���
			}
			break;
		}

		//���Ͻ� ���꣨x2,y2��
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosy;
		len = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		//���½�
		x2 = leftTopPosX;
		y2 = leftTopPosy + chessSize;
		len = sqrt(pow(x - x2, 2) + pow(y2 - y, 2));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		//���½�
		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosy + chessSize;
		len = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		/*else {
			break;
		}*/

	} while (0);

	return true;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play black.mp3", 0, 0, 0);
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}

	updataGameMap(pos);//����
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	//checkWin()
	if (checkWin()) {
		Sleep(1000);
		if (playerFlag == false) {
			//�ղ�������Ǻڷ������ַ���,����ʤ��
			mciSendString("play black.mp3", 0, 0, 0);
			loadimage(0, "win.png");
		}
		else {
			mciSendString("play white.mp3", 0, 0, 0);
			loadimage(0, "lose.png");
		}

		_getch();//��ͣ
		return true;
	}

	return false;
}

void Chess::updataGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;//�ڰ��彻��

}


bool Chess::checkWin()
{
	//������ӵ��λ��
	int row = lastPos.row;
	int col = lastPos.col;

	//���ӵ��ˮƽ����
	for (int i = 0; i < 5; i++) {
		//���ڵ�i��
		//��������������λ��
		//i=0 (row,col)(row,col+1)...(row,col+4)
		//i=1 (row,col-1)(row,col+1)...(row,col+3)
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4]) {
			return true;
		}
	}

	//��ֱ����
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}

	//���µ�����  б����  " / "
	for (int i = 0; i < 5; i++) {
		if (row + i - 4 >= 0 && row + i < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}

	//�����ϵ����� " \ "
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}

	return false;
}