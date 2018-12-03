#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "LaserStructs.hpp"
#include "VimageMixer.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
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
        vector<VimageMixer> mixers;
    
        ofShader blend;
};
