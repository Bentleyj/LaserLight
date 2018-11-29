#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxNestedFileLoader loader;
    vector<string> vidPaths = loader.load("Lasers Films", "mp4");
    for(int i = 0; i < vidPaths.size(); i++) {
        LaserVideo* vid = new LaserVideo();
        vid->loadVideo(vidPaths[i]);
        videos.push_back(vid);
    }
    loader.clearPaths();
    vector<string> imgPaths = loader.load("LAZERS Pics B_W", "jpg");
    for(int i = 0; i < imgPaths.size(); i++) {
        LaserImage* img = new LaserImage();
        img->loadImage(imgPaths[i]);
        images.push_back(img);
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Controls", settingsPath);
    gui.add(imageOffset.set("Image Offset", ofVec2f(0, 0), ofVec2f(-ofGetWidth()*2, -ofGetHeight()*2), ofVec2f(ofGetWidth()*2, ofGetHeight()*2)));
    gui.add(imageIndex.set("Image Index", 0, 0, images.size() - 1));
    gui.add(videoIndex.set("Video Index", 0, 0, videos.size() - 1));
    gui.add(scale.set("Scale", 1, 0, 3));
    gui.add(videoScale.set("Vid Scale", 1, 0, 100));

    gui.loadFromFile(settingsPath);
    
    imageIndex.addListener(this, &ofApp::onImageChanged);
    videoIndex.addListener(this, &ofApp::onVideoChanged);
    imageOffset.addListener(this, &ofApp::onImageOffsetChanged);
    
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
    
    videos[videoIndex]->play();
}

//--------------------------------------------------------------
void ofApp::update(){
    videos[videoIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofPushMatrix();
//    ofScale(scale, scale);
//    ofTranslate(0, 0);
//    images[imageIndex]->draw();
//    ofTranslate(images[imageIndex]->getWidth(), 0);
//    videos[videoIndex]->draw();
//    ofPopMatrix();
    
    ofPushMatrix();
    ofSetColor(255, 127);
    ofScale(scale, scale);
    images[imageIndex]->draw();
    ofVec2f diff = images[imageIndex]->hotspot - videos[videoIndex]->hotspot;
    ofTranslate(diff);
    ofTranslate(videos[videoIndex]->hotspot);
    ofScale(videoScale, videoScale);
    ofTranslate(-1 * videos[videoIndex]->hotspot);
    videos[videoIndex]->draw();
    ofPopMatrix();
//    if(doMix) {
//        blend.begin();
//        blend.setUniformTexture("imgTex", images[imageIndex]->getTexture(), 0);
//        blend.setUniformTexture("vidTex", videos[videoIndex]->getTexture(), 1);
//        blend.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
//        blend.setUniform1f("imgScale", imgScale);
//        blend.setUniform1f("vidScale", vidScale);
//        blend.setUniform2f("imgOffset", imageOffset.get().x, imageOffset.get().y);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//        blend.end();
//    } else {
//        if(showImg) {
//            ofPushMatrix();
//            ofScale(imgScale, imgScale);
//            images[imageIndex]->draw();
//            ofPopMatrix();
//        } else {
//            ofPushMatrix();
//            ofScale(vidScale, vidScale);
//            videos[videoIndex]->draw();
//            ofPopMatrix();
//        }
//    }
    
    ofSetColor(255);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onImageChanged(int & index) {

}

//--------------------------------------------------------------
void ofApp::onVideoChanged(int & index) {
    for(int i = 0; i < videos.size(); i++) {
        videos[i]->stop();
    }
    videos[index]->play();
}

//--------------------------------------------------------------
void ofApp::onImageOffsetChanged(ofVec2f & offset) {
    images[imageIndex]->pos = offset;
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
    ofVec2f p = ofVec2f(x, y);
    if(p.x > 0 && p.x < images[imageIndex]->baseWidth * scale) {
        if(p.y > 0 && p.y < images[imageIndex]->baseHeight * scale) {
            images[imageIndex]->hotspot = p / (scale);
        }
    }
    
    if(p.x > images[imageIndex]->baseWidth * scale && p.x < images[imageIndex]->baseWidth * scale + videos[videoIndex]->baseWidth * scale) {
        if(p.y > 0 && p.y < videos[videoIndex]->baseHeight * scale) {
            videos[videoIndex]->hotspot = p / (scale);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofVec2f p = ofVec2f(x, y);
    if(p.x > 0 && p.x < images[imageIndex]->baseWidth * scale) {
        if(p.y > 0 && p.y < images[imageIndex]->baseHeight * scale) {
            images[imageIndex]->hotspot = p / (scale);
        }
    }
    
    if(p.x > images[imageIndex]->baseWidth * scale && p.x < images[imageIndex]->baseWidth * scale + videos[videoIndex]->baseWidth * scale) {
        if(p.y > 0 && p.y <  videos[videoIndex]->baseHeight * scale) {
            videos[videoIndex]->hotspot = (p - ofVec2f(images[imageIndex]->baseWidth * scale, 0)) / scale;
        }
    }
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
