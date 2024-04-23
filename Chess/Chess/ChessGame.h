#pragma once
#include "Man.h"
#pragma once
#include "Man.h"
#include "AI.h"
#include "Chess.h"

class ChessGame
{
private:
	/* data */
	Man* man;
	AI* ai;
	Chess* chess;

public:
	void play(); // ��ʼ�Ծ�

	ChessGame(Man* man, AI* ai, Chess* chess);
};

