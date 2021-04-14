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
			board[y][x] = BoardData(glm::ivec2(x, y),false);

		}
	}

	//�����u���b�N
	board[3][3] = BoardData(glm::ivec2(3, 3), true);
	board[3][3].side = Side::Black;

	board[3][4] = BoardData(glm::ivec2(4, 3), true);
	board[3][4].side = Side::White;

	board[4][3] = BoardData(glm::ivec2(3, 4), true);
	board[4][3].side = Side::White;

	board[4][4] = BoardData(glm::ivec2(4, 4), true);
	board[4][4].side = Side::Black;
	
}


Game::~Game()
{
	
	
}

//���̏ꏊ�ɒu���邩�ǂ����H
bool Game::getIsPut(glm::ivec2 p,Side my)
{
	if (board.at(p.y).at(p.x).put == false)
	{
	
		bool b = false;
		int num = 0;

		//�E
		for (int i = 1; i <  BOARD_SIZE - p.x; i++)
		{
			if (board.at(p.y).at(p.x + i).side != my && board.at(p.y).at(p.x + i).put == true)
			{
				num++;
			}
			else if ( (board.at(p.y).at(p.x + i).side == my) && (board.at(p.y).at(p.x + i).put == true) )
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
				
			}
			else if (board.at(p.y).at(p.x + i).put == false)
			{
				break;
			}
		}
			 
		//��
		num = 0;
		for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.x); i++)
		{	
			if (board.at(p.y).at(p.x - i).side != my && board.at(p.y).at(p.x - i).put == true)
			{
				num++;
			}
			else if ( (board.at(p.y).at(p.x - i).side == my) && (board.at(p.y).at(p.x - i).put == true) )
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
			}
			else if (board.at(p.y).at(p.x - i).put == false)
			{
				break;
			}		
		}
		
		//��
		num = 0;
		for (int i = 1; i < (BOARD_SIZE - p.y); i++)
		{
			if (p.y + i < BOARD_SIZE)
			{
				if ((board.at(p.y + i).at(p.x).side != my) && (board.at(p.y + i).at(p.x).put == true))
				{
					num++;
				}
				else if ((board.at(p.y + i).at(p.x).side == my) && (board.at(p.y + i).at(p.x).put == true))
				{
					if (num > 0)
					{
						b = true;
					}
					break;
				}
				else if (board.at(p.y + i).at(p.x).put == false)
				{
					break;
				}			
			}			
		}

		//��
		num = 0;
		for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.y); i++)
		{
			if (p.y - i > -1)
			{
				if ((board.at(p.y - i).at(p.x).side != my) && (board.at(p.y - i).at(p.x).put == true))
				{
					num++;
				}
				else if ((board.at(p.y - i).at(p.x).side == my) && (board.at(p.y - i).at(p.x).put == true))
				{
					if (num > 0)
					{
						b = true;
					}
					break;
				}
				else if (board.at(p.y - i).at(p.x).put == false)
				{
					break;
				}			
			}			
		}
	
		//����
		num = 0;		
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if ( ((p.y - i) > -1) && ((p.x - i) > -1) )
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ( (board.at(p.y - i).at(p.x - i).side != my) && (board.at(p.y - i).at(p.x - i).put == true) )
				{
					num++;
				}
				else if ( (board.at(p.y - i).at(p.x - i).side == my) && (board.at(p.y - i).at(p.x - i).put == true))
				{
					if (num > 0)
					{
						b = true;
						break;
					}
					else if (num == 0)
					{
						break;
					}
				}
				else if (board.at(p.y - i).at(p.x - 1).put == false)
				{
					break;
				}
			}
			else 
			{
				break;
			}
		}
	
		//�E��
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y - i).at(p.x + i).side != my) && (board.at(p.y - i).at(p.x + i).put == true))
				{
					num++;
				}
				else if ( (board.at(p.y - i).at(p.x + i).side == my) && (board.at(p.y - i).at(p.x + i).put == true) )
				{
					if (num > 0)
					{
						b = true;
						break;
					}
					else if (num == 0)
					{
						break;
					}
				}
				else if (board.at(p.y - i).at(p.x + 1).put == false)
				{
					break;
				}

			}
			else {
				break;
			}
		}
		
		//����
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x - i) > -1))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y + i).at(p.x - i).side != my) && (board.at(p.y + i).at(p.x - i).put == true))
				{
					num++;
				}
				else if ( (board.at(p.y + i).at(p.x - i).side == my) && (board.at(p.y + i).at(p.x - i).put == true) )
				{
					if (num > 0)
					{
						b = true;
						break;
					}
					else if (num == 0)
					{
						break;
					}
				}
				else if (board.at(p.y + i).at(p.x - 1).put == false)
				{
					break;
				}

			}
			else 
			{
				break;
			}
		}

		//�E��
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x + i) < BOARD_SIZE))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y + i).at(p.x + i).side != my) && (board.at(p.y + i).at(p.x + i).put == true))
				{
					num++;
				}
				else if ( (board.at(p.y + i).at(p.x + i).side == my) && (board.at(p.y + i).at(p.x + i).put == true) )
				{
					if (num > 0)
					{
						b = true;
						break;
					}
					else if (num == 0)
					{
						break;
					}
				}
				else if (board.at(p.y + i).at(p.x + 1).put == false)
				{
					break;
				}
			}
			else 
			{
				break;
			}
		}
		
		return b;		
	}

	return false;
}

