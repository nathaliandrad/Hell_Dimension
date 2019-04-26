#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> //text to font
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "Wall.h"
#include <list>//linked list
#include "InputHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GameControllerHandler.h"


using namespace std;


int main(int argc, char** argv){
	//initialise SDL with all its sub systems e.g video, input, sound etc
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout<<"SDL failed: "<<SDL_GetError()<<endl;
		system("pause");
		return -1;
	}

	//need to initialise other sub libraries
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		cout << "sdl image failed: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//INIT sdl ttf
	if (TTF_Init() != 0){
		cout << "sdl ttf failed: " << TTF_GetError() << endl;
		system("pause");
		return -1;
	}




	//create window to render into
	//params: (title, position x, position y, width, height, window flags)
	SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		900, 700, SDL_WINDOW_SHOWN); //fullscreen with last param like this: SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN

	if(window == NULL)
	{
		cout<<"window failed: "<<SDL_GetError()<<endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	//create a renderer, which helps draw stuff to the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == NULL){
		cout<<"renderer failed: "<<SDL_GetError()<<endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	//load image into ram, as a surface we can access and tweak pixel data if we like
	SDL_Surface* knightSurface = SDL_LoadBMP("assets/knight.bmp");

	//convert surface into texture. texture will be stored in VRAM for our graphics card to use
	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);

	//dont need surface anymore, lets free its memory
	SDL_FreeSurface(knightSurface);

	//Region we want to draw from our texture
	SDL_Rect sourceRect;
	sourceRect.x = 50;
	sourceRect.y = 60;

	//ask gfx card about widht and height of our texture and store it on our sourceRect
	////SDL_QueryTexture(knightTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.w = 80;
	sourceRect.h = 80;



	//where to draw a knight
	SDL_Rect destinationRect;
	destinationRect.x = 100;
	destinationRect.y = 100;
	destinationRect.w = sourceRect.w*4;
	destinationRect.h = sourceRect.h*2;

	//run texture
	SDL_Texture* runSpriteSheet = IMG_LoadTexture(renderer, "assets/run.png");
	//lest just draw 1 frame of this spritesheet for now
	SDL_Rect runClipRect = { 0, 0, 32, 32 };//x=0,y=0,w=32,h=32
	SDL_Rect runDestRect = { 0, 0, 128, 128 };
	//lets make a version of run where background purple is transparent
	SDL_Surface* runSurface = IMG_Load("assets/run.png");
	//set colour key
	//params: surface
	//	1 = turn on color key, 0 is off
	//	color to act as transparent color. SDL_MapRGB r g b values to the closest match it has its palete
	SDL_SetColorKey(runSurface,1,SDL_MapRGB(runSurface->format,128,128,255));
	//convert to texture
	SDL_Texture* runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);

	SDL_FreeSurface(runSurface);


	//Animations
	Animation anim1(runSpriteSheet, renderer, 4, 32, 32, 0.1);
	Animation anim2(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.7);
	Animation anim3(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.4);

	//SETUP initial game entities
	list<Entity*> entities;
	//build a hero
	Hero* hero = new Hero();
	hero->setAnimation(&anim2);
	hero->setRenderer(renderer);
	hero->setXY(200, 200);
	hero->acceleration.x = 200; // pixels que anda....
	//add to list
	entities.push_back(hero);

	//lets add 2 walls
	Wall* wall1 = new Wall();
	wall1->setRenderer(renderer);
	wall1->setXY(0, 0);
	wall1->setWH(900, 32);
	entities.push_back(wall1);


	Wall* wall2 = new Wall();
	wall2->setRenderer(renderer);
	wall2->setXY(0, 670);
	wall2->setWH(900, 32);
	entities.push_back(wall2);


	//input stuff
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero;


	MouseHandler mouseHandler;
	mouseHandler.hero = hero;


	GameControllerHandler controllerHandler;
	controllerHandler.hero = hero;



	//can still use abstract classses for referecing/polymorphism
	InputHandler* inputHandler = &keyboardHandler;



	// SETUP SOME TEXT
	TTF_Font* font = TTF_OpenFont("assets/something_strange.ttf", 150);
	SDL_Color textColor = { 0, 0, 0, 0 };
	//create surface using font, colours and some sort of message
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Hell Dimension", textColor);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	//text DESTINATION
	SDL_Rect textDestination;
	textDestination.x = 40;
	textDestination.y = 90;
	//query to get width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);





	TTF_Font* titlefont = TTF_OpenFont("assets/arcade_classic.ttf", 60);
	

	SDL_Surface* textsSurface = TTF_RenderText_Blended(titlefont, "Pres  S  to  start", textColor);
	//convert surface to texture
	SDL_Texture* textsTexture = SDL_CreateTextureFromSurface(renderer, textsSurface);
	SDL_FreeSurface(textsSurface);

	//text DESTINATION
	SDL_Rect textsDestination;
	textsDestination.x = 220;
	textsDestination.y = 550;
	//query to get width and height
	SDL_QueryTexture(textsTexture, NULL, NULL, &textsDestination.w, &textsDestination.h);







	//stuff for time management
	Uint32 lastUpdate = SDL_GetTicks();


	bool loop = true;
	while (loop){ //game loop

		//time management, work our Delta Time

		//how many milliseconds since the last time this part of the loop ran
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert whole milliseconds into a fraction of a second for DT
		float DT = timeDiff / 1000.0;//e.g 200ms = 0.2 for DT
		//update last update so next loop calculates properly 
		lastUpdate = SDL_GetTicks();
		

		//Poll inputs
		SDL_Event event;
		//loop through all generated inputs
		while (SDL_PollEvent(&event)){
			//check if windos closed
			if (event.type == SDL_QUIT){
				loop = false;
			}
			//check if they pressed the esc key
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					loop = false;
				}
			}
			//update input handler, whatever it is
			inputHandler->update(&event);

			mouseHandler.update(&event);

			controllerHandler.update(&event);

		}


		if (controllerHandler.controller == NULL)
			keyboardHandler.updateHeldKeys();//check held down keys
		else
			controllerHandler.updateSticksAndDPads();
		




		//set drawing colour for renderer, uses RGBA, each value between 0-255
		SDL_SetRenderDrawColor(renderer, 255, 140, 0, 1); 
		//clear screen with draw color
		SDL_RenderClear(renderer);


		for each(Entity* entity in entities){
			entity->update(DT);
			entity->draw();
		}


		/*
		//rectangle to draw ( x, y, width, height)
		SDL_Rect rectangle = { 50, 30, 200, 100 };
		//magenta
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

		//draw coloured in rectangle to screen
		SDL_RenderFillRect(renderer, &rectangle);

		//draw our 2d image
		//use source rect to clip our texture and draw it destination rect on screen
		SDL_RenderCopy(renderer, knightTexture, &sourceRect, &destinationRect);

		//lets updating the animation
		int const runNumOfFrames = 4;
		runClipRect.x = runClipRect.w*int((SDL_GetTicks() / 100) % runNumOfFrames);

		SDL_RenderCopy(renderer, runSpriteSheet, &runClipRect, &runDestRect);

		//updates
		anim1.update(DT);
		anim2.update(DT);
		anim3.update(DT);
		//draws
		anim1.draw(400, 300);
		anim2.draw(450, 300,4.0f);
		anim3.draw(500, 300, true);
		*/


		//render text last ontop of all the other things
		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);

		SDL_RenderCopy(renderer, textsTexture, NULL, &textsDestination);
		SDL_RenderCopy(renderer, knightTexture, &sourceRect, &destinationRect);

		//render to the screen
		SDL_RenderPresent(renderer);

		//lest exit after 5 seconds still.
		//SDL_GetTicks returns number of milliseconds since the start of the program/game
		//if (SDL_GetTicks() > 5000){
		//   loop = false;
		//  }
	}


	//wait for 5 seconds
	////SDL_Delay(5000);//in milliseconds

	//CLEAN UP
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(knightTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}