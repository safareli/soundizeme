#include "ball.h"
Ball::Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color,float _radius){
    location	=	_location;
    velocity	=	_velocity;
    color		=	_color;
    radius		=	_radius;
    noiseR		=	ofRandom(5000);
    noiseG		=	ofRandom(5000);
    noiseB		=	ofRandom(5000);

}

void Ball::update(float vx,float vy,float r ,float c,float* params){

// fftColorLerp
// noiseColorLerp
// noiseStep


        //limit r to 0.35
	r = (r > 0.5) ? 0.5 :r;
	radius = ofMap(r, 0, 0.5, 10, 50);


	float angle =ofMap(vy, 0, 0.34, 0,TWO_PI);
	acceleration.set(sin(angle),cos(angle));
	acceleration *=ofMap(vy, 0, 0.34, 0, 5);
	if (velocity.dot(acceleration) < 0.9)
        acceleration /= radius;

	if (r != 0){
		ofColor icolor;
	    icolor.setHex(ofMap(r, 0, 0.35, 0, 255*255*255));
	    color.lerp(icolor,0.175); //params[0]
	};
	ofColor disiredColor = ofColor(
		ofMap(ofNoise(noiseR), 0, 1, 0, 255),
		ofMap(ofNoise(noiseG), 0, 1, 0, 255),
		ofMap(ofNoise(noiseB), 0, 1, 0, 255)
	);
	color.lerp(disiredColor,0.355); //params[1]
	if(color.getBrightness() < 150)
		color.setBrightness(150);

	if(color.getSaturation() < 100)
		color.setSaturation(100);


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
	noiseR += 0.02;
	noiseG += 0.02;
	noiseB += 0.02;


}

void Ball::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(location.x, location.y, radius);
}
