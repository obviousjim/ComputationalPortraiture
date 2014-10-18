#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

	
	ofBackground(22);


}

//--------------------------------------------------------------
void ofApp::update(){
	if(mesh.getNumVertices() > 0){
		cam.setTarget( mesh.getCentroid() * 1000 );
	}
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

	copyMesh.draw();

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

		copyMesh.clear();

		for(int i = 0; i < mesh.getNumIndices(); i += 3){
			if( (i/3) % 100 == 0){
				ofIndexType indexA = mesh.getIndex(i);
				ofIndexType indexB = mesh.getIndex(i+1);
				ofIndexType indexC = mesh.getIndex(i+2);

				ofVec3f vertA = mesh.getVertex(indexA);  
				ofVec3f vertB = mesh.getVertex(indexB);  
				ofVec3f vertC = mesh.getVertex(indexC);  

				ofVec3f normal = (vertB-vertA).getCrossed(vertC-vertA).normalized();
				normal *= .1;

				copyMesh.addVertex(vertA + normal);
				copyMesh.addVertex(vertB + normal);
				copyMesh.addVertex(vertC + normal);

			}
		}

		copyMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	}
}
