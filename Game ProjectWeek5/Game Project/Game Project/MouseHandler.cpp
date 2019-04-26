#include "MouseHandler.h"


MouseHandler::MouseHandler()
{
	leftMouseHeld = false;
}


MouseHandler::~MouseHandler()
{
}

void MouseHandler::update(SDL_Event* event){
	//check if left click
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
		//check if mouse was clicked over hero
		if (event->button.x >= hero->position.x && event->button.x <= hero->position.x + 32 && event->button.y >= hero->position.y && event->button.y <= hero->position.y + 32){
		
			leftMouseHeld = true;
		}
	}
	//check to see if left mouse button was release
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT){
		leftMouseHeld = false;
	}
	if (leftMouseHeld && event->type == SDL_MOUSEMOTION){
		hero->setXY(event->motion.x, event->motion.y);
	}

}
