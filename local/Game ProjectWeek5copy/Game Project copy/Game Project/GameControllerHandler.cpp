#include "GameControllerHandler.h"


GameControllerHandler::GameControllerHandler()
{
	//how many joysticks are connected? Remember hoysticks includes gamepads, joysticks, steering wheels etc
	int numJoySticks = SDL_NumJoysticks();

	//loop through joysticks
	for (int joyStickID = 0; joyStickID < numJoySticks; joyStickID++){
		//check if each joystick can be considered "game controller" is similar in design to xbox controller
		if (SDL_IsGameController(joyStickID)){
			//if it is, open this controller
			controller = SDL_GameControllerOpen(joyStickID);
			//we are done now
			break;
		}
	}
}


GameControllerHandler::~GameControllerHandler()
{
	//close controller off if we have one
	if (controller != NULL)
		SDL_GameControllerClose(controller);
}

void GameControllerHandler::update(SDL_Event* event){
	//if got controller and its not detached
	if (controller != NULL && SDL_GameControllerGetAttached(controller)){
		//lets get joystickID from this controller
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));

		//check if event was from our controller
		if (event->cdevice.which == joystickID){
			//which event?
			//IF unplugged
			if (event->type == SDL_CONTROLLERDEVICEREMOVED){
				//close controller
				SDL_GameControllerClose(controller);
				controller = NULL;
				return; //dont run rest of this function
			}
			//IF button pressed
			if (event->type == SDL_CONTROLLERBUTTONDOWN){
				//note: treats all game controllers like xbox controllers, so if user pressed x on a ps4 controller it
				//triggers the A button press
				if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A){
					//reset hero
					hero->position.x = 200;
					hero->position.y = 200;
				}
				//TODO add other button presses e.g B = dodge;


			}
		}

	}

}

void GameControllerHandler::updateSticksAndDPads(){
	if (controller != NULL && SDL_GameControllerGetAttached(controller)){
		//reset acceleration
		hero->acceleration.x = 0;
		hero->acceleration.y = 0;

		//read values from left sticks X and Y axes
		Sint16 axisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);//-values are left, + are right
		Sint16 axisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);//- is up, + down

		//setup deadzone values, because sticks never tend to rest at 0
		int deadzone = 10000;


		//check which way sticks are being pushed
		//LEFT or DPAD left
		if (axisX < -deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)){
			hero->acceleration.x = -80;
		}

		//right
		if (axisX > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)){
			hero->acceleration.x = 80;
		}
		//up
		if (axisY < -deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)){
			hero->acceleration.y = -80;
		}
		//down
		if (axisY > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)){
			hero->acceleration.y = 80;
		}

	
	}
}
