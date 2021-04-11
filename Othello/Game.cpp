#include "Game.hpp"
#include <iostream>

#include "DxLib.h"


Game::Game(Entry* entry)
{
	owner = entry;	//Entry �N���X

	//�X�v���C�g���[�h
	whiteSprite = LoadGraph("Assets/White.png");
	blackSprite = LoadGraph("Assets/Black.png");
	boardSprite = LoadGraph("Assets/Board.png");

	//�Ֆʂ�������
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board[y][x] = BoardData(Side::None, glm::ivec2(x, y));
		}
	}

	//�����u���b�N
	board[3][3] = BoardData(Side::White, glm::ivec2(3, 3));
	board[3][4] = BoardData(Side::Black, glm::ivec2(4, 3));

	board[4][3] = BoardData(Side::Black, glm::ivec2(3, 4));
	board[4][4] = BoardData(Side::White, glm::ivec2(4, 4));
	
}


Game::~Game()
{
	
	
}

//���̏ꏊ�ɒu���邩�ǂ����H
bool Game::getIsPut(glm::ivec2 p,Side my)
{
	if (board[p.y][p.x].side == Side::None)
	{
		if (my == Side::Black)
		{
			int num = 0;
			bool b = false;


			//�E
			for (int i = 1; i <  8 - p.x; i++)
			{
				if (board[p.y][p.x + i].side == Side::White)
				{
					b = true;
				}
				else {
					break;
				}
			}

			//��
			for (int i = 1; i < 8 - p.x; i++)
			{
				if (board[p.y][p.x - i].side == Side::White)
				{
					b = true;
				}
				else {
					break;
				}
			}


			
			//��
			for (int i = 1; i < 8 - p.y; i++)
			{
				if (board[p.y - i][p.x].side == Side::White)
				{
					printf("����\n");

					b = true;
				}
				else {
					break;
				}
			}






			return b;

		}



	}

	return false;
}

void Game::Update()
{
	glm::ivec2 pos;
	GetMousePoint(&pos.x,&pos.y);

	glm::ivec2 p = glm::ivec2(0,0);
	p.x = pos.x / CELL;
	p.y = pos.y / CELL;

	//���N���b�N
	if ((GetMouseInput() && MOUSE_INPUT_LEFT)  != 0)
	{
		//printf("%d , %d\n", p.x, p.y);
		if (getIsPut(p,mySide) == true)
		{
			board[p.y][p.x].side = mySide;






		}
	
	}



}


void Game::Draw()
{
	//printf("��\n");


	DrawGraph(0, 0, boardSprite, true);


	//�Ֆ�
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board[y][x].side == Side::None)
			{
				DrawGraph(x * CELL, y * CELL, boardSprite, true);
			}
			else if (board[y][x].side == Side::White)
			{
				DrawGraph(x * CELL, y * CELL, whiteSprite, true);
			}
			else if (board[y][x].side == Side::Black)
			{
				DrawGraph(x * CELL, y * CELL, blackSprite, true);
			}
		}
	}

}
