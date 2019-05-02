#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> //text to font
#include "Animation.h"
#include "Entity.h"
#include "Wall.h"
#include <list>//linked list
#include <SDL_mixer.h>//sound n music

using namespace std;

int main(int argc, char** argv){
	//initialise SDL with all its sub systems e.g video, input, sound etc
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout<<"SDL failed: "<<SDL_GetError()<<endl;
		system("pause");
		return -1;
	}

	//initialising images
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		cout << "sdl image failed: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//init sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		cout << "Mixer error: " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}


	//INIT sdl text font
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

	//SETUP initial game entities
	list<Entity*> entities;
	
	//adding walls to the menu scene
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


	// Setting up text
	TTF_Font* font = TTF_OpenFont("assets/something_strange.ttf", 90);
	SDL_Color textColor = { 0, 0, 0, 0 };
	//create surface using font, colours and some sort of message
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Hell Dimension", textColor);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	//text DESTINATION
	SDL_Rect textDestination;
	textDestination.x = 200;
	textDestination.y = 50;
	//query to get width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	//setting up other texts
	TTF_Font* menuFont = TTF_OpenFont("assets/arcade_classic.ttf", 50);
	SDL_Color menuTextColor = { 255, 255, 255, 0 };

	SDL_Surface* menuTextSurface = TTF_RenderText_Blended(menuFont, "start game", menuTextColor);
	//convert surface to texture
	SDL_Texture* menuTextTexture = SDL_CreateTextureFromSurface(renderer, menuTextSurface);
	SDL_FreeSurface(menuTextSurface);
	//text DESTINATION
	SDL_Rect menuTextDestination;
	menuTextDestination.x = 315;
	menuTextDestination.y = 185;
	//query to get width and height
	SDL_QueryTexture(menuTextTexture, NULL, NULL, &menuTextDestination.w, &menuTextDestination.h);

	//setting up other texts
	SDL_Surface* menuText2Surface = TTF_RenderText_Blended(menuFont, "load  game", menuTextColor);
	//convert surface to texture
	SDL_Texture* menuText2Texture = SDL_CreateTextureFromSurface(renderer, menuText2Surface);
	SDL_FreeSurface(menuText2Surface);
	//text DESTINATION
	SDL_Rect menuText2Destination;
	menuText2Destination.x = 325;
	menuText2Destination.y = 275;
	//query to get width and height
	SDL_QueryTexture(menuText2Texture, NULL, NULL, &menuText2Destination.w, &menuText2Destination.h);

	//setting up other texts
	SDL_Surface* menuText3Surface = TTF_RenderText_Blended(menuFont, "settings", menuTextColor);
	//convert surface to texture
	SDL_Texture* menuText3Texture = SDL_CreateTextureFromSurface(renderer, menuText3Surface);
	SDL_FreeSurface(menuText3Surface);
	//text DESTINATION
	SDL_Rect menuText3Destination;
	menuText3Destination.x = 330;
	menuText3Destination.y = 365;
	//query to get width and height
	SDL_QueryTexture(menuText3Texture, NULL, NULL, &menuText3Destination.w, &menuText3Destination.h);

	//setting up other texts
	SDL_Surface* menuText4Surface = TTF_RenderText_Blended(menuFont, "leaderboard", menuTextColor);
	//convert surface to texture
	SDL_Texture* menuText4Texture = SDL_CreateTextureFromSurface(renderer, menuText4Surface);
	SDL_FreeSurface(menuText4Surface);
	//text DESTINATION
	SDL_Rect menuText4Destination;
	menuText4Destination.x = 295;
	menuText4Destination.y = 455;
	//query to get width and height
	SDL_QueryTexture(menuText4Texture, NULL, NULL, &menuText4Destination.w, &menuText4Destination.h);

	//setting up other texts
	SDL_Surface* menuText5Surface = TTF_RenderText_Blended(menuFont, "quit game", menuTextColor);
	//convert surface to texture
	SDL_Texture* menuText5Texture = SDL_CreateTextureFromSurface(renderer, menuText5Surface);
	SDL_FreeSurface(menuText5Surface);
	//text DESTINATION
	SDL_Rect menuText5Destination;
	menuText5Destination.x = 330;
	menuText5Destination.y = 545;
	//query to get width and height
	SDL_QueryTexture(menuText5Texture, NULL, NULL, &menuText5Destination.w, &menuText5Destination.h);


	//uploading spritesheet Image
	SDL_Surface* bloodSurface = IMG_Load("assets/blackBlackHolesss.png");
	SDL_SetColorKey(bloodSurface, 1, SDL_MapRGB(bloodSurface->format, 256, 256, 255));
	//convert to texture
	SDL_Texture* bloodSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, bloodSurface);
	SDL_FreeSurface(bloodSurface);
	//Animations
	Animation anim(bloodSpriteSheetWithNoBG, renderer, 4, 64, 64, 0.2);
	Animation anim2(bloodSpriteSheetWithNoBG, renderer, 4, 64, 64, 0.2);


	//LOAD UP SOME MUSIC
	Mix_Music* music = Mix_LoadMUS("assets/World-of-Automatons_Looping.mp3");
	if (music == NULL){
		cout << "Music failed! : " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//Play the music!
	//params: music to play
	//		how many times to loop the music (-1 play infinitely)
	Mix_PlayMusic(music, -1);



	//stuff for time management
	Uint32 lastUpdate = SDL_GetTicks();
	bool loop = true;

	//game loop
	while (loop){ 

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
			//check if they pressed the esc key to exti the window
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

		//start drawing rectangles to design mmenu sreen		
		//rectangle1 inner 
		SDL_Rect rectangle1 = { 235, 170, 420, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rectangle1);
		//outside rectangle
		SDL_Rect rectangle2 = { 245, 180, 400, 60 };
		SDL_SetRenderDrawColor(renderer, 139, 0, 0, 1); //rgba(139,0,0 ,1 )
		SDL_RenderFillRect(renderer, &rectangle2);

		//rectangle 2
		SDL_Rect rectangle3 = { 235, 260, 420, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);	
		SDL_RenderFillRect(renderer, &rectangle3);
		//outside rectangle
		SDL_Rect rectangle4 = { 245, 270, 400, 60 };
		SDL_SetRenderDrawColor(renderer, 139, 0, 0, 1); //rgba(139,0,0 ,1 )
		SDL_RenderFillRect(renderer, &rectangle4);

		//rectangle 3
		SDL_Rect rectangle5 = { 235, 350, 420, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rectangle5);
		//outside rectangle
		SDL_Rect rectangle6 = { 245, 360, 400, 60 };
		SDL_SetRenderDrawColor(renderer, 139, 0, 0, 1); //rgba(139,0,0 ,1 )
		SDL_RenderFillRect(renderer, &rectangle6);


		//rectangle 4
		SDL_Rect rectangle7 = { 235, 440, 420, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rectangle7);
		//outside rectangle
		SDL_Rect rectangle8 = { 245, 450, 400, 60 };
		SDL_SetRenderDrawColor(renderer, 139, 0, 0, 1); //rgba(139,0,0 ,1 )
		SDL_RenderFillRect(renderer, &rectangle8);

		//rectangle 5
		SDL_Rect rectangle9 = { 235, 530, 420, 80 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rectangle9);
		//outside rectangle
		SDL_Rect rectangl10 = { 245, 540, 400, 60 };
		SDL_SetRenderDrawColor(renderer, 139, 0, 0, 1); //rgba(139,0,0 ,1 )
		SDL_RenderFillRect(renderer, &rectangl10);


		//render text last ontop of all the other things
		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
		SDL_RenderCopy(renderer, menuTextTexture, NULL, &menuTextDestination);
		SDL_RenderCopy(renderer, menuText2Texture, NULL, &menuText2Destination);
		SDL_RenderCopy(renderer, menuText3Texture, NULL, &menuText3Destination);
		SDL_RenderCopy(renderer, menuText4Texture, NULL, &menuText4Destination);
		SDL_RenderCopy(renderer, menuText5Texture, NULL, &menuText5Destination);

		//updating blood animation
		anim.update(DT);
		anim2.update(DT);
		//right image
		anim.draw(690, 30, 1.8f);
		//left image
		anim2.draw(70, 30, 1.8f);


		SDL_RenderPresent(renderer);

	
	}


	//stop playing music BEFORE you release its memory
	Mix_PausedMusic();
	//delete song from memory
	Mix_FreeMusic(music);

	//releasing memory/ destroying
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}