#pragma once
#include "ofMain.h"
#include "ClickToSelect.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    vector<ClickToSelect> ClickToSelectImages; // Store all interactive images
    vector<ClickToSelect> SkinTones;//store the skin tones 

    //layout data
    ofImage layoutRef;
    float windowPosPercentX(float percent);
    float windowPosPercentY(float percent);
    float windowScalePercentX(float percent, float originalWidth);
    float windowScalePercentY(float percent, float originalHeight);
};
