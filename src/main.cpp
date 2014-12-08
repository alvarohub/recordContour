// By Alvaro Cassinelli
// This is a simple controller/recorder for the smart laser scanner. mbed should be using the SkinGames code found here:
// http://developer.mbed.org/users/mbedalvaro/code/skinGames_II/

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(WIDTH_SQUARE_WINDOW,WIDTH_SQUARE_WINDOW,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
