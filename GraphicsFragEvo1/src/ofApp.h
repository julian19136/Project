#pragma once

#include "ofMain.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
        void addQuadFacet(ofMesh &curMesh, vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec2 tMin, vec2 tMax);
        void createPedestalMesh(ofVboMesh &curMesh, float width, float height);

        ofVboMesh pedestalMesh;
        ofShader juliaShader;
        ofEasyCam camera;
        ofNode node;
        ofImage img;
        ofPlanePrimitive plane;
        ofLight keyLight;
    
        float position;
    
        float move;
    
		
};
