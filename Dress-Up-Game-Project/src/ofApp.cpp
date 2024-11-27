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
    clothingItem1.load("dress.png");
    clothingItem2.load("dress.png");
    clothingItem3.load("dress.png");
    clothingItem4.load("dress.png");
    clothingItem5.load("dress.png");

    //initial positions
    itemX1 = 200;
    itemY1 = 100;

    itemX2 = 400;
    itemY2 = 100;

    itemX3 = 600;
    itemY3 = 100;

    itemX4 = 800;
    itemY4 = 100;

    itemX5 = 1000;
    itemY5 = 100;

    //list of clothing items

    clothingItems.push_back(&clothingItem1);
    clothingItems.push_back(&clothingItem2);
    clothingItems.push_back(&clothingItem3);
    clothingItems.push_back(&clothingItem4);
    clothingItems.push_back(&clothingItem5);

    itemPositions.push_back(ofVec2f(itemX1, itemY1));
    itemPositions.push_back(ofVec2f(itemX2, itemY2));
    itemPositions.push_back(ofVec2f(itemX3, itemY3));
    itemPositions.push_back(ofVec2f(itemX4, itemY4));
    itemPositions.push_back(ofVec2f(itemX5, itemY5));
    isDragging = false;

    currentItemIndex = -1;  // No item is selected initially

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
    characterBase.draw(0,0, characterBase.getWidth(), characterBase.getHeight());

    //draw clothing items
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

    if (currentItemIndex != -1) {
        // Define a snap region (the area where the clothing item can be placed)
        float snapX = characterBase.getWidth() / 2 - clothingItems[currentItemIndex]->getWidth() / 2; // Center the item horizontally
        float snapY = characterBase.getHeight() / 2 - clothingItems[currentItemIndex]->getHeight() / 2; // Center it vertically

        ofRectangle snapRegion(snapX, snapY, clothingItems[currentItemIndex]->getWidth(), clothingItems[currentItemIndex]->getHeight());

        // Check if the mouse is inside the snap region
        if (snapRegion.inside(x, y)) {
            // Snap the item to the region (center it in the snap area)
            itemPositions[currentItemIndex].x = snapRegion.getCenter().x - clothingItems[currentItemIndex]->getWidth() / 2;
            itemPositions[currentItemIndex].y = snapRegion.getCenter().y - clothingItems[currentItemIndex]->getHeight() / 2;
        }
    }

    currentItemIndex = -1; // Reset the item index after release
}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
