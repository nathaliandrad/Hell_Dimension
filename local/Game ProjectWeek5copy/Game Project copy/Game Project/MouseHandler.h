#pragma once
#include "InputHandler.h"
class MouseHandler :
	public InputHandler
{
public:
	bool leftMouseHeld;


	MouseHandler();
	~MouseHandler();

	virtual void update(SDL_Event* event);

};

