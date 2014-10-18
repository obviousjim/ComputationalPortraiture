#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

	
	ofBackground(22);


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	
	cam.begin();
	ofPushStyle();
	ofPushMatrix();
	//units are in meters which makes the models super small in OF
	ofScale(1000,1000,1000);

	if(ofGetKeyPressed('c')){
		mesh.disableColors();
	}
	else{
		mesh.enableColors();
	}
	if(ofGetKeyPressed('w')){
		ofEnableDepthTest();
		mesh.drawWireframe();
		ofDisableDepthTest();
	}
	else if(ofGetKeyPressed('p')){
		ofEnableBlendMode(OF_BLENDMODE_SCREEN); //make it glow
		mesh.drawVertices();
	}
	else {
		ofEnableDepthTest();
		mesh.draw();
		ofDisableDepthTest();
	}

	ofPopMatrix();
	ofPopStyle();
	cam.end();

}

//--------------------------------------------------------------
void ofApp::exit()
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
	if( ofToLower( ofFilePath::getFileExt(dragInfo.files[0]) ) == "ply" ){
		cout << "loading mesh " << dragInfo.files[0] << endl;
		mesh.load( dragInfo.files[0] );
		cam.setTarget( mesh.getCentroid() );
	}
}
