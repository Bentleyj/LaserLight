#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxNestedFileLoader loader;
    vector<string> vidPaths = loader.load("Videos", "mov");
    for(int i = 0; i < vidPaths.size(); i++) {
        LaserVideo* vid = new LaserVideo();
        vid->loadVideo(vidPaths[i]);
        videos.push_back(vid);
    }
    loader.clearPaths();
    vector<string> imgPaths = loader.load("Images", "jpg");
    for(int i = 0; i < imgPaths.size(); i++) {
        LaserImage* img = new LaserImage();
        img->loadImage(imgPaths[i]);
        images.push_back(img);
    }
    
    gui.setup("Controls");
    gui.add(fade.set("Fade", 0, 0, 1));
    
    blend.load("shaders/blend");
    fadeShader.load("shaders/fade");
    
    showGui = false;
    
    ofxXmlSettings settings;
    settings.load("settings.xml");
    settings.pushTag("videos");
    for(int i = 0; i < videos.size(); i++) {
        settings.pushTag(videos[i]->tag);
        float x = settings.getValue("hotspot:x", 10);
        float y = settings.getValue("hotspot:y", 10);
        videos[i]->hotspot = ofVec2f(x, y);
        settings.popTag();
    }
    settings.popTag();
    
    settings.pushTag("images");
    for(int i = 0; i < images.size(); i++) {
        settings.pushTag(images[i]->tag);
        float x = settings.getValue("hotspot:x", 10);
        float y = settings.getValue("hotspot:y", 10);
        images[i]->hotspot = ofVec2f(x, y);
        settings.popTag();
    }
    settings.popTag();
    
    mixers.resize(2);
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].images = &images;
        mixers[i].videos = &videos;
        mixers[i].blend = &blend;
        mixers[i].setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].drawToBuffer();
    }
    
    fadeShader.begin();
    fadeShader.setUniformTexture("tex1", mixers[0].buffer.getTexture(), 0);
    fadeShader.setUniformTexture("tex2", mixers[1].buffer.getTexture(), 1);
    fadeShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    fadeShader.setUniform1f("fadeAmount", fade);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    fadeShader.end();
//    mixers[0].draw();
    
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].drawGui();
    }
    gui.draw();
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') {
        showGui = !showGui;
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
//    if(!doMix) {
//        ofVec2f p = ofVec2f(x, y);
//        if(p.x > 0 && p.x < images[imageIndex]->baseWidth * scale) {
//            if(p.y > 0 && p.y < images[imageIndex]->baseHeight * scale) {
//                images[imageIndex]->hotspot = p / (scale);
//            }
//        }
//        if(p.x > images[imageIndex]->baseWidth * scale && p.x < images[imageIndex]->baseWidth * scale + videos[videoIndex]->baseWidth * scale * videoScale) {
//            if(p.y > 0 && p.y < videos[videoIndex]->baseHeight * scale * videoScale) {
//                videos[videoIndex]->hotspot = ofVec2f(p.x - images[imageIndex]->baseWidth * scale, p.y) / (scale * videoScale);
//            }
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    if(!doMix) {
//        ofVec2f p = ofVec2f(x, y);
//        if(p.x > 0 && p.x < images[imageIndex]->baseWidth * scale) {
//            if(p.y > 0 && p.y < images[imageIndex]->baseHeight * scale) {
//                images[imageIndex]->hotspot = p / (scale);
//            }
//        }
//        if(p.x > images[imageIndex]->baseWidth * scale && p.x < images[imageIndex]->baseWidth * scale + videos[videoIndex]->baseWidth * scale * videoScale) {
//            if(p.y > 0 && p.y < videos[videoIndex]->baseHeight * scale * videoScale) {
//                cout<<p<<endl;
//                cout<<p / scale<<endl;
//                videos[videoIndex]->hotspot = ofVec2f(p.x - images[imageIndex]->baseWidth * scale, p.y) / (scale * videoScale);
//            }
//        }
//    }
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
