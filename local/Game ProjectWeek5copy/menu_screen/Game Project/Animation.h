#pragma once
#include <SDL.h>
class Animation
{
public:

	int numberOfFrames;
	int frameWidth, frameHeight;
	float frameDuration;
	SDL_Texture* spriteSheet;
	SDL_Renderer* renderer;

	//current state of animation
	int currentFrame;
	float frameTimer;

	Animation();
	Animation(SDL_Texture* texture, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);
	void update(float dt);
	void draw(int x, int y);
	void draw(int x, int y, float scale);
	void draw(int x, int y, bool flip);
	void draw(int x, int y, bool flip, float scale);

};