//�Ђ�����Ԃ�
void Game::RevChip(Side my, glm::ivec2 p)
{

	bool b = false;
	int num = 0;

	//Right
	for (int i = 1; i < BOARD_SIZE - p.x; i++)
	{
		if (board.at(p.y).at(p.x + i).side != my && board.at(p.y).at(p.x + i).put == true)
		{
			num++;
		}
		else if ((board.at(p.y).at(p.x + i).side == my) && (board.at(p.y).at(p.x + i).put == true))
		{
			if (num > 0)
			{
				b = true;
				break;
			}
			else if (num == 0)
			{
				break;
			}

		}
		else if (board.at(p.y).at(p.x + i).put == false)
		{
			break;
		}
	}
	if (b == true)
	{
		for (int i = 1; i < BOARD_SIZE - p.x; i++)
		{
			if (board.at(p.y).at(p.x + i).side != my && board.at(p.y).at(p.x + i).put == true)
			{
				board.at(p.y).at(p.x + i).side = my;
				board.at(p.y).at(p.x + i).put = true;
			}
			else
			{
				break;
			}
		}

		b = false;
	}

	//Left
	num = 0;
	for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.x); i++)
	{
		if (board.at(p.y).at(p.x - i).side != my && board.at(p.y).at(p.x - i).put == true)
		{
			num++;
		}
		else if ((board.at(p.y).at(p.x - i).side == my) && (board.at(p.y).at(p.x - i).put == true))
		{
			if (num > 0)
			{
				b = true;
				break;
			}
			else if (num == 0)
			{
				break;
			}
		}
		else if (board.at(p.y).at(p.x - i).put == false)
		{
			break;
		}
	}
	if (b == true)
	{
		for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.x); i++)
		{
			if (board.at(p.y).at(p.x - i).side != my && board.at(p.y).at(p.x - i).put == true)
			{
				board.at(p.y).at(p.x - i).side = my;
				board.at(p.y).at(p.x - i).put = true;
			}
			else
			{
				break;
			}
		}

		b = false;
	}



	//Down
	num = 0;
	for (int i = 1; i < (BOARD_SIZE - p.y); i++)
	{
		if (p.y + i < BOARD_SIZE)
		{
			if ((board.at(p.y + i).at(p.x).side != my) && (board.at(p.y + i).at(p.x).put == true))
			{
				num++;
			}
			else if ((board.at(p.y + i).at(p.x).side == my) && (board.at(p.y + i).at(p.x).put == true))
			{
				if (num > 0)
				{
					b = true;
				}
				break;
			}
			else if (board.at(p.y + i).at(p.x).put == false)
			{
				break;
			}
		}
	}
	if (b == true)
	{
		for (int i = 1; i < (BOARD_SIZE - p.y); i++)
		{
			if (board.at(p.y + i).at(p.x).side != my && board.at(p.y + i).at(p.x).put == true)
			{
				board.at(p.y + i).at(p.x).side = my;
				board.at(p.y + i).at(p.x).put = true;
			}
			else
			{
				break;
			}
		}

		b = false;
	}



	//Up
	num = 0;
	for (int i = 1; i <  BOARD_SIZE - (BOARD_SIZE - p.y); i++)
	{
		if (p.y - i > -1)
		{
			if ((board.at(p.y - i).at(p.x).side != my) && (board.at(p.y - i).at(p.x).put == true))
			{
				num++;
			}
			else if ((board.at(p.y - i).at(p.x).side == my) && (board.at(p.y - i).at(p.x).put == true))
			{
				if (num > 0)
				{
					b = true;
				}
				break;
			}
			else if (board.at(p.y - i).at(p.x).put == false)
			{
				break;
			}
		}
	}
	if (b == true)
	{
		for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.y); i++)
		{
			if (board.at(p.y - i).at(p.x).side != my && board.at(p.y - i).at(p.x).put == true)
			{
				board.at(p.y - i).at(p.x).side = my;
				board.at(p.y - i).at(p.x).put = true;
			}
			else
			{
				break;
			}
		}

		b = false;
	}





	//����
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y - i) > -1) && ((p.x - i) > -1))
		{
			//�����̐F�Ƌt�̐F�������ꍇ
			if ((board.at(p.y - i).at(p.x - i).side != my) && (board.at(p.y - i).at(p.x - i).put == true))
			{
				num++;
			}
			else if ((board.at(p.y - i).at(p.x - i).side == my) && (board.at(p.y - i).at(p.x - i).put == true))
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
			}
			else if (board.at(p.y - i).at(p.x - 1).put == false)
			{
				break;
			}
		}
		else
		{
			break;

		}
	}
	if (b == true) 
	{
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x - i) > -1))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y - i).at(p.x - i).side != my) && (board.at(p.y - i).at(p.x - i).put == true))
				{
					board.at(p.y - i).at(p.x - i).side = my;
					board.at(p.y - i).at(p.x - i).put = true;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		b = false;
	}

	//�E��
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
		{
			//�����̐F�Ƌt�̐F�������ꍇ
			if ((board.at(p.y - i).at(p.x + i).side != my) && (board.at(p.y - i).at(p.x + i).put == true))
			{
				num++;
			}
			else if ((board.at(p.y - i).at(p.x + i).side == my) && (board.at(p.y - i).at(p.x + i).put == true))
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
			}
			else if (board.at(p.y - i).at(p.x + 1).put == false)
			{
				break;
			}

		}
		else {
			break;
		}
	}
	if (b == true) 
	{
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y - i).at(p.x + i).side != my) && (board.at(p.y - i).at(p.x + i).put == true))
				{
					board.at(p.y - i).at(p.x + i).side = my;
					board.at(p.y - i).at(p.x + i).put = true;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		b = false;
	}




	//����
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y + i) < BOARD_SIZE) && ((p.x - i) > -1))
		{
			//�����̐F�Ƌt�̐F�������ꍇ
			if ((board.at(p.y + i).at(p.x - i).side != my) && (board.at(p.y + i).at(p.x - i).put == true))
			{
				num++;
			}
			else if ((board.at(p.y + i).at(p.x - i).side == my) && (board.at(p.y + i).at(p.x - i).put == true))
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
			}
			else if (board.at(p.y + i).at(p.x - 1).put == false)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (b == true)
	{

		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x - i) > -1))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y + i).at(p.x - i).side != my) && (board.at(p.y + i).at(p.x - i).put == true))
				{
					board.at(p.y + i).at(p.x - i).side = my;
					board.at(p.y + i).at(p.x - i).put = true;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		b = false;
	}

	//�E��
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y + i) < BOARD_SIZE) && ((p.x + i) < BOARD_SIZE))
		{
			//�����̐F�Ƌt�̐F�������ꍇ
			if ((board.at(p.y + i).at(p.x + i).side != my) && (board.at(p.y + i).at(p.x + i).put == true))
			{
				num++;
			}
			else if ((board.at(p.y + i).at(p.x + i).side == my) && (board.at(p.y + i).at(p.x + i).put == true))
			{
				if (num > 0)
				{
					b = true;
					break;
				}
				else if (num == 0)
				{
					break;
				}
			}
			else if (board.at(p.y + i).at(p.x + 1).put == false)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (b == true)
	{
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x + i) < BOARD_SIZE))
			{
				//�����̐F�Ƌt�̐F�������ꍇ
				if ((board.at(p.y + i).at(p.x + i).side != my) && (board.at(p.y + i).at(p.x + i).put == true))
				{
					board.at(p.y + i).at(p.x + i).side = my;
					board.at(p.y + i).at(p.x + i).put = true;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		b = false;
	}



	
}


