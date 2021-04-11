#ifndef ___GAME_HPP
#define ___GAME_HPP
#include "glm/glm.hpp"
#include <array>

//前方宣言
class Entry;


#define BOARD_SIZE ((int)8)	//盤面サイズ
#define CELL ((int)48)		//セル

//ブロックタイプ
typedef enum class Side
{
	White,
	Black,
	None,
}Side;


/*セルのオブジェクトを識別
* 
* 0　白
* 1　黒 
* 2　なし

*/
class BoardData
{
public:

	//コンストラクタ
	BoardData(Side s,glm::ivec2 p)
	{
		side = s;
		pos - p;
	}


	//デフォルトコンストラクタ
	BoardData()	
	{
		side = Side::None;
		pos = glm::ivec2(-1,-1);
	}




	Side side;		//何があるのか？
	glm::ivec2 pos;	//座標	
};


class Game
{
public:
	Game(Entry* entry);
	~Game();

	void Update();
	void Draw();


private:

	//スプライト
	int whiteSprite;	//白
	int blackSprite;	//黒
	int boardSprite;	//ボード


	Side mySide = Side::Black;


	bool getIsPut(glm::ivec2 p, Side my);	//その場所に置けるかどうか？

	//BoardData board[BOARD_SIZE][BOARD_SIZE];		//ボード配列
	std::array<std::array<BoardData,8>,8> board;	//ボード配列

	Entry* owner;	//Entryクラス
};

#endif
