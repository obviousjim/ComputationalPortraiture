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

		copyMesh.clear();
		//go through each triangle, stepping indices of 3
		for(int i = 0; i < mesh.getNumIndices(); i += 3){
			//for 1 in 20 triangles create a duplicate and  send it out alone its normal

			//how many to triangles to delete
			int divider = ofMap(ofGetMouseY(), 0, ofGetHeight(), 1, 100, true);

			if( (i/3) % divider == 0){

				//each three consecutive indices define a triangle, lets grab them
				ofIndexType indexA = mesh.getIndex(i);
				ofIndexType indexB = mesh.getIndex(i+1);
				ofIndexType indexC = mesh.getIndex(i+2);

				//...and pull out the vertices they refer to...
				ofVec3f vertA = mesh.getVertex(indexA);  
				ofVec3f vertB = mesh.getVertex(indexB);  
				ofVec3f vertC = mesh.getVertex(indexC); 

				//...and the normal attribute for each one. this points away from the model
				//.. PLYS in OF from Kinect Fusion doesn't seem to load normals, 
				//... let's make one up for each face based on cross products
				ofVec3f normal = -(vertA-vertB).getCrossed(vertC-vertB).normalized();

				//we will move this triangle away from the model in the direction of the normal by scalar amount
				float normalScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.0, 1.0, true); //still very small

				copyMesh.addVertex(vertA + normal * normalScale);
				copyMesh.addVertex(vertB + normal * normalScale);
				copyMesh.addVertex(vertC + normal * normalScale);

			}
		}

		copyMesh.setMode(OF_PRIMITIVE_TRIANGLES);
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
		copyMesh.draw();
		ofDisableDepthTest();
	}

	//copyMesh.draw();

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


	}
}
