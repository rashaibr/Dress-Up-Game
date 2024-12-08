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
    characterBase.load("Untitled_Artwork.png");
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

    //layout setup
    layoutRef.load("layout_main_ref.jpg");
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic if needed
    skinHairBox.SetPos(windowPosPercentX(35.0f), windowPosPercentY(12.0f));
    skinHairBox.SetSize(ofGetWindowWidth() * 0.5f, ofGetWindowHeight() * 0.2f);
}

//--------------------------------------------------------------
void ofApp::draw() {
    // draw layout
    ofPushMatrix();
        //scale background to the height of our window
        ofScale((1.0f / layoutRef.getHeight()) * ofGetWindowHeight());
        ofSetColor(ofColor(255));
        //layoutRef.draw(0.0f, 0.0f);
    ofPopMatrix();
    ofBackground(128);
    ofSetColor(ofColor(255, 0, 0, 128));
    
    //character stand
    ofDrawRectangle(windowPosPercentX(5.0f), windowPosPercentY(75.0f), windowScalePercentX(25.0f, 1.0f), windowScalePercentY(30.0f, 1.0f));
    
    //character box
    ofDrawRectangle(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    
    //sking + hair box
    //ofDrawRectangle(windowPosPercentX(35.0f), windowPosPercentY(12.0f), windowScalePercentX(50.0f, 1.0f), windowScalePercentY(20.0f, 1.0f));
    ofDrawRectangle(skinHairBox.GetPos(), skinHairBox.GetWidth(), skinHairBox.GetHeight());

    //clothing box
    ofDrawRectangle(windowPosPercentX(35.0f), windowPosPercentY(35.0f), windowScalePercentX(50.0f, 1.0f), windowScalePercentY(50.0f, 1.0f));

    //top icons
    ofDrawRectangle(windowPosPercentX(75.0f), windowPosPercentY(1.0f), windowScalePercentY(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));
    ofDrawRectangle(windowPosPercentX(85.0f), windowPosPercentY(1.0f), windowScalePercentY(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));

    //bottom icons
    ofDrawRectangle(windowPosPercentX(85.0f), windowPosPercentY(88.0f), windowScalePercentX(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));

    ofSetColor(ofColor(0, 0, 255, 128));

    //skintone boxes
    for (int i = 0; i < 7; i++)//SkinTones.size(); i++)
    {
        ofDrawRectangle((skinHairBox.GetPosX() + skinHairBox.GetPosX() * 0.4f) + skinHairBox.GetPosX() * 0.15f * i, skinHairBox.GetPosY() + skinHairBox.GetHeight() * 0.2f, skinHairBox.GetHeight() * 0.2f, skinHairBox.GetHeight() * 0.2f);
    }
    //hair boxes
    for (int i = 0; i < 3; i++)//HairLenghts.size(); i++)
    {
        ofDrawRectangle((skinHairBox.GetPosX() + skinHairBox.GetPosX() * 0.4f) + skinHairBox.GetPosX() * 0.35f * i, skinHairBox.GetPosY() + skinHairBox.GetHeight() * 0.6f, skinHairBox.GetHeight() * 0.8f, skinHairBox.GetHeight() * 0.2f);
    }

    /*
    // Draw all clickable images
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        ClickToSelectImages[i].draw();
    }

    // Draw result images if toggled
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        ClickToSelectImages[i].displayResultImage(100, 100);
    }
    */

    //draw the character base
    UIBox characterSnapRegion;//(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    characterSnapRegion.SetPos(windowPosPercentX(10.0f), windowPosPercentY(18.0f));
    characterSnapRegion.SetSize(windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    characterSnapRegion.hitBox.setPosition(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY());
    characterSnapRegion.hitBox.setSize(characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());
    
    ofPushMatrix();
        ofTranslate(characterSnapRegion.hitBox.getCenter());
        ofScale((1.0f / characterBase.getHeight()) * characterSnapRegion.GetHeight());
        //cout << windowScalePercentY(65.0f, characterBase.getHeight()) << '\n';
        ofSetRectMode(OF_RECTMODE_CENTER);
        characterBase.draw(0, 0);//characterBase.getWidth() * 0.20f, characterBase.getHeight() * 0.5f);
        ofSetRectMode(OF_RECTMODE_CORNER);
        //characterBase.draw(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, characterBase.getWidth()), windowScalePercentY(65.0f, characterBase.getHeight()));

    ofPopMatrix();
    
    //draw clothing items
    //  for (size_t i = 0; i < clothingItems.size(); ++i) {

    //    if (itemPositions[i] == characterSnapRegion.hitBox.getCenter() - (clothingItems[i]->getWidth() / 2))
    //    {
    //        ofSetColor(ofColor::black);
    //        cout << "in center" << '\n';
    //        ofPushMatrix();
    //        ofTranslate(characterSnapRegion.hitBox.getCenter());// -(clothingItems[i]->getWidth() / 2));
    //        ofScale((1.0f / clothingItems[i]->getHeight()) * characterSnapRegion.GetHeight() * 0.3f);
    //        ofSetRectMode(OF_RECTMODE_CENTER);
    //        clothingItems[i]->draw(0, 0);//clothingItems[i]->getWidth() * 0.5f, clothingItems[i]->getHeight() * 0.5f);
    //        ofSetRectMode(OF_RECTMODE_CORNER);
    //        ofPopMatrix();
    //    }
    //    
    //    ofPushMatrix();
    //    ofSetColor(ofColor::white);
    //    ofTranslate(itemPositions[i]);
    //    //ofScale((1.0f / clothingItems[i]->getHeight()) * 100);
    //    clothingItems[i]->draw(0, 0);
    //    ofPopMatrix();
    //}
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

        //ofRectangle snapRegion(snapX, snapY, clothingItems[currentItemIndex]->getWidth(), clothingItems[currentItemIndex]->getHeight());
        ofRectangle snapRegion(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));

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

// for layout adjustmetns
// how far into window do you want to go along the x (ex. 10%, 20%, 50%)
float ofApp::windowPosPercentX(float percent)
{
    return (ofGetWindowWidth() * (percent / 100.0f));
}
// how deep do you want to go into y
float ofApp::windowPosPercentY(float percent)
{
    return (ofGetWindowHeight() * (percent / 100.0f));
}
// scaling based on window size
float ofApp::windowScalePercentX(float percent, float originalWidth)
{
    return ((1.0f / originalWidth) * (ofGetWindowWidth() * (percent / 100.0f)));
}
float ofApp::windowScalePercentY(float percent, float originalHeight)
{
    return ((1.0f / originalHeight) * (ofGetWindowHeight() * (percent / 100.0f)));
}
