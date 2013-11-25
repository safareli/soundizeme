#include "soundizeMeApp.h"

/*void soundizeMeApp::~soundizeMeApp(){

}*/
//--------------------------------------------------------------
void soundizeMeApp::setup(){

    // Smooth edges
    ofEnableSmoothing();

    // Fixed framerate
    ofSetFrameRate(60);

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	m_nBandsToGet = 1024;
	m_fftSmoothed = new float[m_nBandsToGet];
	for (int i = 0; i < m_nBandsToGet; i++){
		m_fftSmoothed[i] = 0;
	}

	/*
	1 sichqare X [-2,2]
	2 sichqare Y [-2,2]
	3 radiusi  [5,30]
	4 rgb	 setHex
	*/
	int balln = m_nBandsToGet/4;
	for (int i = 0; i < balln; ++i)
	{
		float alpha 		= ofRandom(0,360);
		ofVec2f location 	= ofVec2f(ofRandomWidth(),ofRandomHeight());
		ofVec2f velocity 	= ofVec2f(sin(alpha),cos(alpha));
		ofColor color 		= ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
		velocity *= ofRandom(0.5,2);
		m_balls.push_back(Ball(location,velocity,color,20));
	}
// fftColorLerp
// noiseColorLerp
// noiseStep

	slider1.setup("slider1", 50, 0, 100);
	slider2.setup("slider2", 50, 0, 100);
	slider3.setup("slider3", 50, 0, 100);
	slider4.setup("slider4", 50, 0, 100);
	m_gui.setup("params", 10, 10);
	m_gui.add(&slider1);
	m_gui.add(&slider2);
	m_gui.add(&slider3);
	m_gui.add(&slider4);

}

//--------------------------------------------------------------
void soundizeMeApp::update(){


	// grab the fft, and put in into a "smoothed" array,
	// by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(m_nBandsToGet * 2);		// request 1024 values for fft
	for (int i = 0;i < m_nBandsToGet; i++){

		// let the smoothed calue sink to zero:
		m_fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (m_fftSmoothed[i] < val[i]) m_fftSmoothed[i] = val[i];

	}

	float * paramns = new float[4];
	paramns[0] = slider1.getValue();
	paramns[1] = slider2.getValue();
	paramns[2] = slider3.getValue();
	paramns[3] = slider4.getValue();
	for (int i = 0; i < m_balls.size(); i++){
		m_balls.at(i).update(
			sqrt(m_fftSmoothed[i*4+0]),
			sqrt(m_fftSmoothed[i*4+1]),
			sqrt(m_fftSmoothed[i*4+2]),
			sqrt(m_fftSmoothed[i*4+3]),
			paramns
		);
	}
	delete[] paramns;
	m_debagFrame = false;
}

//--------------------------------------------------------------
void soundizeMeApp::draw(){
 	ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
 	for (int i = 0; i < m_balls.size(); ++i){
		m_balls.at(i).draw();
	}



	// ofSetColor(255,255,255,255);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0,ofGetHeight());
	m_nBandsToGet;
	for (int i = 0;i < m_nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		glVertex2f(i+1,ofGetHeight() - (m_fftSmoothed[i] * 200));
		// ofRect(i*width,ofGetHeight(),width,-(m_fftSmoothed[i] * 200) -5);
	}
	glEnd();
    m_gui.draw();

}

//--------------------------------------------------------------
void soundizeMeApp::keyPressed(int key){
	if (key == 'd'){
		cout << "m_balls.size()         " << m_balls.size() << endl;
		cout << "ofGetFrameRate()       " << ofGetFrameRate() << endl;
		cout << "ofGetTargetFrameRate() " << ofGetTargetFrameRate() << endl;
		m_debagFrame = true;
	}else if(key == 's'){
		// ofSaveViewport("ofSaveViewport.jpg");
		// ofSaveScreen("ofSaveScreen.jpg");
		ofSaveFrame();
	}else if(key == 'p'){
		m_audio.setPaused(m_isPlaying);
		m_isPlaying = !m_isPlaying;
	}
}

//--------------------------------------------------------------
void soundizeMeApp::keyReleased(int key){

}

//--------------------------------------------------------------
void soundizeMeApp::mouseMoved(int x, int y){

}
//--------------------------------------------------------------


//--------------------------------------------------------------
void soundizeMeApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void soundizeMeApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void soundizeMeApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void soundizeMeApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void soundizeMeApp::gotMessage(ofMessage msg){

}
//--------------------------------------------------------------
void soundizeMeApp::dragEvent(ofDragInfo dragInfo){
	if (dragInfo.files.size()){
        m_audio.loadSound(dragInfo.files.at(0),false);
        m_audio.play();
        m_isPlaying = true;

	}
}
