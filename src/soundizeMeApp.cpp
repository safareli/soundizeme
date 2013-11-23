#include "soundizeMeApp.h"

//--------------------------------------------------------------
void soundizeMeApp::setup(){

    // Smooth edges
    ofEnableSmoothing();

    // Fixed framerate
    ofSetFrameRate(60);

}

//--------------------------------------------------------------
void soundizeMeApp::update(){
	for (int i = 0; i < m_balls.size(); ++i){
		m_balls.at(i).update();
	}
}

//--------------------------------------------------------------
void soundizeMeApp::draw(){
 	ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
 	for (int i = 0; i < m_balls.size(); ++i){
		m_balls.at(i).draw();
	}
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < ofGetWidth(); ++i){
		glVertex2f(i,ofNoise(ofGetFrameNum()*0.01, i*0.01)*50);
	}
	glEnd();
}

//--------------------------------------------------------------
void soundizeMeApp::keyPressed(int key){
	if (key == 'd'){
		cout << "m_balls.size()         " << m_balls.size() << endl;
		cout << "ofGetFrameRate()       " << ofGetFrameRate() << endl;
		cout << "ofGetTargetFrameRate() " << ofGetTargetFrameRate() << endl;
	}else if(key == 's'){
		// ofSaveViewport("ofSaveViewport.jpg");
		// ofSaveScreen("ofSaveScreen.jpg");
		ofSaveFrame();
	}else if(key == 'o'){
		ofFileDialogResult dialog_result = ofSystemLoadDialog("open mp3",false);
		if (dialog_result.bSuccess){
			cout << "Name: " <<dialog_result.getName() << endl;
			cout << "Path: " <<dialog_result.getPath() << endl;
		}
	}

}

//--------------------------------------------------------------
void soundizeMeApp::keyReleased(int key){

}

//--------------------------------------------------------------
void soundizeMeApp::mouseMoved(int x, int y){

}
//--------------------------------------------------------------
void soundizeMeApp::addBall(){
	ofVec2f location, velocity;
	ofColor color;
	location.set(mouseX,mouseY);
	velocity.set(ofRandom(-2,2),ofRandom(-2,2));
	color.set(ofRandom(255), ofRandom(255), ofRandom(255));
	m_balls.push_back(Ball(location,velocity,color));
}

//--------------------------------------------------------------
void soundizeMeApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < 10; ++i){
		addBall();
	}
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

}
