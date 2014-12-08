#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    factorResize=1.0*WIDTH_SQUARE_WINDOW/WIDTH_LASER_WINDOW;
    
    ofBackground(20, 80, 20);
    
    
    cout << "listening for osc messages on port " << PORT_REC << "\n";
    receiver.setup(PORT_REC);
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
    standBy=1;
    recordMode=false;
    
    // Start laser projector in contour following, one blob, stand by and sending OSC for position only:
    ofxOscMessage myMessage;
    
    myMessage.setAddress("/spot_following");
    myMessage.addIntArg(1);
    sender.sendMessage(myMessage);
    myMessage.clear();
    
    myMessage.setAddress("/standBy");
    myMessage.addIntArg(standBy);
    sender.sendMessage(myMessage);
    myMessage.clear();
    
    myMessage.setAddress("/sendAnchorPos"); // note: sendAnchorPosp will send the center of the blob; sendPos will send ALL the points of the blob.
    myMessage.addIntArg(1);
    sender.sendMessage(myMessage);
    myMessage.clear();
    
    myMessage.setAddress("/sendOSC");
    myMessage.addIntArg(1);
    sender.sendMessage(myMessage);
    myMessage.clear();
    
    trajectories.clear();
    currentTrajectory.clear();
    
    trajectoryNumber=0;
    logDataFileName="squares"; // we will add the number of the trajectory
    logDataFileEnding=".txt";
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage recMessage;
        receiver.getNextMessage(&recMessage);
        
      //  cout << "message received: address" <<recMessage.getAddress() << endl;
      //  cout << "Args: " << recMessage.getArgAsString(0) << ", " << recMessage.getArgAsString(1) << endl;
        
        //Parse addresses:
        if(recMessage.getAddress() == "/p0"){ // only check on the first blob
            if (recMessage.getNumArgs()==2) {
                // both the arguments are int32's
                newCoordinates.x = (int)recMessage.getArgAsInt32(0)*factorResize;
                newCoordinates.y = (int)recMessage.getArgAsInt32(1)*factorResize;
                
                // Then, save in the current trajectory IF we are in saving mode:
                if (recordMode) currentTrajectory.push_back(newCoordinates);
                
            } // else, it is probably an error
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    ofPolyline curveTrajectory;
    // Draw all the previously acquired trajectories with different alpha channels:
    for (int i=0; i< trajectories.size(); i++) {
        
        ofSetColor(255, 255, 255, 255.0*(i+1)/trajectories.size());
        //ofSetLineWidth(3);
        curveTrajectory.clear();
        // add all the current vertices to cur polyline
        curveTrajectory.addVertices(trajectories[i]);
        curveTrajectory.setClosed(false);
        curveTrajectory.draw();
    }
    // Draw the current trajectory in red:
    curveTrajectory.clear();
    curveTrajectory.addVertices(currentTrajectory);
    curveTrajectory.setClosed(false);
    ofSetColor(255, 0, 0);
    curveTrajectory.draw();
    
    // Draw the current point too, even if it not being recorded:
    ofSetColor(255, 0, 255);
    ofFill();
    ofCircle(newCoordinates.x, newCoordinates.y, 5);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') { // toggle stand by
        standBy=1-standBy;
        ofxOscMessage m;
        m.setAddress("/standBy");
        m.addIntArg(standBy);
        sender.sendMessage(m);
    }
    
    if (key==OF_KEY_RETURN) { // confirm one contour, save it to a file too:
        trajectories.push_back(currentTrajectory);
        // Save in a file and clear the current trajectory:
        
        string name=logDataFileName+ofToString(trajectoryNumber)+logDataFileEnding;
        saveRecording(name);
        trajectoryNumber++;
        
        recordMode=false;
        currentTrajectory.clear();
    }
    
    if (key==OF_KEY_BACKSPACE) { // delete de current trajectory without saving:
      
        recordMode=false;
        currentTrajectory.clear();
    }
    
    if ((key=='r')||(key=='R')) recordMode=true;
    if ((key=='s')||(key=='S')) recordMode=false;
}


void ofApp::saveRecording(string namefile) {
    if(logDataFile.open(ofToDataPath(namefile), ofFile::WriteOnly, false)) {
        logDataFile.create();
        // Save data:
        // 1) Header:
        logDataFile << "Values between 0 and 4096"<< "\n";
        logDataFile << "Number of pairs: " << currentTrajectory.size() << "\n";
        
        // 2) Trajectory data:
        for (int i=0; i<currentTrajectory.size(); i++) {
            
            logDataFile << currentTrajectory[i].x <<"\t"<< currentTrajectory[i].y << "\t";
            logDataFile << "\n";
        }
        cout << "Data saved into " << logDataFile.path() << " file." << endl;
        logDataFile.close();
    } else {
        cout << "Could not open the file "<< namefile << " to save data!" << endl;
        ofLogError("The file " + namefile + " cannot be opened!");
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
