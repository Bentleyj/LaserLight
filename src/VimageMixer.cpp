//
//  VimageMixer.cpp
//  LaserLight
//
//  Created by cafe on 03/12/2018.
//

#include "VimageMixer.hpp"

//--------------------------------------------------------------
void VimageMixer::setup() {
    if(images != nullptr && videos != nullptr) {
        gui.setup("Controls");
        gui.add(imageOffset.set("Image Offset", ofVec2f(0, 0), ofVec2f(-ofGetWidth()*2, -ofGetHeight()*2), ofVec2f(ofGetWidth()*2, ofGetHeight()*2)));
        gui.add(imageIndex.set("Image Index", 0, 0, images->size() - 1));
        gui.add(videoIndex.set("Video Index", 0, 0, videos->size() - 1));
        gui.add(scale.set("Scale", 1, 0, 3));
        gui.add(videoScale.set("Vid Scale", 1, 0, 100));
        gui.add(doMix.set("Mix", false));
        
        imageIndex.addListener(this, &VimageMixer::onImageChanged);
        videoIndex.addListener(this, &VimageMixer::onVideoChanged);
        imageOffset.addListener(this, &VimageMixer::onImageOffsetChanged);
        
        buffer.allocate(ofGetWidth(), ofGetHeight());
        
        (*videos)[videoIndex]->play();
    } else {
        cout<< "Cannot setup VimageMixer without Assigning image and video Pointers First!"<<endl;
    }
}

//--------------------------------------------------------------
void VimageMixer::update() {
    videoScale = calculateScaleForVideoToFitImage((*images)[imageIndex], (*videos)[videoIndex]);
    (*videos)[videoIndex]->update();
}

//--------------------------------------------------------------
void VimageMixer::draw() {
    drawBuffer();
    drawGui();
}

//--------------------------------------------------------------
void VimageMixer::drawBuffer() {
    buffer.draw(0, 0);
}

//--------------------------------------------------------------
void VimageMixer::drawGui() {
    gui.draw();
}

//--------------------------------------------------------------
void VimageMixer::drawToBuffer() {
    buffer.begin();
    blend->begin();
    blend->setUniformTexture("imgTex", (*images)[imageIndex]->getTexture(), 0);
    blend->setUniformTexture("vidTex", (*videos)[videoIndex]->getTexture(), 1);
    blend->setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    blend->setUniform2f("imgSize", (*images)[imageIndex]->getWidth(), (*images)[imageIndex]->getHeight());
    blend->setUniform2f("vidSize", (*videos)[videoIndex]->getWidth(), (*videos)[videoIndex]->getHeight());
    blend->setUniform2f("imgHotspot", (*images)[imageIndex]->hotspot.x, (*images)[imageIndex]->hotspot.y);
    blend->setUniform2f("vidHotspot", (*videos)[videoIndex]->hotspot.x, (*videos)[videoIndex]->hotspot.y);
    blend->setUniform1f("vidScale", videoScale);
    blend->setUniform1f("scale", scale);
    blend->setUniform2f("imageOffset", imageOffset.get().x, imageOffset.get().y);
    blend->setUniform1f("novelty", novelty);
    ofDrawRectangle(0, 0, ofGetWidth() / scale, ofGetHeight() / scale);
    blend->end();
    buffer.end();
}

//--------------------------------------------------------------
void VimageMixer::onImageChanged(int & index) {
    
}

//--------------------------------------------------------------
void VimageMixer::onVideoChanged(int & index) {
//    (*videos)[index]->play();
}

//--------------------------------------------------------------
void VimageMixer::onImageOffsetChanged(ofVec2f & offset) {
    (*images)[imageIndex]->pos = offset;
}

//--------------------------------------------------------------
float VimageMixer::calculateScaleForVideoToFitImage(LaserImage* img, LaserVideo* vid) {
    // We assume that img is larger than vid
    // First we identify the biggest difference between top, bottom, left and right.
    float rightI = img->baseWidth - img->hotspot.x;
    float leftI = img->hotspot.x;
    float topI = img->hotspot.y;
    float bottomI = img->baseHeight - img->hotspot.y;
    
    float rightV = vid->baseWidth - vid->hotspot.x;
    float leftV = vid->hotspot.x;
    float topV = vid->hotspot.y;
    float bottomV = vid->baseHeight - vid->hotspot.y;
    
    vector<float> diffSizes;
    float rightD = rightI / rightV;
    float leftD = leftI / leftV;
    float topD = topI / topV;
    float bottomD = bottomI / bottomV;
    diffSizes.push_back(rightD);
    diffSizes.push_back(leftD);
    diffSizes.push_back(topD);
    diffSizes.push_back(bottomD);
    
    sort(diffSizes.begin(), diffSizes.end());
    
    
    float scale = diffSizes[3];

    return scale;
}
