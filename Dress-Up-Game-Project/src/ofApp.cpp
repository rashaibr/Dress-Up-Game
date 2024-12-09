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

    // Set up the Main Menu button
    menuButton.set(50, 50, 200, 50); // Position and size of the button

    float windowCenterX = ofGetWidth() / 2; // Horizontal center of the window
    float windowCenterY = ofGetHeight() / 2; // Vertical center of the window
    float buttonWidth = 200; // Button width
    float buttonHeight = 40; // Button height
    float spacing = 20; // Spacing between buttons

    resumeButton.set(windowCenterX - buttonWidth / 2, windowCenterY - (buttonHeight + spacing) * 1.5, buttonWidth, buttonHeight); // Centered "Resume Game"
    creditsButton.set(windowCenterX - buttonWidth / 2, windowCenterY - buttonHeight / 2, buttonWidth, buttonHeight); // Centered "Credits"
    quitButton.set(windowCenterX - buttonWidth / 2, windowCenterY + (buttonHeight + spacing) * 1.5, buttonWidth, buttonHeight); // Centered "Quit"
    // Initialize the menu state to be closed
    isMenuOpen = false;


    isCreditsOpen = false;
    creditsWindow.set(400, 200, 250, 200); // Position and size of the credits popup
    closeButton.set(creditsWindow.getRight() - 100, creditsWindow.getTop() + 20, 80, 30); // Close button position

    // Create the new window that will open (initially hidden)
    newWindow.set(50, 150, 247, 250); // Position and size of the new window

    // Set background color
    ofBackground(255); // White background

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
        itemPositions.push_back(ofVec2f(xOffset, 50));
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

    //layout setup
    layoutRef.load("layout_main_ref.jpg");
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic if needed
    skinHairBox.SetPos(windowPosPercentX(35.0f), windowPosPercentY(12.0f));
    skinHairBox.SetSize(ofGetWindowWidth() * 0.5f, ofGetWindowHeight() * 0.2f);

    //move dress if it's snapped to character
    for (size_t i = 0; i < clothingItems.size(); ++i) { //check all clothes

        if (itemPositions[i] == characterSnapRegion.hitBox.getCenter()) //if the item was snapped to center of character hitbox
        {
            //testing
            //cout << "in center" << '\n';
            //set the position of the corner of clothing image off center so it draws properly on the character
            itemPositions[i].x = characterSnapRegion.hitBox.getCenter().x - (clothingItems[i]->getWidth() / 2);
            itemPositions[i].y = characterSnapRegion.hitBox.y + characterSnapRegion.hitBox.height * 0.34f;
            
        }

    }
    //character box
    characterSnapRegion.SetPos(windowPosPercentX(10.0f), windowPosPercentY(18.0f));
    characterSnapRegion.SetSize(characterBase.getWidth(), characterBase.getHeight());//windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    characterSnapRegion.hitBox.setPosition(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY());
    characterSnapRegion.hitBox.setSize(characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());

    //clothing box
    clothesBox.SetPos(windowPosPercentX(35.0f), windowPosPercentY(35.0f));
    clothesBox.SetSize(ofGetWindowWidth() * 0.5f, ofGetWindowHeight() * 0.5f);
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
    
    //sking + hair box
    //ofDrawRectangle(windowPosPercentX(35.0f), windowPosPercentY(12.0f), windowScalePercentX(50.0f, 1.0f), windowScalePercentY(20.0f, 1.0f));
    ofDrawRectangle(skinHairBox.GetPos(), skinHairBox.GetWidth(), skinHairBox.GetHeight());

    //clothing box
    ofDrawRectangle(clothesBox.GetPos(), clothesBox.GetWidth(), clothesBox.GetHeight());

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
    //(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    
    ofPushMatrix();
        ofTranslate(characterSnapRegion.hitBox.getCenter());
        //ofScale((1.0f / characterBase.getHeight()) * characterSnapRegion.GetHeight());
        //cout << windowScalePercentY(65.0f, characterBase.getHeight()) << '\n';
        ofSetRectMode(OF_RECTMODE_CENTER);
        characterBase.draw(0, 0);//characterBase.getWidth() * 0.20f, characterBase.getHeight() * 0.5f);
        ofSetRectMode(OF_RECTMODE_CORNER);
        //characterBase.draw(windowPosPercentX(10.0f), windowPosPercentY(18.0f), windowScalePercentX(15.0f, characterBase.getWidth()), windowScalePercentY(65.0f, characterBase.getHeight()));

    //characterBase.draw(400, 200, characterBase.getWidth(), characterBase.getHeight());
    ofPopMatrix();
    
    //character box
    ofDrawRectangle(characterSnapRegion.GetPos(), characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());
    // Draw the button (Main Menu)
    ofSetColor(ofColor::deepPink);
    ofDrawRectangle(menuButton); // Draw the button

    // Draw the label inside the button
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Main Menu", menuButton.getCenter().x - 40, menuButton.getCenter().y);

    //top clothing
    for (int i = 0; i < 4; i++)
    {
        
        topClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.05f);
        topClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);
        
        if (!isDragging && !characterSnapRegion.hitBox.inside(itemPositions[i].x + clothingItems[i]->getWidth() * 0.5f, itemPositions[i].y + clothingItems[i]->getHeight() * 0.5f))
        {
            itemPositions[i] = topClothesBox.GetPos();
        }

        ofDrawRectangle(topClothesBox.GetPos(), topClothesBox.GetWidth(), topClothesBox.GetHeight());
    }

    //bottom clothing
    for (int i = 0; i < 4; i++)
    {
        bottomClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.4f);
        bottomClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);
        
        if (!isDragging && !characterSnapRegion.hitBox.inside(itemPositions[i + 4].x + clothingItems[i + 4]->getWidth() * 0.5f, itemPositions[i + 4].y + clothingItems[i + 4]->getHeight() * 0.5f))
        {
            itemPositions[i + 4] = bottomClothesBox.GetPos();
        }
        
        ofDrawRectangle(bottomClothesBox.GetPos(), bottomClothesBox.GetWidth(), bottomClothesBox.GetHeight());
    }

    // Draw clothing items
    for (size_t i = 0; i < clothingItems.size(); ++i) {

      /*  if (!characterSnapRegion.hitBox.inside(itemPositions[i]))
        {
            if (clothingItems[i]->getHeight() > topClothesBox.GetHeight())
            {
                ofPushMatrix();
                ofTranslate(itemPositions[i]);
                ofScale(1.0f / clothingItems[i]->getHeight() * topClothesBox.GetHeight());
                clothingItems[i]->draw(0, 0);
                ofPopMatrix();
            }
            else if (clothingItems[i]->getWidth() > topClothesBox.GetWidth())
            {
                ofPushMatrix();
                ofTranslate(itemPositions[i]);
                ofScale(1.0f / clothingItems[i]->getWidth() * topClothesBox.GetWidth());
                clothingItems[i]->draw(0,0);
                ofPopMatrix();
            }
        }
        else
        {*/
            //clothingItems[i]->draw(itemPositions[i]);
        //}

        ofSetColor(ofColor::white);

        clothingItems[i]->draw(itemPositions[i].x, itemPositions[i].y);
    }

    // If the menu is open, draw the new window
    if (isMenuOpen) {
        // Update button positions dynamically based on newWindow's position
        resumeButton.set(newWindow.x + 20, newWindow.y + 60, 200, 40);
        creditsButton.set(newWindow.x + 20, newWindow.y + 110, 200, 40);
        quitButton.set(newWindow.x + 20, newWindow.y + 160, 200, 40);

        // Draw the new window
        ofSetColor(ofColor::white);
        ofDrawRectangle(newWindow);

        // Draw buttons inside the window
        ofSetColor(ofColor::deepPink);
        ofDrawRectangle(resumeButton);
        ofDrawRectangle(creditsButton);
        ofDrawRectangle(quitButton);

        // Draw button labels
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Resume Game", resumeButton.getCenter().x - 50, resumeButton.getCenter().y + 5);
        ofDrawBitmapString("Credits", creditsButton.getCenter().x - 30, creditsButton.getCenter().y + 5);
        ofDrawBitmapString("Quit", quitButton.getCenter().x - 20, quitButton.getCenter().y + 5);
    }

    if (isCreditsOpen) {
        // Draw the credits window
        ofSetColor(ofColor::white);
        ofDrawRectangle(creditsWindow);

        // Draw the close button
        ofSetColor(ofColor::white);
        ofDrawRectangle(closeButton);
        ofSetColor(ofColor::black);

        // Draw the credits text
        ofSetColor(ofColor::deepPink);
        ofDrawBitmapString("Game Credits:", creditsWindow.x + 20, creditsWindow.y + 50);
        ofDrawBitmapString("Racha Ibrahim", creditsWindow.x + 20, creditsWindow.y + 80);
        ofDrawBitmapString("Hairuo Chen", creditsWindow.x + 20, creditsWindow.y + 110);
        ofDrawBitmapString("Jason Law", creditsWindow.x + 20, creditsWindow.y + 140);
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

    // Check if the mouse is inside the Main Menu button
    if (menuButton.inside(x, y)) {
        isMenuOpen = !isMenuOpen; // Toggle the menu state
        return; // Prevent further checks if the main menu button was clicked
    }

    if (isMenuOpen) {
        if (resumeButton.inside(x, y)) {
            isMenuOpen = false; // Close the menu
        }
        else if (creditsButton.inside(x, y)) {
            isCreditsOpen = !isCreditsOpen;
            return;
        }
        else if (quitButton.inside(x, y)) {
            ofExit(); // Quit the game
        }
    }

    if (isCreditsOpen && closeButton.inside(x, y)) {
        isCreditsOpen = false; // Close the credits popup
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


        //ofRectangle snapRegion(snapX, snapY, clothingItems[currentItemIndex]->getWidth(), clothingItems[currentItemIndex]->getHeight());
        ofRectangle snapRegion(characterSnapRegion.GetPos(), characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());

        //ofRectangle snapRegion(snapX, snapY, characterBase.getWidth(), characterBase.getHeight());


        // Check if the item is released within the snap region
        if (snapRegion.inside(x, y)) {
            // Center the item on the character base
            //itemPositions[currentItemIndex].x = snapX + (characterBase.getWidth() - clothingItems[currentItemIndex]->getWidth()) / 2;
            //itemPositions[currentItemIndex].y = snapY + (characterBase.getHeight() - clothingItems[currentItemIndex]->getHeight()) / 2;
            itemPositions[currentItemIndex] = snapRegion.getCenter();
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
