#ifndef _HUARONGDAO_H_
#define _HUARONGDAO_H_

#include <graphics.h>
#include <stdio.h>

#include "MagicTown.h"

class MagicTown;

typedef struct
{
	int x;
	int y;
}position;

class HuaRongDao
{
private:
	int huarongdao_map[4][6][7];  //���ݵ���ͼ
	int num = 0;
	IMAGE empty, caocao, guanyu, zhangfei, zhaoyun, machao, huangzhong, zu1, zu2, zu3, zu4;

private:
	void MoveChess(int name, int x, int y); // �ƶ�����
	void ChooseMap();  // ѡ���ͼ�����˳�
	void InitMap();  // ��ʼ����Ӧ��ͼ�Ľ���
	void DrawChooseMap();  // ��ʾ��ͼ���Ⲣ��������
	void LoadPicture();  // ���ػ��ݵ�����ͼƬ
	void DrawGame();  // ���ݵ�ͼ�ҳ���Ӧ��������겢����
	void WinGame();  // ���ƻ��ݵ�ʤ������
	position FindPosition(int name); // ��������λ�ã������Ͻ�Ϊ����ֵ

public:
	HuaRongDao();
	void PlayGame(); // ���л��ݵ���Ϸ

public:
	// ����MagicTown�෽��
	MagicTown* magic_town;
};

#endif // !HUARONGDAO_H_