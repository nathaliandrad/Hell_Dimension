#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}


void Entity::setRenderer(SDL_Renderer* renderer){
	this->renderer = renderer;
}
void Entity::setXY(float x, float y){
	position.x = x;
	position.y = y;
}
float Entity::getX(){
	return position.x;
}
float Entity::getY(){
	return position.y;
}

void Entity::update(float dt){
	//do nothing, let sub classes deal with this
}


void Entity::updateMovement(float dt){
	//acceleration changes velocity
	velocity.x = velocity.x + (acceleration.x*dt);
	velocity.y = velocity.y + (acceleration.y*dt);
	
	//velocity changes position
	position.x = position.x + (velocity.x*dt);
	position.y = position.y + (velocity.y*dt);

}


void Entity::draw(){
	//same as update
}