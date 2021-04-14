#ifndef ___GAME_HPP
#define ___GAME_HPP
#include "glm/glm.hpp"
#include <array>


#define SCREEN_WIDTH ((int)640)
#define SCREEN_HEIGHT ((int)480)


//前方宣言
class Entry;


#define BOARD_SIZE ((int)8)	//盤面サイズ
#define CELL ((int)48)		//セル

//ブロックタイプ
typedef enum class Side
{
	White,
	Black,
	
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
	BoardData(glm::ivec2 p,bool b)
	{
		pos - p;
		put = b;
	}


	//デフォルトコンストラクタ
	BoardData()	
	{
		side = Side::Black;
		pos = glm::ivec2(-1,-1);
		put = false;
	}




	Side side;		//何があるのか？
	glm::ivec2 pos;	//座標	
	bool put;		//何か置いてあるかどうか？
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
	void RevChip(Side my ,glm::ivec2 p);	//ひっくり返す。
	void Opponent();						//相手ターン
	void Percentage();						//ブロック数を数える
	void Debug_board();						//デバッグ用の盤面を表示
	bool GameOver(Side my);						//ゲームオーバー判定 true ゲームオーバー



	std::array<std::array<BoardData,8>,8> board;	//ボード配列
	int whiteNum = 0;			//白の数
	int blackNum = 0;			//黒の数
	bool turn = false;			//ターン　自分のターンはfalse
	int anim = 0;				//待機フレーム
	bool isGameOver = false;	//ゲームオーバーになったかどうか？
	Entry* owner;	//Entryクラス
};

#endif
