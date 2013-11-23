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
	theBall.moveTo(mouseX,mouseY);
}

//--------------------------------------------------------------
void soundizeMeApp::draw(){
 	ofBackgroundGradient(ofColor::gray,ofColor(30,10,30), OF_GRADIENT_CIRCULAR);
    theBall.draw();
}

//--------------------------------------------------------------
void soundizeMeApp::keyPressed(int key){
	// cout << "keyPressed " << key << endl;

}

//--------------------------------------------------------------
void soundizeMeApp::keyReleased(int key){

}

//--------------------------------------------------------------
void soundizeMeApp::mouseMoved(int x, int y){

}

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

}
