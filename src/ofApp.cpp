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
    gui.add(imageOffset.set("Image Offset", ofVec2f(0, 0), ofVec2f(-ofGetWidth(), -ofGetHeight()), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(imageIndex.set("Image Index", 0, 0, images.size() - 1));
    gui.add(videoIndex.set("Video Index", 0, 0, videos.size() - 1));

    gui.loadFromFile(settingsPath);
    
    imageIndex.addListener(this, &ofApp::onImageChanged);
    videoIndex.addListener(this, &ofApp::onVideoChanged);
    imageOffset.addListener(this, &ofApp::onImageOffsetChanged);
    
    blend.load("shaders/blend");
    
    videoIndex = 0;
    imageIndex = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    videos[videoIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    blend.begin();
    blend.setUniformTexture("imgTex", images[imageIndex]->getTexture(), 0);
    blend.setUniformTexture("vidTex", videos[videoIndex]->getTexture(), 1);
    blend.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    blend.setUniform1f("imgScale", imgScale);
    blend.setUniform1f("vidScale", vidScale);
    blend.setUniform2f("imgOffset", imageOffset.get().x, imageOffset.get().y);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    blend.end();
    
    ofSetColor(255);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onImageChanged(int & index) {
    if(images[imageIndex]->baseWidth > images[imageIndex]->baseHeight) {
//        imgScale =  ofGetWidth() / images[imageIndex]->baseWidth;
        images[imageIndex]->drawWidth = images[imageIndex]->baseWidth * imgScale;
        images[imageIndex]->drawHeight = images[imageIndex]->baseHeight * imgScale;
    } else {
//        imgScale =  ofGetHeight() / images[imageIndex]->baseHeight;
        images[imageIndex]->drawWidth = images[imageIndex]->baseWidth * imgScale;
        images[imageIndex]->drawHeight = images[imageIndex]->baseHeight * imgScale;
    }

}

//--------------------------------------------------------------
void ofApp::onVideoChanged(int & index) {
    if(videos[videoIndex]->baseWidth > videos[videoIndex]->baseHeight) {
//        vidScale =  ofGetWidth() / videos[videoIndex]->baseWidth;
        videos[videoIndex]->drawWidth = videos[videoIndex]->baseWidth * vidScale;
        videos[videoIndex]->drawHeight = videos[videoIndex]->baseHeight * vidScale;
    } else {
//        vidScale =  ofGetHeight() / videos[videoIndex]->baseWidth;
        videos[videoIndex]->drawWidth = videos[videoIndex]->baseWidth * vidScale;
        videos[videoIndex]->drawHeight = videos[videoIndex]->baseHeight * vidScale;
    }
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
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
    if(images[imageIndex]->baseWidth > images[imageIndex]->baseHeight) {
        imgScale =  w / images[imageIndex]->baseWidth;
        images[imageIndex]->drawWidth = w;
        images[imageIndex]->drawHeight = images[imageIndex]->baseHeight * imgScale;
    } else {
        imgScale =  h / images[imageIndex]->baseHeight;
        images[imageIndex]->drawWidth = images[imageIndex]->baseWidth * imgScale;
        images[imageIndex]->drawHeight = h;
    }
    
    if(videos[videoIndex]->baseWidth > videos[videoIndex]->baseHeight) {
        vidScale =  w / videos[videoIndex]->baseWidth;
        videos[videoIndex]->drawWidth = w;
        videos[videoIndex]->drawHeight = videos[videoIndex]->baseHeight * vidScale;
    } else {
        vidScale =  h / videos[videoIndex]->baseWidth;
        videos[videoIndex]->drawWidth = videos[videoIndex]->baseWidth * vidScale;
        videos[videoIndex]->drawHeight = h;
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
