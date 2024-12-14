#pragma once
#include "ofMain.h"
#include "ClickToSelect.h"
#include "Headers.h"
#include "ofxGui.h"


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

// <<<<<<< HEAD
//     vector<ClickToSelect> ClickToSelectImages; // Store all interactive images
//     vector<ClickToSelect> SkinTones;//store the skin tones 
//     vector<ofImage> HairButtons;
// =======
    vector<ClickToSelect> Hairstyles;
    vector<ClickToSelect> Accessories;
    vector<ClickToSelect> Backgrounds;

    ofImage blond;
    ofImage blondButton;
    ofImage red;
    ofImage redButton;
    ofImage brown;
    ofImage brownButton;

    ofImage gold;
    ofImage goldButton;
    ofImage silver;
    ofImage silverButton;
    ofImage white;
    ofImage whiteButton;

    ofImage bg1;
    ofImage bg1Button;
    ofImage bg2;
    ofImage bg2Button;
    ofImage bg3;
    ofImage bg3Button;
    ofImage bg4;
    ofImage bg4Button;

    void handleGroupClick(vector<ClickToSelect> &group, int x, int y);
//>>>>>>> main

    //layout data
    ofImage layoutRef;
    float windowPosPercentX(float percent);
    float windowPosPercentY(float percent);
    float windowScalePercentX(float percent, float originalWidth);
    float windowScalePercentY(float percent, float originalHeight);

    UIBox skinHairBox;
    UIBox clothesBox;
    UIBox topClothesBox;
    UIBox bottomClothesBox;
    UIBox characterSnapRegion;
    
    ofImage restartImage;
    UIBox restartBox;

    //variables for the character and items

    ofImage characterBase;
    ofImage pinkShirt;
    ofImage pinkShoes;
    ofImage purpleDress;
    ofImage purpleShoes;
    ofImage redDress;
    ofImage jeans;
    ofImage greenShirt;
    ofImage shorts;
  

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

    // Declare a boolean to track if the menu is open
    bool isMenuOpen;

    // Declare the button position and size
    ofRectangle menuButton;
    ofRectangle resumeButton;
    ofRectangle creditsButton;
    ofRectangle quitButton;

    // Declare the new window size and position
    ofRectangle newWindow;

    bool isCreditsOpen;           // Tracks if the credits window is open
    ofRectangle creditsWindow;    // Rectangle for the credits popup
    ofRectangle closeButton;      // Close button inside the credits popup


};
