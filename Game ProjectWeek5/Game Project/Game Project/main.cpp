#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> //text to font
#include "Animation.h"
#include "Entity.h"
#include "Wall.h"
#include <list>//linked list

using namespace std;


int main(int argc, char** argv){
	//initialise SDL with all its sub systems e.g video, input, sound etc
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout<<"SDL failed: "<<SDL_GetError()<<endl;
		system("pause");
		return -1;
	}
	//intialising images
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

	//loading image
	SDL_Surface* blackHoleSurface = IMG_Load("assets/blackhole.png");
	SDL_SetColorKey(blackHoleSurface,1,SDL_MapRGB(blackHoleSurface->format,128,128,255));
	SDL_Texture* blackHoleSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, blackHoleSurface);

	SDL_FreeSurface(blackHoleSurface);

	//Animations
	Animation anim2(blackHoleSpriteSheetWithNoBG, renderer, 4, 128, 128, 0.2);
	
	list<Entity*> entities;
	//setting up 2 walls
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


	// SETUP SOME TEXT
	TTF_Font* font = TTF_OpenFont("assets/something_strange.ttf", 150);
	SDL_Color textColor = { 0, 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Hell Dimension", textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	//text DESTINATION
	SDL_Rect textDestination;
	textDestination.x = 40;
	textDestination.y = 90;
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	//another font
	TTF_Font* titlefont = TTF_OpenFont("assets/arcade_classic.ttf", 60);
	SDL_Surface* textsSurface = TTF_RenderText_Blended(titlefont, "Pres  S  to  start", textColor);
	SDL_Texture* textsTexture = SDL_CreateTextureFromSurface(renderer, textsSurface);
	SDL_FreeSurface(textsSurface);
	//text DESTINATION
	SDL_Rect textsDestination;
	textsDestination.x = 220;
	textsDestination.y = 550;
	SDL_QueryTexture(textsTexture, NULL, NULL, &textsDestination.w, &textsDestination.h);

	Uint32 lastUpdate = SDL_GetTicks();
	bool loop = true;

	//game loop
	while (loop){ 

		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float DT = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();
		

		//Poll inputs
		SDL_Event event;
		//loop through all generated inputs
		while (SDL_PollEvent(&event)){
			//check if windos closed
			if (event.type == SDL_QUIT){
				loop = false;
			}
			//check if they pressed the esc key to exit window
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					loop = false;
				}
			}

		}

		//set drawing colour for renderer
		SDL_SetRenderDrawColor(renderer, 255, 140, 0, 1); 
		//clear screen with draw color
		SDL_RenderClear(renderer);

		for each(Entity* entity in entities){
			entity->update(DT);
			entity->draw();
		}

		//render text last ontop of all the other things
		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
		SDL_RenderCopy(renderer, textsTexture, NULL, &textsDestination);
		
		//animating black hole image
		anim2.update(DT);
		anim2.draw(320, 250, 2.0f);

		//render to the screen
		SDL_RenderPresent(renderer);

	}

	//CLEAN UP
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);


	SDL_Quit();

	return 0;
}