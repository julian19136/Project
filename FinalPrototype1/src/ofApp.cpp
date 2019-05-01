#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    juliaShader.load("julia");
    
    move = 4;
    
    // Set capture dimensions of 320x240, a common video size.
    w = 640;
    h = 400;
    
    // Open an ofVideoGrabber for the default camera
    videoGrabber.initGrabber (w,h);
    
    outImage = new unsigned char [w * h * 3];
    
    Texture.allocate(w, h, GL_RGB);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    videoGrabber.update();
    
    if (videoGrabber.isFrameNew()){
        unsigned char *input = videoGrabber.getPixels().getData();
        //Looping through them
        for (int y = 0; y <h; y ++) {
            for (int x = 0; x <w; x ++) {
                //Input pixel (x, y):
                int r = input [6 * (x + w * (y*2)) + 0];
                int g = input [6 * (x + w * (y*2)) + 1];
                int b = input [6 * (x + w * (y*2)) + 2];
                //Threshold via Blue
                int result = (r> b + 100 && r > g + 100)? 255: 0;
                //Write output image will be black or white:
                outImage[3 * (x + w * y) + 0] = result;
                outImage[3 * (x + w * y) + 1] = result;
                outImage[3 * (x + w * y) + 2] = result;}}
        //Write to a texture for the subsequent withdrawal of its on-screen
        Texture.loadData(outImage, w, h, GL_RGB);
    };
    
    pos = ofPoint(0, 0);
    int n = 0; //Number of pixels found
    for (int y = 0; y <h; y ++) {
        for (int x = 0; x <w; x ++) {
            int r = outImage[3 * (x + w * y) + 2]; //Look processed image
            if (r == 255) { //We have previously labeled as blue dots
                pos.x += x; pos.y += y;n ++;}}}//Display average
    if (n> 0) {pos.x/= n;pos.y/= n;}
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    videoGrabber.draw(0,0, w, h); //Output frame
    
    Texture.draw(0, 0, w*2, h*2);  //Output the processing result
    
    juliaShader.begin();
    juliaShader.setUniform2f("mousePos", vec2(pos.x, pos.y));
    juliaShader.setUniform2f("windowSize", vec2(ofGetWidth(), ofGetHeight()));
    juliaShader.setUniform1f("complexRange", move);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    juliaShader.end();
    
    
   

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'a'){
        move += 0.5; // do something
    } else if (key == 's'){
        move -= 0.5; // do something else
    }

}
