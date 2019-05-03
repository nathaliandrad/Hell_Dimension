#include "Wall.h"

Wall::Wall()
{
}


Wall::~Wall()
{
}


void Wall::setWH(float w, float h){
	this->w = w;
	this->h = h;
}

void Wall::draw(){
	SDL_Rect wallRect = { position.x, position.y, w, h };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &wallRect);
}
