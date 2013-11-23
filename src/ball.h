#ifndef ball_h
#define ball_h
 
#include "ofMain.h"
 
class Ball {
public:
        Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color);
 
        void update();
        void draw();
 
        ofVec2f location, velocity, acceleration;
        ofColor color;
};
#endif