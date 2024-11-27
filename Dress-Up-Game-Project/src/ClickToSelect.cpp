#include "ClickToSelect.h"

// Constructor to initialize the images and set the hitbox location
ClickToSelect::ClickToSelect(ofImage _imageToSelect, ofImage _imageResult, float x, float y) {
    imageToSelect = _imageToSelect;
    imageResult = _imageResult;
    hitBox.set(x, y, imageToSelect.getWidth(), imageToSelect.getHeight());
}

// Draw the image and the result image if needed
void ClickToSelect::draw() {
    imageToSelect.draw(hitBox.x, hitBox.y);
    ofSetColor(255, 0, 0, 100); // Semi-transparent red
    ofDrawRectangle(hitBox);
    ofSetColor(255); // Reset color to white
}

// Check if the mouse is inside the hitbox
bool ClickToSelect::isMouseInside(float x, float y) {
    return hitBox.inside(x, y);
}

// Display the result image at the specified position
void ClickToSelect::displayResultImage(float x, float y) {
    imageResult.draw(x, y);
    ofLogNotice() << "Displaying result image at: " << x << ", " << y;
    imageResult.draw(x, y);
}