//
//  MotionDetector
//
//  Created by T9T9.com 2014/04/01
//
//

#include "ofxMotionDetector.h"

#define PREVIEW_W	320
#define PREVIEW_H	240

ofxMotionDetector::ofxMotionDetector(){
	isMotionDetected = false;
}

void ofxMotionDetector::setup(int camW, int camH){

	w = camW;
	h = camH;

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(w,h);

	colorImg.allocate(w,h);
	grayImg.allocate(w,h);
	diffImg.allocate(w,h);
	binaryImg.allocate(w,h);

	drawGui = true;

	gui.setup("LaserMouse"); // most of the time you don't need a name
	gui.add(guiHelp.setup("[H] Key ", "Hide Menu"));
	gui.add(imgThreshold.setup("Threshold", 30, 0, 255));
	gui.add(minArea.setup("Min Area", 20, 0, 300*200));
	gui.add(maxArea.setup("Max Area", 900, 0, 600*400));
	gui.add(hMirror.setup("H Mirror", false));
	gui.add(vMirror.setup("V Mirror", false));
	gui.add(debugView.setup("Debug View", true));
	gui.add(motionStatus.setup("Motion ", ""));

	gui.loadFromFile("settings.xml");
	gui.setPosition( 0, 0 );

}

void ofxMotionDetector::update(){

	vidGrabber.update();

	if (vidGrabber.isFrameNew()){
		colorImg.setFromPixels(vidGrabber.getPixels());
		colorImg.mirror( vMirror, hMirror );

		grayImg = colorImg;		

		diffImg.absDiff(grayImg, grayPrevImg);

		grayPrevImg = colorImg;

		binaryImg = diffImg;
		binaryImg.threshold(imgThreshold);

		contourFinder.findContours(binaryImg, minArea, maxArea, 10, false);

		if (contourFinder.nBlobs > 0){
			isMotionDetected = true;
			motionStatus = "detected";
		}else{
			isMotionDetected = false;
			motionStatus = "none";
		}
	}
	
}

void ofxMotionDetector::draw(){

	ofBackgroundGradient(ofColor::gray, ofColor::black);

	ofSetColor(255);

	if (debugView){
		ofPushMatrix();
		ofTranslate( 200, 0 );
		colorImg.draw( 0, 0, PREVIEW_W, PREVIEW_H);
		grayImg.draw( PREVIEW_W, 0, PREVIEW_W, PREVIEW_H);
		diffImg.draw( PREVIEW_W, PREVIEW_H, PREVIEW_W, PREVIEW_H);
		binaryImg.draw( 0, PREVIEW_H, PREVIEW_W, PREVIEW_H);

		// Contour Finder
		ofTranslate( 0, PREVIEW_H );
		ofScale((float)PREVIEW_W / w,(float)PREVIEW_H / h);
		
		
		int x, y;

		for (int i = 0; i < contourFinder.nBlobs; i++){
			stringstream str;

			contourFinder.blobs[i].draw(0, 0);

			x = (contourFinder.blobs[i].centroid.x);
			y = (contourFinder.blobs[i].centroid.y);

			ofSetColor(ofColor::red);

			str << std::fixed << setprecision(0) << x << "," << setprecision(0) << y;

			ofDrawBitmapString(str.str(), x, y);

			str.clear();
		}
		ofPopMatrix();

		ofPopStyle();
		ofPopMatrix();
	}

	if (drawGui){
		ofEnableAlphaBlending();
		gui.draw();
		ofDisableAlphaBlending();
	}

}

void ofxMotionDetector::save(){
	gui.saveToFile("settings.xml");
}