//
//  LaserStructs.hpp
//  LaserLight
//
//  Created by James Bentley on 11/6/18.
//

#ifndef LaserStructs_hpp
#define LaserStructs_hpp

#include "ofMain.h"

struct LaserImage : ofImage {
public:
    LaserImage() {
        baseWidth = drawWidth = 0;
        baseHeight = drawHeight = 0;
        pos = ofVec2f(0, 0);
        filePath = "";
    }
    ofVec2f pos;
    float baseWidth, baseHeight;
    float drawWidth, drawHeight;
    
    string filePath;
    bool loadImage(string path) {
        filePath = path;
        bool loaded = ofImage::load(path);
        baseWidth = getWidth();
        baseHeight = getHeight();
        drawWidth = baseWidth;
        drawHeight = baseHeight;
        return loaded;
    }
    void draw() {
        ofImage::draw(pos.x, pos.y, drawWidth, drawHeight);
    }
private:
};

struct LaserVideo : ofVideoPlayer {
public:
    LaserVideo() {
        baseWidth = drawWidth = 0;
        baseHeight = drawHeight = 0;
        pos = ofVec2f(0, 0);
        filePath = "";
    }
    ofVec2f pos;
    string filePath;
    float baseWidth, baseHeight;
    float drawWidth, drawHeight;
    bool loadVideo(string path) {
        filePath = path;
        bool loaded = ofVideoPlayer::load(path);
        baseWidth = getWidth();
        baseHeight = getHeight();
        drawWidth = baseWidth;
        drawHeight = baseHeight;
        return loaded;
    }
    void draw() {
        ofVideoPlayer::draw(pos.x, pos.y, drawWidth, drawHeight);
    }
private:
};

#endif /* LaserStructs_hpp */
