#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "oneTunnel.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
  void keyReleased(int key);
        void mouseDragged(int x, int y, int button);
    
    oneTunnel tunnel_object;
private:	
    //if usecamera is true, we'll turn on the camera view
    bool usecamera;
	ofEasyCam camera;


 
};
