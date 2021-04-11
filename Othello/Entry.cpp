#include "Entry.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include "DxLib.h"

Entry::Entry()
{
	input = std::make_shared<Input>();
	game = std::make_shared<Game>(this);

}


Entry::~Entry()
{

}



void Entry::Update()
{
	input->Update();

	game->Update();




	//‹­§I—¹
	if (input->getKeyDown(KEY_INPUT_ESCAPE) == true)
	{
		exit(0);
	}
}

void Entry::Draw()
{
	game->Draw();

}

