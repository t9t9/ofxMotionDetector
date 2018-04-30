//
//  MotionDetector
//
//  Created by T9T9.com 2014/04/01
//

#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofxMotionDetector{

public:
	ofxMotionDetector();

	void			setup(int camW=640, int camH=480, int cameraDeviceID = 0);
	void			update();
	void			draw();
	void			save();

	int				w, h;

	ofVideoGrabber 	vidGrabber;

	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage		grayImg;
	ofxCvGrayscaleImage		grayPrevImg;
	ofxCvGrayscaleImage		diffImg;
	ofxCvGrayscaleImage 	binaryImg;

	ofxCvContourFinder		contourFinder;

	bool			isMotionDetected;

	// GUI group
	bool			drawGui;

	ofxGuiGroup		gui;
	ofxLabel		guiHelp;

	ofxIntSlider	imgThreshold;
	ofxIntSlider	minArea;
	ofxIntSlider	maxArea;

	ofxToggle		vMirror;
	ofxToggle		hMirror;
	ofxToggle		debugView;

	ofxLabel		motionStatus;
};
