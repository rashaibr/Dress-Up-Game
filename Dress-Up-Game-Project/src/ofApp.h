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

    //variables for the character and items

    ofImage characterBase;
    ofImage clothingItem1;
    ofImage clothingItem2;
    ofImage clothingItem3;
    ofImage clothingItem4;
    ofImage clothingItem5;

    //position of the draggable item
    float itemX1, itemY1;
    float itemX2, itemY2;
    float itemX3, itemY3;
    float itemX4, itemY4;
    float itemX5, itemY5;

    //list of clothing items
    vector<ofImage*> clothingItems;

    //Positions of each clothing item
    vector<ofVec2f> itemPositions;

    //The index of the clothing item being dragged
    int currentItemIndex;


    //wether the item is being dragged
    bool isDragging;
};