//����^�[��
void Game::Opponent()
{
	bool b = false;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{

			if (getIsPut(glm::ivec2(x, y), Side::White) == true)
			{
				
				board.at(y).at(x).side = Side::White;
				board.at(y).at(x).put = true;
				RevChip(Side::White, glm::ivec2(x,y));	//�u���b�N���Ђ�����Ԃ�
				
				b = true;	
				break;	
			}
		}

		if (b == true)
		{
			break;
		}
	}


}

//�u���b�N���𐔂���
void Game::Percentage()
{

	//����������
	whiteNum = 0;
	blackNum = 0;

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board.at(y).at(x).side == Side::White)
			{
				whiteNum++;
			}
			else if (board.at(y).at(x).side == Side::Black)
			{
				blackNum++;
			}
		}
	}
}

//�f�o�b�O�p�̔Ֆʂ�\��
void Game::Debug_board()
{
	//�f�o�b�O
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board.at(y).at(x).side == Side::White)
			{
				printf("��");
			}
			else if (board.at(y).at(x).side == Side::Black)
			{
				printf("��");
			}
			else {
				printf("�E");
			}
		}
		printf("\n");
	}

}



//�Q�[���I�[�o�[����
bool Game::GameOver(Side my) 
{
	bool b = true;
	//�f�o�b�O
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (getIsPut(glm::ivec2(x,y),my) == true)
			{
				b = false;
			}
		}
	}

	return b;
}



