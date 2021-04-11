#ifndef ___ENTRY_HPP
#define ___ENTRY_HPP

#include <iostream>

class Input;
class Game;
class Entry
{
public:

	std::shared_ptr<Input> input;

	Entry();
	~Entry();


	void Update();
	void Draw();

private:

	std::shared_ptr<Game> game;

	
};
#endif
