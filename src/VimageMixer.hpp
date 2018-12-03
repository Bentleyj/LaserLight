//
//  VimageMixer.hpp
//  LaserLight
//
//  Created by cafe on 03/12/2018.
//

#ifndef VimageMixer_hpp
#define VimageMixer_hpp

#include "ofMain.h"
#include "LaserStructs.hpp"
#include "ofxGui.h"

class VimageMixer {
public:
    VimageMixer() {};
    
    float calculateScaleForVideoToFitImage(LaserImage* img, LaserVideo* vid);
    void drawBuffer();
    void drawToBuffer();
    void drawGui();
    void setup();
    void draw();
    void update();
    
    void onImageChanged(int & index);
    void onVideoChanged(int & index);
    void onImageOffsetChanged(ofVec2f & offset);
    
    vector<LaserImage*>* images;
    vector<LaserVideo*>* videos;
    
    ofxPanel gui;
    
    ofParameter<float> scale;
    ofParameter<float> videoScale;
    ofParameter<bool> doMix;
    ofParameter<ofVec2f> imageOffset;
    ofParameter<int> imageIndex;
    ofParameter<int> videoIndex;
    
    ofFbo buffer;
    
    ofShader* blend;
    
    float novelty;

private:
};

#endif /* VimageMixer_hpp */