void Game::Update()
{
	
	//����̃^�[��
	if (turn == true)
	{
		if (anim == 90) {

			Opponent();
			printf("\n\n");
			printf("����\n");
			Debug_board();

			turn = false;
			anim = 0;
		}
		else {
			anim++;
		}
	}





	glm::ivec2 pos = glm::ivec2(0,0);
	GetMousePoint(&pos.x,&pos.y);
	if ((pos.x < (BOARD_SIZE * CELL) && pos.x > 0) && (pos.y < (BOARD_SIZE * CELL) && pos.y > 0) && turn == false)
	{
		//�Z�����Z�o
		pos.x = pos.x / CELL;
		pos.y = pos.y / CELL;

		//���N���b�N
		if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
		{

			if (getIsPut(pos, mySide) == true && isGameOver == false)
			{
				//�u����ꍇ
				//printf("put\n");
				board.at(pos.y).at(pos.x).side = mySide;
				board.at(pos.y).at(pos.x).put = true;
				RevChip(mySide, pos);	//�u���b�N��ϓ]

				//�f�o�b�O
				printf("����\n");
				Debug_board();
				
				turn = true;	//����̃^�[����
			}else if (isGameOver == true)
			{
				//�Q�[���I�[�o�[�̂��ߍď�����

				//�Ֆʂ�������
				for (int y = 0; y < BOARD_SIZE; y++)
				{
					for (int x = 0; x < BOARD_SIZE; x++)
					{
						board[y][x] = BoardData(glm::ivec2(x, y), false);

					}
				}

				//�����u���b�N
				board[3][3] = BoardData(glm::ivec2(3, 3), true);
				board[3][3].side = Side::Black;

				board[3][4] = BoardData(glm::ivec2(4, 3), true);
				board[3][4].side = Side::White;

				board[4][3] = BoardData(glm::ivec2(3, 4), true);
				board[4][3].side = Side::White;

				board[4][4] = BoardData(glm::ivec2(4, 4), true);
				board[4][4].side = Side::Black;


				isGameOver = false;
			}



			


		}
	}








	isGameOver = GameOver(mySide);
	Percentage();	//�u���b�N�̐��𐔂���B
}


void Game::Draw()
{

	//�Ֆ�
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board.at(y).at(x).put == false)
			{
				DrawGraph(x * CELL, y * CELL, boardSprite, true);
			}
			else if (board.at(y).at(x).side == Side::White && board.at(y).at(x).put == true)
			{
				DrawGraph(x * CELL, y * CELL, whiteSprite, true);
			}
			else if (board.at(y).at(x).side == Side::Black && board.at(y).at(x).put == true)
			{
				DrawGraph(x * CELL, y * CELL, blackSprite, true);
			}
		}
	}

	//����������\��
	DrawFormatString(400, 50, GetColor(255, 255, 255), "Black: %d", blackNum);
	DrawFormatString(400, 80, GetColor(255, 255, 255), "White: %d", whiteNum);

	if (isGameOver == true)
	{
		DrawBox(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 25, GetColor(0, 0, 100), true);
		DrawFormatString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GetColor(255, 255, 255), "GAME OVER");

	}
	


}
