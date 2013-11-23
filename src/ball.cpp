#include "ball.h"
 
Ball::Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color){
	location 	= 	_location;
	velocity 	= 	_velocity;
	color 		= 	_color;
}
 
void Ball::update(){
	velocity = velocity + acceleration;
	location = location + velocity;
}
 
void Ball::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(location.x, location.y, 30);
}