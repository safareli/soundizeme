#include "ball.h"
Ball::Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color,float _radius){
    location    =   _location;
    velocity    =   _velocity;
    color       =   _color;
    radius      =   _radius;
    noiseR      =   ofRandom(5000);
    noiseG      =   ofRandom(5000);
    noiseB      =   ofRandom(5000);

}
void Ball::updateColor(float fftValue){
    if (fftValue != 0){
        color.lerp(ofColor::fromHex(ofMap(fftValue, 0, 0.35, 0, 255*255*255)),FFT_COLOR_LERP);
    }

    color.lerp(ofColor(
        ofMap(ofNoise(noiseR), 0, 1, 0, 255),
        ofMap(ofNoise(noiseG), 0, 1, 0, 255),
        ofMap(ofNoise(noiseB), 0, 1, 0, 255)
    ),NOISE_COLOR_LERP);
    
    if(color.getBrightness() < MIN_BRIGHTNESS)
        color.setBrightness(MIN_BRIGHTNESS);
    if(color.getSaturation() < MIN_SATURATION)
        color.setSaturation(MIN_SATURATION);


    noiseR += NOISE_STEP;
    noiseG += NOISE_STEP;
    noiseB += NOISE_STEP;
}

void Ball::checkEdges(){
    float diameter = radius*2;
    if (location.x > ofGetWidth() + diameter)
        location.x  =   -diameter;
    else if (location.x < -diameter)
        location.x  =  ofGetWidth() + diameter;

    if (location.y > ofGetHeight() + diameter)
        location.y  =  -diameter;
    else if (location.y < -diameter)
        location.y  =  ofGetHeight() + diameter;
}
void Ball::updateRadius(float fftValue){ 
    if(fftValue > FFT_MAP_RADIUS)
        fftValue = FFT_MAP_RADIUS;
    radius = ofMap(fftValue, 0, FFT_MAP_RADIUS, RADIUS_MIN, RADIUS_MAX);
}

void Ball::applyFFTForce(ofVec2f FFTForce){
    float angle = ofMap(FFTForce.x, 0, FFT_MAP_FORCE, 0,TWO_PI);
    float length = ofMap(FFTForce.y, 0, FFT_MAP_FORCE, 0, FFT_FORCE_MAX);
    FFTForce.set(sin(angle),cos(angle));
    FFTForce = FFTForce * length;
    applyForce(FFTForce);
}

void Ball::applyForce(ofVec2f force){
    // force = force / mass //radius
    acceleration = acceleration + force;   
}

void Ball::update(float vx,float vy,float r ,float c,float* params){
    updateRadius(r);
    applyFFTForce(ofVec2f(vx,vy));
    updateColor(c);

    velocity = velocity + acceleration;
    velocity.limit(MAX_VELOCITY);
    location = location + velocity;
    acceleration = acceleration * 0;

    checkEdges();
}

void Ball::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(location.x, location.y, radius);
}
