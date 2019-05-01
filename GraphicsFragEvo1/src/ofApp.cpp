#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    juliaShader.load("julia");
    
    move = 4;
    
    plane.mapTexCoordsFromTexture(img.getTextureReference());
    
    camera.setPosition(vec3(0.0f, 0.0f, 0.0f));
    camera.setTarget(vec3(ofGetWidth()/2, ofGetHeight()/2, 0.0f));
    //camera.setFov(35.0f);
    //camera.setAutoDistance(false);
    
    createPedestalMesh(pedestalMesh, 60, 60);
    ofEnableNormalizedTexCoords();
    
    keyLight.setDiffuseColor(ofFloatColor(0.0f, 0.0f, 1.0f));
    keyLight.setSpecularColor(keyLight.getDiffuseColor());
    keyLight.setPosition(vec3(120.0f, 100.0f, 120.0f));
    keyLight.setSpotlight(45.f, 0.f);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    camera.begin();
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    keyLight.enable();
    
    img.getTextureReference().bind();
    
    juliaShader.begin();
    juliaShader.setUniform2f("mousePos", vec2(ofGetMouseX(), ofGetMouseY()));
    juliaShader.setUniform2f("windowSize", vec2(ofGetWidth(), ofGetHeight()));
    juliaShader.setUniform1f("complexRange", move);
    pedestalMesh.draw();
    //ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    //ofDrawIcoSphere(ofGetWidth()/2, ofGetHeight()/2, 200);
    //ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    juliaShader.end();
    
    img.getTextureReference().unbind();

    camera.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    
}


void ofApp::addQuadFacet(ofMesh &curMesh, vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec2 tMin, vec2 tMax) {
    // Adds a quadrilateral facet based on positions of the 4 vertex positions and min and max
    // values for the texture coordinates. Automatically calculates the normal based on a CCW winding
    // order for the vertex positions.
    
    int baseIndex = curMesh.getNumVertices();
    
    curMesh.addVertex(v0);
    curMesh.addVertex(v1);
    curMesh.addVertex(v2);
    curMesh.addVertex(v3);
    
    vec3 n = normalize(cross(v1 - v0, v3 - v0));
    curMesh.addNormal(n);
    curMesh.addNormal(n);
    curMesh.addNormal(n);
    curMesh.addNormal(n);
    
    curMesh.addTexCoord(vec2(tMin.x, tMin.y));
    curMesh.addTexCoord(vec2(tMax.x, tMin.y));
    curMesh.addTexCoord(vec2(tMax.x, tMax.y));
    curMesh.addTexCoord(vec2(tMin.x, tMax.y));
    
    curMesh.addTriangle(baseIndex, baseIndex + 1, baseIndex + 2);
    curMesh.addTriangle(baseIndex, baseIndex + 2, baseIndex + 3);
}

void ofApp::createPedestalMesh(ofVboMesh &curMesh, float width, float height) {
    curMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    // Pedestal width and height values
    const float w = 0.9f * width;
    const float h = height;
    
    // Facets for the 4 sides
    addQuadFacet(curMesh, vec3(-w, 0, w), vec3(w, 0, w), vec3(w, h, w), vec3(-w, h, w), vec2(0.0f, 0.0f), vec2(0.25f, 1.0f));
    addQuadFacet(curMesh, vec3(w, 0, -w), vec3(-w, 0, -w), vec3(-w, h, -w), vec3(w, h, -w), vec2(0.5f, 0.0f), vec2(0.75f, 1.0f));
    //addQuadFacet(curMesh, vec3(-w, 0, -w), vec3(-w, 0, w), vec3(-w, h, w), vec3(-w, h, -w), vec2(0.75f, 0.0f), vec2(1.0f, 1.0f));
     //addQuadFacet(curMesh, vec3(w, 0, w), vec3(w, 0, -w), vec3(w, h, -w), vec3(w, h, w), vec2(0.25f, 0.0f), vec2(0.5f, 1.0f));
    
    // Facet for the top
    //addQuadFacet(curMesh, vec3(-w, h, w), vec3(w, h, w), vec3(w, h, -w), vec3(-w, h, -w), vec2(0.0f, 0.0f), vec2(0.25f, 0.25f));
}
