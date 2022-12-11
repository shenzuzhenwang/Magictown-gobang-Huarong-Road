#include "WhiteblackChess.h"
/*
    ��ʼ���ڰ�������
*/
WhiteblackChess::WhiteblackChess()
{
	black_chess = 0;
	white_chess = 0;
	// ��ʼ������Ϊ��
	memset(blackwhite_chess_map, 0, sizeof(blackwhite_chess_map));
}
/*
    ���ƺڰ�������
*/
void WhiteblackChess::InitGame()
{
	// ��ʼ����������ʾ���ڰ��塱
	initgraph(650, 650);
	setbkcolor(RGB(255, 215, 0));
	cleardevice();
	settextstyle(150, 0, L"����");
	settextcolor(BLACK);
	outtextxy(100, 250, L"�ڰ���");
	Sleep(5000);
	cleardevice();

	// �����˳���
	setlinecolor(BLACK);
	setfillcolor(LIGHTGRAY);
	bar(580, 0, 650, 40);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, L"����");
	settextcolor(LIGHTCYAN);
	outtextxy(585, 0, L"�˳�");

	// ��������
	for (int i = 0; i < 9; i++)
	{
		line(70 * i + 45, 45, 70 * i + 45, 605);
		line(45, 70 * i + 45, 605, 70 * i + 45);
	}
	// �����Ӵ�
	line(44, 44, 44, 606);
	line(44, 44, 606, 44);
	line(44, 606, 606, 606);
	line(606, 44, 606, 606);
	line(45, 45, 604, 45);
	line(45, 45, 45, 604);
	line(45, 604, 604, 604);
	line(604, 45, 604, 604);

	// ��ʾ���巽
	setbkmode(OPAQUE);
	settextcolor(RED);
	outtextxy(280, 7, L"�ڷ���");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			blackwhite_chess_map[i][j] = 0;

	// �����м���������
	blackwhite_chess_map[3][3] = 1;
	blackwhite_chess_map[4][4] = 1;
	blackwhite_chess_map[3][4] = 2;
	blackwhite_chess_map[4][3] = 2;
	DrawChess(3, 3, 1);
	DrawChess(4, 4, 1);
	DrawChess(3, 4, 2);
	DrawChess(4, 3, 2);
	CountChess();
}
/*
    ���ڰ��塱��Ϸ���У���������������ж���������
*/
void WhiteblackChess::PlayGame()
{
	InitGame();
	// ����blackwhite_chess_map�ϵ�����
	int map_x = 0, map_y = 0;
	// ��������
	int color = 1;
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 580 && m.x < 650 && m.y>0 && m.y < 40)
			{
				// ������˳���
				magic_town->PlayGame();
			}
			else if (m.x < 45 || m.y < 45 || m.x > 605 || m.y > 605)
			{
				// ���������
				settextcolor(LIGHTRED);
				outtextxy(280, 7, L"������");
				continue;
			}

			// ������������꣬�ж�ѡ��λ��
			map_x = (m.x - 45) / 70;
			map_y = (m.y - 45) / 70;
			// �жϸ������Ƿ�Ϊ�����Ƿ��������
			if (blackwhite_chess_map[map_y][map_x] == 0 && CanSetThere(map_x, map_y, color))
			{
				blackwhite_chess_map[map_y][map_x] = color;
				DrawChess(map_x, map_y, color);
				TakeDown(map_x, map_y, color);

				// ����ѡ��
				if (color == 1)
				{
					color = 2;
					settextcolor(BLUE);
					outtextxy(280, 7, L"�׷���");
				}
				else if (color == 2)
				{
					color = 1;
					settextcolor(RED);
					outtextxy(280, 7, L"�ڷ���");
				}
			}
			// ��λ�����ӣ���������
			else
			{
				settextcolor(LIGHTRED);
				outtextxy(280, 7, L"�²���");
				continue;
			}

			// �������и���������
			CountChess();

			if (CanNotSet(color) == 1)
			{
				if (CanNotSet(3 - color) == 1)
				{
					// ˫�����ӿ���
					setbkmode(TRANSPARENT);
					settextcolor(LIGHTGRAY);
					settextstyle(100, 0, L"����");

					// �ж�ʤ����
					if (black_chess > white_chess)
					{
						outtextxy(175, 275, L"�ڷ�ʤ");
						Sleep(3000);
						magic_town->PlayGame();
					}
					if (black_chess <= white_chess)
					{
						outtextxy(175, 275, L"�׷�ʤ");
						Sleep(3000);
						magic_town->PlayGame();
					}
				}
				else
				{
					// һ�����ӿ����������÷�
					if (color == 1)
					{
						color = 2;
						settextcolor(BLUE);
						outtextxy(280, 7, L"�׷���");
					}
					else if (color == 2)
					{
						color = 1;
						settextcolor(RED);
						outtextxy(280, 7, L"�ڷ���");
					}
				}
			}
		}
	}

}
/*
    �������ӣ�x��yΪ���ӵ����꣬colorΪ��ɫ
*/
void WhiteblackChess::DrawChess(int x, int y, int color)
{
	if (color == 1)
		setfillcolor(BLACK);
	if (color == 2)
		setfillcolor(WHITE);
	fillcircle(x * 70 + 80, y * 70 + 80, 30);
}
/*
    �ڰ������  
	ע�⣺Ӧ�����ж������б��Ե����ӣ���󽫱��Ե����ӱ�ɫ
*/
void WhiteblackChess::TakeDown(int x, int y, int color)
{
	// �ж��Ϸ�����
	for (int i = y - 1; i >= 0 && blackwhite_chess_map[i][x]; i--)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			for (int j = y - 1; j > i; j--)
			{
				// �Ϸ����ӱ�ɫ
				blackwhite_chess_map[j][x] = 4;
				DrawChess(x, j, color);
			}
			break;
		}
	}
	// �ж��·�����
	for (int i = y + 1; i < 8 && blackwhite_chess_map[i][x]; i++)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			for (int j = y + 1; j < i; j++)
			{
				// �·����ӱ�ɫ
				blackwhite_chess_map[j][x] = 4;
				DrawChess(x, j, color);
			}
			break;
		}
	}
	// �ж��󷽳���
	for (int i = x - 1; i >= 0 && blackwhite_chess_map[y][i]; i--)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			for (int j = x - 1; j > i; j--)
			{
				// �����ӱ�ɫ
				blackwhite_chess_map[y][j] = 4;
				DrawChess(j, y, color);
			}
			break;
		}
	}
	// �ж��ҷ�����
	for (int i = x + 1; i < 8 && blackwhite_chess_map[y][i]; i++)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			for (int j = x + 1; j < i; j++)
			{
				// �ҷ����ӱ�ɫ
				blackwhite_chess_map[y][j] = 4;
				DrawChess(j, y, color);
			}
			break;
		}
	}
	// �ж����Ϸ�����
	for (int i = y - 1, j = x - 1; i >= 0 && j >= 0 && blackwhite_chess_map[i][j]; i--, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y - 1, jj = x - 1; ii > i && jj > j; ii--, jj--)
			{
				// ���Ϸ����ӱ�ɫ
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// �ж����·�����
	for (int i = y + 1, j = x - 1; i < 8 && j >= 0 && blackwhite_chess_map[i][j]; i++, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y + 1, jj = x - 1; ii < i && jj > j; ii++, jj--)
			{
				// ���·����ӱ�ɫ
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// �ж����Ϸ�����
	for (int i = y - 1, j = x + 1; i >= 0 && j < 8 && blackwhite_chess_map[i][j]; i--, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y - 1, jj = x + 1; ii > i && jj < j; ii--, jj++)
			{
				// ���Ϸ����ӱ�ɫ
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// �ж����·�����
	for (int i = y + 1, j = x + 1; i < 8 && j < 8 && blackwhite_chess_map[i][j]; i++, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y + 1, jj = x + 1; ii < i && jj < j; ii++, jj++)
			{
				// ���·����ӱ�ɫ
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// ������ӱ�ɫ
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (blackwhite_chess_map[i][j] == 4)
				blackwhite_chess_map[i][j] = color;

}
/*
    �ж����λ���ܷ�����
	���򣺱����г���
*/
bool WhiteblackChess::CanSetThere(int x, int y, int color)
{
	// �Ƿ�Խ���з���
	bool sign[8] = { 0 };

	// �ж��Ϸ��Ƿ���ͬɫ��
	for (int i = y - 1; i >= 0 && blackwhite_chess_map[i][x]; i--)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			// �Ϸ���ͬɫ���Ҳ����ڣ��������
			if (i != y - 1)
				sign[0] = true;
			break;
		}
	}
	// �ж��·��Ƿ���ͬɫ��
	for (int i = y + 1; i < 8 && blackwhite_chess_map[i][x]; i++)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			// �·���ͬɫ���Ҳ����ڣ��������
			if (i != y + 1)
				sign[1] = true;
			break;
		}
	}
	// �ж����Ƿ���ͬɫ��
	for (int i = x - 1; i >= 0 && blackwhite_chess_map[y][i]; i--)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			// ����ͬɫ���Ҳ����ڣ��������
			if (i != x - 1)
				sign[2] = true;
			break;
		}
	}
	// �ж��ҷ��Ƿ���ͬɫ��
	for (int i = x + 1; i < 8 && blackwhite_chess_map[y][i]; i++)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			// �ҷ���ͬɫ���Ҳ����ڣ��������
			if (i != x + 1)
				sign[3] = true;
			break;
		}
	}
	// �ж����Ϸ��Ƿ���ͬɫ��
	for (int i = y - 1, j = x - 1; i >= 0 && j >= 0 && blackwhite_chess_map[i][j]; i--, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// ���Ϸ���ͬɫ���Ҳ����ڣ��������
			if (i != y - 1 && j != x - 1)
				sign[4] = true;
			break;
		}
	}
	// �ж����·��Ƿ���ͬɫ��
	for (int i = y + 1, j = x - 1; i < 8 && j >= 0 && blackwhite_chess_map[i][j]; i++, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// ���·���ͬɫ���Ҳ����ڣ��������
			if (i != y + 1 && j != x - 1)
				sign[5] = true;
			break;
		}
	}
	// �ж����Ϸ��Ƿ���ͬɫ��
	for (int i = y - 1, j = x + 1; i >= 0 && j < 8 && blackwhite_chess_map[i][j]; i--, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// ���Ϸ���ͬɫ���Ҳ����ڣ��������
			if (i != y - 1 && j != x + 1)
				sign[6] = true;
			break;
		}
	}
	// �ж����·��Ƿ���ͬɫ��
	for (int i = y + 1, j = x + 1; i < 8 && j < 8 && blackwhite_chess_map[i][j]; i++, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// ���·���ͬɫ���Ҳ����ڣ��������
			if (i != y + 1 && j != x + 1)
				sign[7] = true;
			break;
		}
	}
	if (sign[0] || sign[1] || sign[2] || sign[3] || sign[4] || sign[5] || sign[6] || sign[7])
		return 1;
	else
		return 0;
}
/*
    �ж��Ƿ��еط�����
*/
bool WhiteblackChess::CanNotSet(int color)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (blackwhite_chess_map[i][j] == 0 && CanSetThere(j, i, color))
				return 0;
	return 1;
}
/*
    ������������
*/
void WhiteblackChess::CountChess()
{
	black_chess = 0;
	white_chess = 0;
	TCHAR s[100];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (blackwhite_chess_map[i][j] == 1)
				black_chess++;
			if (blackwhite_chess_map[i][j] == 2)
				white_chess++;
		}
	settextcolor(BLACK);
	wsprintf(s, L"���ӣ�%d ", black_chess);
	outtextxy(100, 0, s);
	settextcolor(WHITE);
	wsprintf(s, L"���ӣ�%d ", white_chess);
	outtextxy(430, 0, s);
}