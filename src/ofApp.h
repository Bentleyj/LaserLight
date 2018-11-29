#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "LaserStructs.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void onImageChanged(int & index);
    void onVideoChanged(int & index);
    void onImageOffsetChanged(ofVec2f & offset);
    void saveHotspots();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<LaserImage*> images;
    vector<LaserVideo*> videos;
    
    ofParameter<float> scale;
    ofParameter<float> videoScale;

    ofxPanel gui;
    
    ofShader blend;
    
    ofParameter<ofVec2f> imageOffset;
    ofParameter<int> imageIndex;
    ofParameter<int> videoIndex;
};
