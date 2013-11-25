#include "ball.h"
Ball::Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color,float _radius){
    location	=	_location;
    velocity	=	_velocity;
    color		=	_color;
    radius		=	_radius;
}

void Ball::update(float vx,float vy,float r ,float c){
 
  
 

        //limit r to 0.35
	r = (r > 0.5) ? 0.5 :r;
	radius = ofMap(r, 0, 0.5, 2, 50);


	float angle =ofMap(vy, 0, 0.34, 0,TWO_PI);
	acceleration.set(sin(angle),cos(angle));
	acceleration *=ofMap(vy, 0, 0.34, 0, 5);
	if (velocity.dot(acceleration) < 0.9)
	{
        acceleration /= radius;
	}

	ofColor icolor;
    icolor.setHex(ofMap(r, 0, 0.35, 0, 255*255*255));
    color.lerp(icolor,0.25);



	if (location.x > ofGetWidth() + radius*2)
        location.x  =   -radius*2;
	else if (location.x < -radius*2)
        location.x  =  ofGetWidth() + radius*2;

	if (location.y > ofGetHeight() + radius*2)
        location.y  =  -radius*2;
	else if (location.y < -radius*2)
        location.y  =  ofGetHeight() + radius*2;

	velocity = velocity + acceleration;
	location = location + velocity;
	velocity.limit(3);
	acceleration = acceleration * 0;



}

void Ball::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(location.x, location.y, radius);
}
