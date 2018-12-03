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
    
    blend.load("shaders/blend");
    
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
//    videos[videoIndex]->update();
//    if(doMix) {
//        videoScale = calculateScaleForVideoToFitImage(images[imageIndex], videos[videoIndex]);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].drawToBuffer();
    }
    mixers[0].draw();
    
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::saveHotspots() {
    ofxXmlSettings settings;
    for(int i = 0; i < videos.size(); i++) {
        settings.setValue("videos:" + videos[i]->tag + ":hotspot:x", videos[i]->hotspot.x);
        settings.setValue("videos:" + videos[i]->tag + ":hotspot:y", videos[i]->hotspot.y);
    }
    for(int i = 0; i < images.size(); i++) {
        settings.setValue("images:" + images[i]->tag + ":hotspot:x", images[i]->hotspot.x);
        settings.setValue("images:" + images[i]->tag + ":hotspot:y", images[i]->hotspot.y);
    }
    
    settings.saveFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        saveHotspots();
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
