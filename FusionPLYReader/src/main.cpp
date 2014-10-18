#include "ofApp.h"

//--------------------------------------------------------------
int main(){

	//ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
	//ofSetCurrentRenderer(renderer, false);

	ofSetupOpenGL(1224, 768, OF_WINDOW);
	ofRunApp(new ofApp()); // start the app
}
