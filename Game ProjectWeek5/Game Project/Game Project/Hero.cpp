#include "Hero.h"


Hero::Hero()
{
	animation = NULL;
	faceRight = true;

}


Hero::~Hero()
{
}


void Hero::setAnimation(Animation* animation){
	this->animation = animation;
}

void Hero::update(float dt){
	//TODO 
	//add new movement stuff

	if (velocity.x > 0)
		faceRight = true;
	if (velocity.x < 0)
		faceRight = false;


	//lazy friction force to apply to acceleration
	Vector friction(-0.5 * (velocity.x), -0.5 * (velocity.y));

	acceleration.x += friction.x;
	acceleration.y += friction.y;


	//update movement based on velocity
	updateMovement(dt);


	if (animation != NULL)
		animation->update(dt);

}
void Hero::draw(){
	if (animation != NULL){
		if (faceRight)
			animation->draw(position.x, position.y);
		else
			animation->draw(position.x, position.y, true);
	}
}
