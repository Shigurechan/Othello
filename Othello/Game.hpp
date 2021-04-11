#ifndef ___GAME_HPP
#define ___GAME_HPP
#include "glm/glm.hpp"
#include <array>

//�O���錾
class Entry;


#define BOARD_SIZE ((int)8)	//�ՖʃT�C�Y
#define CELL ((int)48)		//�Z��

//�u���b�N�^�C�v
typedef enum class Side
{
	White,
	Black,
	None,
}Side;


/*�Z���̃I�u�W�F�N�g������
* 
* 0�@��
* 1�@�� 
* 2�@�Ȃ�

*/
class BoardData
{
public:

	//�R���X�g���N�^
	BoardData(Side s,glm::ivec2 p)
	{
		side = s;
		pos - p;
	}


	//�f�t�H���g�R���X�g���N�^
	BoardData()	
	{
		side = Side::None;
		pos = glm::ivec2(-1,-1);
	}




	Side side;		//��������̂��H
	glm::ivec2 pos;	//���W	
};


class Game
{
public:
	Game(Entry* entry);
	~Game();

	void Update();
	void Draw();


private:

	//�X�v���C�g
	int whiteSprite;	//��
	int blackSprite;	//��
	int boardSprite;	//�{�[�h


	Side mySide = Side::Black;


	bool getIsPut(glm::ivec2 p, Side my);	//���̏ꏊ�ɒu���邩�ǂ����H

	//BoardData board[BOARD_SIZE][BOARD_SIZE];		//�{�[�h�z��
	std::array<std::array<BoardData,8>,8> board;	//�{�[�h�z��

	Entry* owner;	//Entry�N���X
};

#endif