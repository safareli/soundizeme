#ifndef ball_h
#define ball_h

#include "ofMain.h"


#define MAX_VELOCITY        3
#define FFT_MAP_RADIUS      0.5
#define FFT_MAP_FORCE       0.36
#define FFT_FORCE_MAX       5
#define FFT_COLOR_LERP      0.175
#define NOISE_COLOR_LERP    0.355
#define MIN_SATURATION      100
#define MIN_BRIGHTNESS      150
#define NOISE_STEP          0.02
#define RADIUS_MIN          5
#define RADIUS_MAX          50

class Ball {
    public:
        Ball(ofVec2f _location,ofVec2f _velocity,ofColor _color,float _radius);

        void update(float vx,float vy,float r ,float c,float *param);
        void draw();

        ofVec2f location, velocity, acceleration;
        ofColor color;
        float radius;
        float noiseR,noiseG,noiseB;
    private:
        void checkEdges();
        void updateColor(float fftValue);
        void updateRadius(float fftValue);
        void applyFFTForce(ofVec2f FFTForce);
        void applyForce(ofVec2f force);
};
#endif
