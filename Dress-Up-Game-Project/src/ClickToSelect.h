#pragma once
#include "ofMain.h"

class ClickToSelect {
public:
    ClickToSelect(ofImage _imageToSelect, ofImage _imageResult, float x, float y);

    void draw(); // Draw the clickable image
    bool isMouseInside(float x, float y); // Check if the mouse is inside the hitbox
    void toggleResult(); // Toggle the display state of the result image
    void displayResultImage(float x, float y); // Display the result image if toggled

    bool isClicked = false; // Track whether the result image is toggled on

private:
    ofImage imageToSelect;    // The clickable image
    ofImage imageResult;      // The result image
    ofRectangle hitBox;       // The clickable area
};
