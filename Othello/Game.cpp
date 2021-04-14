#include "Game.hpp"
#include <iostream>

#include "DxLib.h"


Game::Game(Entry* entry)
{
	owner = entry;	//Entry クラス

	//スプライトロード
	whiteSprite = LoadGraph("Assets/White.png");
	blackSprite = LoadGraph("Assets/Black.png");
	boardSprite = LoadGraph("Assets/Board.png");

	//盤面を初期化
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board[y][x] = BoardData(glm::ivec2(x, y),false);

		}
	}

	//初期ブロック
	board[3][3] = BoardData(glm::ivec2(3, 3), true);
	board[3][3].side = Side::Black;

	board[3][4] = BoardData(glm::ivec2(4, 3), true);
	board[3][4].side = Side::White;

	board[4][3] = BoardData(glm::ivec2(3, 4), true);
	board[4][3].side = Side::Black;

	board[4][4] = BoardData(glm::ivec2(4, 4), true);
	board[4][4].side = Side::White;
	
}


Game::~Game()
{
	
	
}

//その場所に置けるかどうか？
bool Game::getIsPut(glm::ivec2 p,Side my)
{
	if (board.at(p.y).at(p.x).put == false)
	{
	
		bool b = false;
		int num = 0;

		//右
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
			 
		//左
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
		
		//下
		num = 0;
		for (int i = 1; i < (BOARD_SIZE - p.y); i++)
			//for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.y); i++)
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

		//上
		num = 0;
		for (int i = 1; i < (BOARD_SIZE - p.y); i++)
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
	
		//左上
		num = 0;		
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if ( ((p.y - i) > -1) && ((p.x - i) > -1) )
			{
				//自分の色と逆の色だった場合
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




		
		//右上
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
			{
				//自分の色と逆の色だった場合
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
		
		//左下
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x - i) > -1))
			{
				//自分の色と逆の色だった場合
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


		//右下
		num = 0;
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y + i) < BOARD_SIZE) && ((p.x + i) < BOARD_SIZE))
			{
				//自分の色と逆の色だった場合
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

//ひっくり返す
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
		//for (int i = 1; i < BOARD_SIZE - (BOARD_SIZE - p.y); i++)
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



	//上
	num = 0;
	for (int i = 1; i < (BOARD_SIZE - p.y); i++)
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
		for (int i = 1; i < (BOARD_SIZE - p.y); i++)
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





	//左上
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y - i) > -1) && ((p.x - i) > -1))
		{
			//自分の色と逆の色だった場合
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
	
	num = 0;
	if (b == true) 
	{
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x - i) > -1))
			{
				//自分の色と逆の色だった場合
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

	//右上
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
		{
			//自分の色と逆の色だった場合
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

	num = 0;
	if (b == true) 
	{
		for (int i = 1; i < BOARD_SIZE; i++)
		{
			if (((p.y - i) > -1) && ((p.x + i) < BOARD_SIZE))
			{
				//自分の色と逆の色だった場合
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




	//左下
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y + i) < BOARD_SIZE) && ((p.x - i) > -1))
		{
			//自分の色と逆の色だった場合
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
				//自分の色と逆の色だった場合
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






	//右下
	num = 0;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (((p.y + i) < BOARD_SIZE) && ((p.x + i) < BOARD_SIZE))
		{
			//自分の色と逆の色だった場合
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
				//自分の色と逆の色だった場合
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


//相手ターン
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
				RevChip(Side::White, glm::ivec2(x,y));	//ブロックをひっくり返す
				
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



void Game::Update()
{
	
	glm::ivec2 pos = glm::ivec2(0,0);
	GetMousePoint(&pos.x,&pos.y);

	if ((pos.x < (BOARD_SIZE * CELL) && pos.x > 0) && (pos.y < (BOARD_SIZE * CELL) && pos.y > 0))
	{
		//セルを算出
		pos.x = pos.x / CELL;
		pos.y = pos.y / CELL;

		//左クリック
		if ((GetMouseInput() && MOUSE_INPUT_LEFT) != 0)
		{
			if (getIsPut(pos, mySide) == true)
			{
				//置ける場合
				//printf("put\n");
				board.at(pos.y).at(pos.x).side = mySide;
				board.at(pos.y).at(pos.x).put = true;
				RevChip(mySide, pos);	//ブロックを変転

				//デバッグ
				printf("自分\n");
				for (int y = 0; y < BOARD_SIZE; y++)
				{
					for (int x = 0; x < BOARD_SIZE; x++)
					{

						if (x == pos.x && y == pos.y)
						{
							printf("□");
						}
						else if (board.at(y).at(x).side == Side::White)
						{
							printf("●");
						}else if (board.at(y).at(x).side == Side::Black)
						{
							printf("◯");
						}
						else {
							printf("・");
						}
					}

					printf("\n");
				}




				//Sleep(3000);
				Opponent();


				//デバッグ
				printf("\n\n");
				printf("相手\n");

				for (int y = 0; y < BOARD_SIZE; y++)
				{
					for (int x = 0; x < BOARD_SIZE; x++)
					{
						if (board.at(y).at(x).side == Side::White)
						{
							printf("●");
						}
						else if (board.at(y).at(x).side == Side::Black)
						{
							printf("◯");
						}
						else {
							printf("・");
						}
					}

					printf("\n");
				}


			}
		}
	}
}


void Game::Draw()
{



	//盤面
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
}
