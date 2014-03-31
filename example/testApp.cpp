#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(30);

	camW = 640;
	camH = 480;

	motionDetector.setup(camW, camH);

}

//--------------------------------------------------------------
void testApp::update(){

	motionDetector.update();

}

//--------------------------------------------------------------
void testApp::draw(){

	motionDetector.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key){
	case 'f':
	case 'F':
		ofToggleFullscreen();
		break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::exit(){
	motionDetector.save();
}