#include "ClickToSelect.h"

// Constructor to initialize the images and set the hitbox location
ClickToSelect::ClickToSelect(ofImage _imageToSelect, ofImage _imageResult, float x, float y)
    : imageToSelect(_imageToSelect), imageResult(_imageResult), isClicked(false) {
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
    isClicked = !isClicked;
    ofLogNotice() << "Image toggled. New state: " << isClicked;
}

// Display the result image only if toggled on
void ClickToSelect::displayResultImage(float x, float y) {
    if (isClicked) {
        imageResult.draw(x, y);
    }
}

// Check if the object is toggled on
bool ClickToSelect::isToggled() const {
    return isClicked;
}

// Disable the toggling
void ClickToSelect::disable() {
    isClicked = false;
}

// Set the position of the object
void ClickToSelect::setPos(float x, float y)
{
    hitBox.x = x;
    hitBox.y = y;
}