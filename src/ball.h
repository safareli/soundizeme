#ifndef ball_h
#define ball_h
 
#include "ofMain.h"
 
class Ball {
public:
        Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color,float _radius);
 
        void update(float vx,float vy,float r ,float c,bool debag);
        void draw();
 
        ofVec2f location, velocity, acceleration;
        ofColor color;
        float radius;
};
#endif