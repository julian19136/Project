#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    juliaShader.load("julia");
    
    move = 4;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    juliaShader.begin();
    juliaShader.setUniform2f("mousePos", vec2(ofGetMouseX(), ofGetMouseY()));
    juliaShader.setUniform2f("windowSize", vec2(ofGetWidth(), ofGetHeight()));
    juliaShader.setUniform1f("complexRange", move);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    juliaShader.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'a'){
        move += 0.1; // do something
    } else if (key == 's'){
        move -= 0.1; // do something else
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
