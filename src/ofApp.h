#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "LaserStructs.hpp"
#include "VimageMixer.hpp"
#include "ofxAubio.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void setRandomSettings(VimageMixer* mixer);

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
        void exit();
    
        void audioIn(float * input, int bufferSize, int nChannels);
    
        vector<LaserImage*> images;
        vector<LaserVideo*> videos;
        vector<VimageMixer> mixers;
    
        float lastSwapTime;
        int fadeTarget = 0;
        
        ofxPanel gui;
        ofParameter<float> fade;
        ofParameter<float> imageDuration;
        ofParameter<float> fadeSpeed;
        ofParameter<float> onsetNovelty;
        ofParameter<float> maxOnset;
    
        float lastJumpTime;
        ofParameter<float> jumpCooldown;
    
        bool showGui;
        
        ofShader blend;
        ofShader fadeShader;
    
        ofxAubioOnset onset;
};
