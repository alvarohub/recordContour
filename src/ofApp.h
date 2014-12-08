#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// Address mbed:
#define HOST "10.0.0.2"
#define PORT 10000

#define PORT_REC 12000 // mbed sends to here

#define WIDTH_SQUARE_WINDOW 600
#define WIDTH_LASER_WINDOW 4096


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void saveRecording(string);
    
    ofFile logDataFile;
    string logDataFileName, logDataFileEnding;
    int trajectoryNumber;
    
    int standBy;
    bool recordMode;
    ofVec2f newCoordinates;
    float factorResize;
    
    vector< vector<ofPoint> > trajectories;
    vector<ofPoint> currentTrajectory;
    
    ofTrueTypeFont font;
    ofxOscSender sender;
    ofxOscReceiver receiver;

		
};
