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
        baseWidth = 0;
        baseHeight = 0;
        hotspot = ofVec2f(0, 0);
        filePath = "";
    }
    ofVec2f pos;
    ofVec2f hotspot;
    float baseWidth, baseHeight;
    string filePath;
    string tag;
    
    bool loadImage(string path) {
        filePath = path;
        tag = removeCharacter(path, " ");
        tag = removeCharacter(tag, ".");
        tag = removeCharacter(tag, "/");
        tag = removeCharacter(tag, "(");
        tag = removeCharacter(tag, ")");
        bool loaded = ofImage::load(path);
        cout<<"w: "<<getWidth()<<endl;
        cout<<"h: "<<getHeight()<<endl;
        baseWidth = getWidth();
        baseHeight = getHeight();
        hotspot = ofVec2f(baseWidth/2, baseHeight/2);
        return loaded;
    }
    void draw() {
        ofImage::draw(0, 0, baseWidth, baseHeight);
        drawCross(hotspot);
        
    }
private:
    void drawCross(ofVec2f p) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawLine(p.x - 10, p.y, p.x + 10, p.y);
        ofDrawLine(p.x, p.y - 10, p.x, p.y + 10);
        ofPopStyle();
    }
    string removeCharacter(string s, string c) {
        vector<string> v = ofSplitString(s, c);
        string s2 = "";
        for(int i = 0; i < v.size(); i++) {
            s2 += v[i];
        }
        return s2;
    }
};

struct LaserVideo : ofVideoPlayer {
public:
    LaserVideo() {
        baseWidth = 0;
        baseHeight = 0;
        hotspot = ofVec2f(0, 0);
        filePath = "";
    }
    ofVec2f(hotspot);
    string filePath;
    string tag;
    float baseWidth, baseHeight;
    
    bool loadVideo(string path) {
        filePath = path;
        tag = removeCharacter(path, " ");
        tag = removeCharacter(tag, ".");
        tag = removeCharacter(tag, "/");
        tag = removeCharacter(tag, "(");
        tag = removeCharacter(tag, ")");
        bool loaded = ofVideoPlayer::load(path);
        baseWidth = getWidth();
        baseHeight = getHeight();
        hotspot = ofVec2f(baseWidth/2, baseHeight/2);
        return loaded;
    }
    
    void draw() {
        ofVideoPlayer::draw(0, 0, baseWidth, baseHeight);
        drawCross(hotspot);
    }
private:
    void drawCross(ofVec2f p) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawLine(p.x - 10, p.y, p.x + 10, p.y);
        ofDrawLine(p.x, p.y - 10, p.x, p.y + 10);
        ofPopStyle();
    }
    string removeCharacter(string s, string c) {
        vector<string> v = ofSplitString(s, c);
        string s2 = "";
        for(int i = 0; i < v.size(); i++) {
            s2 += v[i];
        }
        return s2;
    }
};

#endif /* LaserStructs_hpp */
