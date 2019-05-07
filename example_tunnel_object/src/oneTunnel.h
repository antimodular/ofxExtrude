//
//  oneTunnel.h
//  example
//
//  Created by Stephan Schulz on 2019-05-07.
//

#ifndef oneTunnel_h
#define oneTunnel_h
#include "ofxExtrude.h"


class oneTunnel{
private:
    
public:
    ofVboMesh meshTunnel;
    
    ofxPanel panel;
    
    ofParameter<glm::vec3> tunnelPos;
    ofParameter<glm::vec3> tunnelDepth;
    ofParameter<float> tunnelDecay;
    
    ofTrueTypeFont verdana;
    
    ofPath leftPath, rightPath;
    
    ofxExtrude extrude_object;
    vector<ofVec3f> points;
    
    float myTimer;
    
    void setup(){
        // setups parameters
        ofParameterGroup starGroup("tunnel");
        starGroup.add(tunnelPos.set("tunnel_pos", glm::vec3(100, 0, 0), glm::vec3(-500.), glm::vec3(500.)));
        starGroup.add(tunnelDepth.set("tunnel_depth", glm::vec3(0, 0, 100), glm::vec3(-300), glm::vec3(300)));
        starGroup.add(tunnelDecay.set("tunnel_decay", 1, 0.1, 2));
        
        
        panel.setup();
        panel.add(starGroup);
    }
    
    void update(){
        if(ofGetElapsedTimef() - myTimer > tunnelDecay){
            myTimer = ofGetElapsedTimef();
            if(points.size() > 0){
                points.erase(points.begin());
                updateTunnel();
            }
        }
    }
    
    void draw(){
        ofNoFill();
        leftPath.draw();
        
        ofPushMatrix();
        ofTranslate(tunnelPos.get());
        ofSetColor(128);
        meshTunnel.draw(OF_MESH_FILL);
        ofSetColor(255);
        meshTunnel.draw(OF_MESH_WIREFRAME);
        ofPopMatrix();
        
    }
    
    void drawInfo(){
        
    }
    void addPoint(ofVec3f mousePoint){
              myTimer = ofGetElapsedTimef();
        
        if(points.size() == 0 || points.back().distance(mousePoint) > 2){
            points.push_back(mousePoint);
        }
        
        updateTunnel();
    }
    void updateTunnel(){
        
        leftPath.clear();
        if(points.size() > 0){
            leftPath.moveTo(points[0]);
            
            //code taken from cameraRibbonExample
            for(unsigned int i = 1; i < points.size(); i++){
                
                //find this point and the next point
                ofVec3f thisPoint = points[i-1];
                ofVec3f nextPoint = points[i];
                
                //get the direction from one to the next.
                //the ribbon should fan out from this direction
                ofVec3f direction = (nextPoint - thisPoint);
                
                //get the distance from one point to the next
                float distance = direction.length();
                
                //get the normalized direction. normalized vectors always have a length of one
                //and are really useful for representing directions as opposed to something with length
                ofVec3f unitDirection = direction.getNormalized();
                
                //find both directions to the left and to the right
                ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
                ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
                
                //use the map function to determine the distance.
                //the longer the distance, the narrower the line.
                //this makes it look a bit like brush strokes
                float thickness = ofMap(distance, 0, 60, 20, 2, true);
                
                //calculate the points to the left and to the right
                //by extending the current point in the direction of left/right by the length
                ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
                ofVec3f rightPoint = thisPoint+toTheRight*thickness;
                
                //add these points to the triangle strip
                //        mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
                //        mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
                
                leftPath.lineTo(leftPoint);
            }
            
            //add point sin reverse and on right side of path
            
            //    for(unsigned int i = 1; i < points.size(); i++){
            for(unsigned int i = points.size()-1; i > 0; i--){
                
                
                //find this point and the next point
                ofVec3f thisPoint = points[i-1];
                ofVec3f nextPoint = points[i];
                
                //get the direction from one to the next.
                //the ribbon should fan out from this direction
                ofVec3f direction = (nextPoint - thisPoint);
                
                //get the distance from one point to the next
                float distance = direction.length();
                
                //get the normalized direction. normalized vectors always have a length of one
                //and are really useful for representing directions as opposed to something with length
                ofVec3f unitDirection = direction.getNormalized();
                
                //find both directions to the left and to the right
                ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
                ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
                
                //use the map function to determine the distance.
                //the longer the distance, the narrower the line.
                //this makes it look a bit like brush strokes
                float thickness = ofMap(distance, 0, 60, 20, 2, true);
                
                //calculate the points to the left and to the right
                //by extending the current point in the direction of left/right by the length
                ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
                ofVec3f rightPoint = thisPoint+toTheRight*thickness;
                
                //add these points to the triangle strip
                //        mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
                //        mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
                
                leftPath.lineTo(rightPoint);
            }
            
            leftPath.close();
            
            meshTunnel = extrude_object.getByStraight(leftPath, tunnelDepth.get());
        }else{
            meshTunnel.clear();
        }
    }
};

#endif /* oneTunnel_h */
