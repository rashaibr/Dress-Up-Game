#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    // Set window size and position
    ofSetWindowShape(1280, 720);

    int screenWidth = ofGetScreenWidth();
    int screenHeight = ofGetScreenHeight();

    int windowWidth = 1280; 
    int windowHeight = 720; 

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    
    ofSetWindowPosition(x, y);

    // Set background color
    ofBackground(255); // White background

    //load assets
    characterBase.load("character.png");
    pinkShirt.load("pinkShirt.png");
    pinkShoes.load("pinkShoes.png");
    jeans.load("jeans.png");
    redDress.load("redDress.png");
    purpleDress.load("purpleDress.png");
    greenShirt.load("greenShirt.png");
    shorts.load("shorts.png");
    purpleShoes.load("purpleShoes.png");

    //list of clothing items

    clothingItems.push_back(&pinkShirt);
    clothingItems.push_back(&pinkShoes);
    clothingItems.push_back(&purpleDress);
    clothingItems.push_back(&purpleShoes);
    clothingItems.push_back(&jeans);
    clothingItems.push_back(&redDress);
    clothingItems.push_back(&greenShirt);
    clothingItems.push_back(&shorts);


    int xOffset = 200; // Horizontal offset for positioning
    for (size_t i = 0; i < clothingItems.size(); ++i) {
        itemPositions.push_back(ofVec2f(xOffset, 100));
        xOffset += 200; // Increment position for the next item
    }

    isDragging = false;
    currentItemIndex = -1; // No item is selected initially

    ofImage imageToSelect1, imageResult1;
    imageToSelect1.load("imageToSelect1.jpg");
    imageResult1.load("imageResult1.jpg");

    // Add the interactive image to the vector
    ClickToSelectImages.push_back(ClickToSelect(imageToSelect1, imageResult1, 50, 50));

    ofLogNotice() << "Setup complete. Clickable images initialized.";
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic if needed
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Draw all clickable images
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        ClickToSelectImages[i].draw();
    }

    // Draw result images if toggled
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        ClickToSelectImages[i].displayResultImage(100, 100);
    }

    //draw the character base
    characterBase.draw(400, 200, characterBase.getWidth(), characterBase.getHeight());

    //draw clothing items
    // Draw clothing items
    for (size_t i = 0; i < clothingItems.size(); ++i) {
        clothingItems[i]->draw(itemPositions[i].x, itemPositions[i].y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // Toggle the state of the clicked image
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        if (ClickToSelectImages[i].isMouseInside(x, y)) {
            ClickToSelectImages[i].toggleResult();
        }
    }

    isDragging = false;       // Reset dragging state
    currentItemIndex = -1;    // Reset selected item index

    // Loop through clothing items to check if the mouse click is within their bounds
    for (size_t i = 0; i < clothingItems.size(); i++) {
        // Calculate the item's bounds
        float itemLeft = itemPositions[i].x;
        float itemRight = itemPositions[i].x + clothingItems[i]->getWidth();
        float itemTop = itemPositions[i].y;
        float itemBottom = itemPositions[i].y + clothingItems[i]->getHeight();

        // Check if the click is inside the bounds of the item
        if (x >= itemLeft && x <= itemRight && y >= itemTop && y <= itemBottom) {
            isDragging = true;
            currentItemIndex = i; // Set the index of the clicked item
            return; // Exit the loop as soon as the item is found
        }
    }
}


//--------------------------------------------------------------
// Remaining event methods
void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (isDragging && currentItemIndex != -1) {
        // Drag the selected item to follow the mouse
        itemPositions[currentItemIndex].x = x - clothingItems[currentItemIndex]->getWidth() / 2;
        itemPositions[currentItemIndex].y = y - clothingItems[currentItemIndex]->getHeight() / 2;
    }
}

void ofApp::mouseReleased(int x, int y, int button) {
    isDragging = false;

    if (currentItemIndex >= 0 && currentItemIndex < clothingItems.size()) {
        // Define a snap region for clothing items to align to the character
        float snapX = 600; // Example snap position (center of character)
        float snapY = 300;

        ofRectangle snapRegion(snapX, snapY, characterBase.getWidth(), characterBase.getHeight());

        // Check if the item is released within the snap region
        if (snapRegion.inside(x, y)) {
            // Center the item on the character base
            itemPositions[currentItemIndex].x = snapX + (characterBase.getWidth() - clothingItems[currentItemIndex]->getWidth()) / 2;
            itemPositions[currentItemIndex].y = snapY + (characterBase.getHeight() - clothingItems[currentItemIndex]->getHeight()) / 2;
        }
    }

    currentItemIndex = -1; // Reset the item index after release
}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
