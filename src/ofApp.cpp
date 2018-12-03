#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxNestedFileLoader loader;
    vector<string> vidPaths = loader.load("Videos", "mov");
    for(int i = 0; i < vidPaths.size(); i++) {
        LaserVideo* vid = new LaserVideo();
        vid->loadVideo(vidPaths[i]);
        vid->play();
        videos.push_back(vid);
    }
    loader.clearPaths();
    vector<string> imgPaths = loader.load("Images", "jpg");
    for(int i = 0; i < imgPaths.size(); i++) {
        LaserImage* img = new LaserImage();
        img->loadImage(imgPaths[i]);
        images.push_back(img);
    }
    
    string settingsPath = "settings/masterSettings.xml";
    gui.setup("Controls", settingsPath);
    gui.add(fade.set("Fade", 0, 0, 1));
    gui.add(fadeSpeed.set("Fade Speed", 0.1, 0.0, 1.0));
    gui.add(imageDuration.set("Image Duration", 5.0, 1.0, 30.0));
    gui.add(maxOnset.set("Max Onset", 5000, 0.0, 10000));
    gui.add(onsetNovelty.set("Onset Novelty", 0, 0, maxOnset));
    gui.add(jumpCooldown.set("Jump Cooldown", 0, 0, 1.0));
    gui.loadFromFile(settingsPath);
    
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
        setRandomSettings(&(mixers[i]));
    }
    
    onset.setup();
    
    int nOutputs = 2;
    int nInputs = 2;
    ofSoundStreamSetup(nOutputs, nInputs, this);
    
    lastSwapTime = ofGetElapsedTimef();
}


//--------------------------------------------------------------
void ofApp::update(){
    onsetNovelty.setMax(maxOnset);
    onsetNovelty = onsetNovelty < onset.novelty ? onset.novelty : ofLerp(onsetNovelty, onset.novelty, 0.1);
    if(onsetNovelty > maxOnset && ofGetElapsedTimef() - lastJumpTime > jumpCooldown) {
        for(int i = 0; i < mixers.size(); i++) {
            mixers[i].videoIndex++;
            mixers[i].videoIndex %= mixers[i].videos->size();
//            int frame = videos[mixers[i].videoIndex]->getCurrentFrame();
//            int maxFrames = videos[mixers[i].videoIndex]->getTotalNumFrames();
//            int step = 20;
//            frame += step;
//            frame %= maxFrames;
//            videos[mixers[i].videoIndex]->setFrame(frame);
        }
        lastJumpTime = ofGetElapsedTimef();
    }
    for(int i = 0; i < mixers.size(); i++) {
        mixers[i].update();
        mixers[i].novelty = ofMap(onsetNovelty, 0, maxOnset, 0, 1, true);
    }
    for(int i = 0; i < videos.size(); i++) {
        videos[i]->update();
    }
    if(ofGetElapsedTimef() - lastSwapTime > imageDuration) {
        fadeTarget = int(fade.get()+1) % 2;
        lastSwapTime = ofGetElapsedTimef();
        if(fade == 0) {
            setRandomSettings(&(mixers[1]));
        } else if(fade == 1.0){
            setRandomSettings(&(mixers[0]));
        }
    }
    fade = ofLerp(fade, fadeTarget, fadeSpeed);
    if(abs(fade - fadeTarget) < 0.01) {
        fade = fadeTarget;
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
    
    if(showGui) {
        for(int i = 0; i < mixers.size(); i++) {
            mixers[i].drawGui();
        }
        gui.draw();
    }

    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::setRandomSettings(VimageMixer* mixer) {
    mixer->imageIndex = ofRandom(0, mixer->images->size());
    mixer->videoIndex = ofRandom(0, mixer->videos->size());
    ofImage* img = (*mixer->images)[mixer->imageIndex];
    mixer->scale = ofRandom(0.1, 0.2);
    
    ofVec2f offset = ofVec2f(ofRandom(100, ofGetWidth() - img->getWidth() * mixer->scale - 100), ofRandom(100, ofGetHeight() - img->getHeight() * mixer->scale));
    mixer->imageOffset.set(offset);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') {
        showGui = !showGui;
    }
    if(key == ' ') {
        if(fade == 0) {
            setRandomSettings(&(mixers[1]));
        } else if(fade == 1.0){
            setRandomSettings(&(mixers[0]));
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // compute onset detection
     onset.audioIn(input, bufferSize, nChannels);
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
