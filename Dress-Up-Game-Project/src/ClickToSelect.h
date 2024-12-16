#pragma once
#include "ofMain.h"

class ClickToSelect {
public:
    ClickToSelect(ofImage _imageToSelect, ofImage _imageResult, float x, float y);

    void draw(); // Draw the image to select
    bool isMouseInside(float x, float y); // Check if the mouse is inside the hitbox
    void toggleResult(); // Toggle the result image's display state
    void displayResultImage(float x, float y); // Conditionally display the result image

    bool isToggled() const;  // New method to check if toggled
    void disable();          // New method to disable

    void setPos(float x, float y); //Set the position of the hitbox
    float getDisplayWidth(); // Get the width of the display image
    float getDisplayHeight(); // Get the height of the display image

private:
    ofImage imageToSelect;    // Initial clickable image
    ofImage imageResult;      // Image to display on toggle
    ofRectangle hitBox;       // Hitbox for mouse interaction
    bool isClicked;           // State to track toggling
};
