#include "soundizeMeApp.h"

/*void soundizeMeApp::~soundizeMeApp(){

}*/
//--------------------------------------------------------------
void soundizeMeApp::setup(){

    // Smooth edges
    ofEnableSmoothing();

    // Fixed framerate
    ofSetFrameRate(60);

    //ofAddListener(ofEvents.fileDragEvent,this,&soundizeMeApp::onFileDragEvent);
	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	m_fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		m_fftSmoothed[i] = 0;
	}

	m_nBandsToGet = 1024;
/*
1 sichqare X [-2,2]
2 sichqare Y [-2,2]
3 radiusi  [5,30]
4 rgb	 setHex
*/
	int balln = m_nBandsToGet/4;
	for (int i = 0; i < balln; ++i)
	{
		ofVec2f location, velocity;
		ofColor color;
		location.set(ofRandomWidth(),ofRandomHeight());
		float alpha = ofRandom(0,360);
		velocity.set(sin(alpha),cos(alpha));
		velocity*= ofRandom(0.5,2);
		color.set(0, 0, 0);
		m_balls.push_back(Ball(location,velocity,color,20));
	}

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

	for (int i = 0; i < m_balls.size(); i++){
		m_balls.at(i).update(
			m_fftSmoothed[i*4+0],
			m_fftSmoothed[i*4+1],
			m_fftSmoothed[i*4+2],
			m_fftSmoothed[i*4+3],
			m_debagFrame
		);
	}
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

	}
}
