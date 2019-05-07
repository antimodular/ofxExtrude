#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
        
  
    
    tunnel_object.setup();
    
    ofBackground(64);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    tunnel_object.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    
    
    if(usecamera){
        camera.begin();
    }    
    tunnel_object.draw();
    if(usecamera){
        camera.end();
    }
    
            ofDisableDepthTest();
    
      tunnel_object.panel.draw();
    
    ofDrawBitmapString("key c to change camera", 300, 10);
    ofDrawBitmapString("key x to clear tunnel shape", 300, 30);
    ofDrawBitmapString("only change tunnel depth z", 300, 50);

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}
void ofApp::keyReleased(int key){
    if(key == 'c'){
        usecamera = !usecamera;
    }
    if(key == 'x'){
        tunnel_object.points.clear();
    }
}
void ofApp::mouseDragged(int x, int y, int button){
    //if we are using the camera, the mouse moving should rotate it around the whole sculpture
    
    if(usecamera == false){
        
        ofVec3f mousePoint(x,y,0);
        tunnel_object.addPoint(mousePoint);
       
        
    }
}

