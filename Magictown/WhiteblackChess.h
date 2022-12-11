#ifndef _BLACKWHITE_H_
#define _BLACKWHITE_H_

#include <graphics.h>
#include <stdio.h>

#include "MagicTown.h"

class MagicTown;

class WhiteblackChess
{
private:
	int blackwhite_chess_map[8][8];  // �ڰ�������
	int black_chess, white_chess; // �ڰ�������

private:
	void InitGame(); // ���ƺڰ�������
	void DrawChess(int a, int b, int color); // ��������
	bool CanSetThere(int x, int y, int color); // �ж����λ���ܷ�����
	void TakeDown(int x, int y, int color); // �ڰ������
	bool CanNotSet(int color); // �ж��Ƿ��еط�����
	void CountChess(); // ������������

public:
	WhiteblackChess();
	void PlayGame(); // ���ڰ��塱��Ϸ����

public:
	// ����MagicTown��ķ���
	MagicTown* magic_town;

};

#endif // !_BLACKWHITE_H_