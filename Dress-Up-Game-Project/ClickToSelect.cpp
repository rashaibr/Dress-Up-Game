#include "ClickToSelect.h"

// Constructor: Initialize images and hitbox
ClickToSelect::ClickToSelect(ofImage _imageToSelect, ofImage _imageResult, float x, float y)
    : imageToSelect(_imageToSelect), imageResult(_imageResult) {
    hitBox.set(x, y, imageToSelect.getWidth(), imageToSelect.getHeight());
}

// Draw the clickable image
void ClickToSelect::draw() {
    imageToSelect.draw(hitBox.x, hitBox.y);
}

// Check if the mouse is inside the hitbox
bool ClickToSelect::isMouseInside(float x, float y) {
    return hitBox.inside(x, y);
}

// Toggle the display state of the result image
void ClickToSelect::toggleResult() {
    isClicked = !isClicked; // Toggle the state
}

// Display the result image if toggled on
void ClickToSelect::displayResultImage(float x, float y) {
    if (isClicked) {
        imageResult.draw(x, y);
    }
}
