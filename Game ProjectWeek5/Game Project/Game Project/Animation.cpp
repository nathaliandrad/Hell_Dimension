#include "Animation.h"


Animation::Animation()
{
}


Animation::Animation(SDL_Texture* texture, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration){
	this->spriteSheet = texture;
	this->renderer = renderer;
	this->numberOfFrames = numberOfFrames;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frameDuration = frameDuration;

	currentFrame = 0;//0 as first frame
	frameTimer = 0;
}
void Animation::update(float dt){
	//update frameTimer
	frameTimer += dt;

	//if this frame has been on screen long enough
	if (frameTimer >= frameDuration){
		//move to next frame
		currentFrame++;
		//reset timer
		frameTimer = 0;

		//if past the end, loop animation back to start frame
		if (currentFrame >= numberOfFrames){
			currentFrame = 0;
		}
	}
}
void Animation::draw(int x, int y){
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0; //if having multiple rows of animation, this part will need to be changed
	clip.w = frameWidth;
	clip.h = frameHeight;
	//setup destination rectangle
	SDL_Rect dest = { x, y, frameWidth, frameHeight };
	//draw
	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);

}
void Animation::draw(int x, int y,float scale){
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0; //if having multiple rows of animation, this part will need to be changed
	clip.w = frameWidth;
	clip.h = frameHeight;
	//setup destination rectangle
	SDL_Rect dest = { x, y, frameWidth*scale, frameHeight*scale };
	//draw
	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);

}
void Animation::draw(int x, int y, bool flip){
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0; //if having multiple rows of animation, this part will need to be changed
	clip.w = frameWidth;
	clip.h = frameHeight;
	//setup destination rectangle
	SDL_Rect dest = { x, y, frameWidth, frameHeight };
	
	//setup flip flag
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if (flip)
		flipType = SDL_FLIP_HORIZONTAL;

	//draw										   angle,rotation center, flip flag
	SDL_RenderCopyEx(renderer, spriteSheet, &clip, &dest, 0,NULL, flipType);

}
