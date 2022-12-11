#ifndef _MAGICTOWN_H_
#define _MAGICTOWN_H_

#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#include "HuaRongDao.h"
#include "WhiteblackChess.h"

class HuaRongDao;
class WhiteblackChess;

class MagicTown
{
private:
	IMAGE wall, wall2, floor, shang, xia, zuo, you, door1, door2, key1, key2, up, down;
	IMAGE huarongdao, blackwhitechess;
	int yellowkey_num, bluekey_num, floor_num; // Կ��1������Կ��2����������-1
	int place_x, place_y; // ����λ��
	int map[3][10][10]; // ħ����ͼ

private:
	void LoadPicture(); // ����ħ��ͼƬ
	void DrawGame(int floor); // ���ݲ�����ʼ����ͼ
	void ShowThings(); // ��ʾԿ����¥��
	void InitGame(); // ��ʼ��ħ����ͼ

public:
	MagicTown();
	~MagicTown();
	void PlayGame(); // ��ʼħ����Ϸ

public:
	// ����HuaRongDao���WhiteblackChess��ķ���
	HuaRongDao* hua_rong_dao;
	WhiteblackChess* whiteblack_chess;

};

#endif // !_MAGICTOWN_H_