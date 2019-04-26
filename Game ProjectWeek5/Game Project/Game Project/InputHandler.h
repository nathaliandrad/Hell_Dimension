#pragma once
#include <SDL.h>
#include "Hero.h"

//this class is abstractbecause it contains an abstract function
//abstract class cannot be instatiated: cant do InputHandler myHandler;
//use abstract classes as parent, helps setup a pattern children will inherit
class InputHandler
{
public:
	Hero* hero;

	InputHandler();
	~InputHandler();


	virtual void update(SDL_Event* event) = 0; // <--- 0 means this is an abstract function

};

