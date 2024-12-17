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
    
    //tops
    pinkShirt.load("pinkShirt.png");
    purpleDress.load("purpleDress.png");
    redDress.load("redDress.png");
    greenShirt.load("greenShirt.png");
    //feet
    pinkShoes.load("pinkShoes.png");
    purpleShoes.load("purpleShoes.png");
    //pants
    jeans.load("jeans.png");
    shorts.load("shorts.png");

    //list of clothing items

    //tops
    clothingItems.push_back(&pinkShirt);
    clothingItems.push_back(&purpleDress);
    clothingItems.push_back(&redDress);
    clothingItems.push_back(&greenShirt);
    //feet
    clothingItems.push_back(&pinkShoes);
    clothingItems.push_back(&purpleShoes);
    //pants
    clothingItems.push_back(&jeans);
    clothingItems.push_back(&shorts);


    int xOffset = 200; // Horizontal offset for positioning
    for (size_t i = 0; i < clothingItems.size(); ++i) {
        itemPositions.push_back(ofVec2f(xOffset, 50));
        xOffset += 200; // Increment position for the next item
    }

    isDragging = false;
    currentItemIndex = -1; // No item is selected initially

    // Load the ClickToSelect images
    blond.load("blond.png");
    blondButton.load("blondButton.png");
    red.load("red.png");
    redButton.load("redButton.png");
    brown.load("brown.png");
    brownButton.load("brownButton.png");
    
    gold.load("gold.png");
    goldButton.load("goldButton.png");
    silver.load("silver.png");
    silverButton.load("silverButton.png");
    white.load("white.png");
    whiteButton.load("whiteButton.png");
    
    bg1.load("bg1.png");
    bg1Button.load("bg1Button.png");
    bg2.load("bg2.png");
    bg2Button.load("bg2Button.png");
    bg3.load("bg3.png");
    bg3Button.load("bg3Button.png");
    bg4.load("bg4.png");
    bg4Button.load("bg4Button.png");

    // Add the interactive image to the Hairstyles vector
    Hairstyles.push_back(ClickToSelect(blondButton, blond, 50, 50));
    Hairstyles.push_back(ClickToSelect(redButton, red, 50, 50));
    Hairstyles.push_back(ClickToSelect(brownButton, brown, 50, 50));

    // Add the interactive image to the Accessories vector
    Accessories.push_back(ClickToSelect(goldButton, gold, 50, 50));
    Accessories.push_back(ClickToSelect(silverButton, silver, 50, 50));
    Accessories.push_back(ClickToSelect(whiteButton, white, 50, 50));

    // Add the interactive image to the Backgrounds vector
    Backgrounds.push_back(ClickToSelect(bg1Button, bg1, 50, 50));
    Backgrounds.push_back(ClickToSelect(bg2Button, bg2, 50, 50));
    Backgrounds.push_back(ClickToSelect(bg3Button, bg3, 50, 50));
    Backgrounds.push_back(ClickToSelect(bg4Button, bg4, 50, 50));

    ofLogNotice() << "Setup complete. Clickable images initialized.";

    //load reset image
    restartImage.load("restart.png");

    // Load background music
    backgroundMusic.load("backgroundMusic.mp3"); // Make sure to place the audio file in the correct folder
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    isMusicPlaying = true;

    // Load the music toggle button image
    musicButton.load("musicButton.png");
    musicButtonRect.set(500, 50, musicButton.getWidth(), musicButton.getHeight()); // Adjust position and size

    // Load the camera button image
    cameraButton.load("camera.png");
    cameraButtonRect.set(0 ,0 ,cameraButton.getWidth() ,cameraButton.getHeight());
    cameraSound.load("cameraSound.mp3");
    cameraSound.setLoop(false);
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic if needed
    hairBox.SetPos(windowPosPercentX(30.0f), windowPosPercentY(12.0f));
    hairBox.SetSize(ofGetWindowWidth() * 0.6f, ofGetWindowHeight() * 0.25f);

    //move dress if it's snapped to character
    for (size_t i = 0; i < clothingItems.size(); ++i) { //check all clothes

        if (itemPositions[i] == characterSnapRegion.hitBox.getCenter()) //if the item was snapped to center of character hitbox
        {
            //testing
            //cout << "in center" << '\n';
            //set the position of the corner of clothing image off center so it draws properly on the character
            itemPositions[i].x = characterSnapRegion.hitBox.getCenter().x - (clothingItems[i]->getWidth() / 2);
            //snap dresses to correct height
            if (i < 4)
            {
                itemPositions[i].y = characterSnapRegion.hitBox.y + characterSnapRegion.hitBox.height * 0.34f;
            }
            //snap shoes to correct height
            if (i >= 4 && i <= 5)
            {
                itemPositions[i].y = characterSnapRegion.hitBox.y + characterSnapRegion.hitBox.height - clothingItems[i]->getHeight();
            }
            //snap pants to correct height
            if (i > 5)
            {
                itemPositions[i].y = characterSnapRegion.hitBox.y + characterSnapRegion.hitBox.height * 0.55f;
            }
        }

    }

    // Set top clothing positions
    for (int i = 0; i < 4; i++)
    {

        topClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.05f);
        topClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);

        if (!isDragging && !characterSnapRegion.hitBox.inside(itemPositions[i].x + clothingItems[i]->getWidth() * 0.5f, itemPositions[i].y + clothingItems[i]->getHeight() * 0.5f))
        {
            itemPositions[i] = topClothesBox.GetPos();
        }

    }

    // Set bottom clothing positions
    for (int i = 0; i < 4; i++)
    {
        bottomClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.6f);
        bottomClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);

        if (!isDragging && !characterSnapRegion.hitBox.inside(itemPositions[i + 4].x + clothingItems[i + 4]->getWidth() * 0.5f, itemPositions[i + 4].y + clothingItems[i + 4]->getHeight() * 0.5f))
        {
            itemPositions[i + 4] = bottomClothesBox.GetPos();
        }

    }

    //hair buttons
    for (int i = 0; i < Hairstyles.size(); i++)
    {
        Hairstyles[i].setPos(hairBox.GetPosX() + (hairBox.GetWidth() * 0.2f) + hairBox.GetWidth() * 0.20f * i, hairBox.GetPosY() + hairBox.GetHeight() * 0.6f);
    }
    //accessories
    for (int i = 0; i < Accessories.size(); i++)
    {
        Accessories[i].setPos((hairBox.GetPosX() + hairBox.GetWidth() * 0.2f) + hairBox.GetWidth() * 0.10f * i, hairBox.GetPosY() + hairBox.GetHeight() * 0.2f);
    }
    //backgrounds
    for (int i = 0; i < Backgrounds.size(); i++)
    {
        Backgrounds[i].setPos((hairBox.GetPosX() + hairBox.GetWidth() * 0.2f) + hairBox.GetWidth() * 0.10f * (i + 3), hairBox.GetPosY() + hairBox.GetHeight() * 0.2f);
    }
    //character box
    characterSnapRegion.SetPos(windowPosPercentX(10.0f), windowPosPercentY(18.0f));
    characterSnapRegion.SetSize(characterBase.getWidth(), characterBase.getHeight());//windowScalePercentX(15.0f, 1.0f), windowScalePercentY(65.0f, 1.0f));
    characterSnapRegion.hitBox.setPosition(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY());
    characterSnapRegion.hitBox.setSize(characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());

    //character stand
    characterStand.SetSize(characterSnapRegion.GetWidth() * 1.5f, ofGetWindowHeight());
    characterStand.SetPos(characterSnapRegion.hitBox.getCenter().x - characterStand.GetWidth() * 0.5f, characterSnapRegion.hitBox.getCenter().y + characterSnapRegion.GetHeight() * 0.5f);

    //clothing box
    clothesBox.SetPos(windowPosPercentX(30.0f), windowPosPercentY(38.0f));
    clothesBox.SetSize(ofGetWindowWidth() * 0.6f, ofGetWindowHeight() * 0.6f);

    //reset box
    restartBox.SetPos(ofGetWindowWidth() - (windowScalePercentY(10.0f, 1.0f) * 2.2), windowPosPercentY(1.0f));
    restartBox.SetSize(windowScalePercentY(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));
    restartBox.hitBox.setPosition(restartBox.GetPosX(), restartBox.GetPosY());
    restartBox.hitBox.setSize(restartBox.GetWidth(), restartBox.GetHeight());

    //music box
    musicButtonRect.setPosition(ofGetWindowWidth() - windowScalePercentY(10.0f, 1.0f), windowPosPercentY(1.0f));
    musicButtonRect.setSize(windowScalePercentY(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));

    //camera box
    cameraButtonRect.setPosition(ofGetWindowWidth() - windowScalePercentX(10.0f, 1.0f), windowPosPercentY(88.0f));
    cameraButtonRect.setSize(windowScalePercentX(10.0f, 1.0f), windowScalePercentY(10.0f, 1.0f));
}

//--------------------------------------------------------------
void ofApp::draw() {

    //draw backgrounds
    ofSetColor(ofColor::white);
    for (int i = 0; i < Backgrounds.size(); i++)
    {
        ofPushMatrix();
        ofScale((1.0f / Backgrounds[i].getDisplayWidth()) * ofGetWindowWidth());
        Backgrounds[i].displayResultImage(0.0f, 0.0f);
        ofPopMatrix();
    }

    //character stand
    ofSetColor(ofColor::deepPink);
    ofDrawRectRounded(characterStand.GetPos(), characterStand.GetWidth(), characterStand.GetHeight(), 50.0f);
    
    //box for hair, accessories, and backgrounds
    ofDrawRectRounded(hairBox.GetPos(), hairBox.GetWidth(), hairBox.GetHeight(), 50.0f);

    //clothing box
    ofDrawRectRounded(clothesBox.GetPos(), clothesBox.GetWidth(), clothesBox.GetHeight(), 50.0f);
    ofSetColor(ofColor::white);
    
    // Text for upper box
    ofDrawBitmapString("\n Accessories\n      &\n Backgrounds:", hairBox.GetPosX() + hairBox.GetWidth() * 0.02f, hairBox.GetPosY() + hairBox.GetHeight() * 0.22f);
    ofDrawBitmapString(" Hair:", hairBox.GetPosX() + hairBox.GetWidth() * 0.02f, hairBox.GetPosY() + hairBox.GetHeight() * 0.70f);

    //accesory boxes
    for (int i = 0; i < Accessories.size(); i++)
    {
        Accessories[i].draw();
    }
    //background boxes
    for (int i = 0; i < Backgrounds.size(); i++)
    {
        Backgrounds[i].draw();
    }
    //hair boxes
    for (int i = 0; i < Hairstyles.size(); i++)//HairLenghts.size(); i++)
    {
        Hairstyles[i].draw();//((hairBox.GetPosX() + hairBox.GetWidth() * 0.2f) + hairBox.GetWidth() * 0.20f * i, hairBox.GetPosY() + hairBox.GetHeight() * 0.6f);
    }

    //character box
    ofPushMatrix();
        ofTranslate(characterSnapRegion.hitBox.getCenter());
        ofSetRectMode(OF_RECTMODE_CENTER);
        characterBase.draw(0, 0);
        ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();

    // Draw the button (Main Menu)
    ofSetColor(ofColor::deepPink);
    ofDrawRectRounded(menuButton, 25.0f); // Draw the button

    // Draw the label inside the button
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Main Menu", menuButton.getCenter().x - 40, menuButton.getCenter().y);

    //draw hair
    for (int i = 0; i < Hairstyles.size(); i++)
    {
        Hairstyles[i].displayResultImage(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY());
    }

    // Draw clothing items in reverse order so pants are under dresses
    for (size_t i = clothingItems.size(); i > 0; --i) {
        clothingItems[i - 1]->draw(itemPositions[i - 1].x, itemPositions[i - 1].y);
    }

    //draw accessories
    for (int i = 0; i < Accessories.size(); i++)
    {
        Accessories[i].displayResultImage(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY());
    }

    // If the menu is open, draw the new window
    if (isMenuOpen) {
        // Update button positions dynamically based on newWindow's position
        resumeButton.set(newWindow.x + 20, newWindow.y + 60, 200, 40);
        creditsButton.set(newWindow.x + 20, newWindow.y + 110, 200, 40);
        quitButton.set(newWindow.x + 20, newWindow.y + 160, 200, 40);

        // Draw the new window
        ofSetColor(ofColor::white);
        ofDrawRectRounded(newWindow, 25.0f);

        // Draw buttons inside the window
        ofSetColor(ofColor::deepPink);
        ofDrawRectRounded(resumeButton, 25.0f);
        ofDrawRectRounded(creditsButton, 25.0f);
        ofDrawRectRounded(quitButton, 25.0f);

        // Draw button labels
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Resume Game", resumeButton.getCenter().x - 50, resumeButton.getCenter().y + 5);
        ofDrawBitmapString("Credits", creditsButton.getCenter().x - 30, creditsButton.getCenter().y + 5);
        ofDrawBitmapString("Quit", quitButton.getCenter().x - 20, quitButton.getCenter().y + 5);
    }

    if (isCreditsOpen) {
        // Draw the credits window
        ofSetColor(ofColor::white);
        ofDrawRectRounded(creditsWindow, 25.0f);

        // Draw the close button
        ofSetColor(ofColor::deepPink);
        ofDrawRectRounded(closeButton, 25.0f);
        ofSetColor(ofColor::white);
        ofDrawBitmapString("X", closeButton.getCenter().x - 5, closeButton.getCenter().y + 5);

        // Draw the credits text
        ofSetColor(ofColor::deepPink);
        ofDrawBitmapString("Game Credits:", creditsWindow.x + 20, creditsWindow.y + 50);
        ofDrawBitmapString("Racha Ibrahim", creditsWindow.x + 20, creditsWindow.y + 80);
        ofDrawBitmapString("Hairuo Chen", creditsWindow.x + 20, creditsWindow.y + 110);
        ofDrawBitmapString("Jason Law", creditsWindow.x + 20, creditsWindow.y + 140);
        ofSetColor(ofColor::white);
    }

    // Top icons
    // Music button
    if (!isMusicPlaying)
    {
        ofSetColor(ofColor::grey); // Choose a color for the music button when disabled
    }
    else
    {
        ofSetColor(ofColor::white);
    }
    musicButton.draw(musicButtonRect); // Draw the music button at its specified position
    ofSetColor(ofColor::white);

    // Restart button
    ofPushMatrix();
    ofTranslate(restartBox.GetPos());
    ofScale(1.0f / restartImage.getWidth() * restartBox.GetWidth());
    restartImage.draw(0, 0);
    ofPopMatrix();

    // Bottom icons
    // Camera button
    if (cameraButtonRect.inside(ofGetMouseX(), ofGetMouseY()))
    {
        // change color when we hover
        ofSetColor(ofColor::deepPink);
    }
    else if (characterSaved)
    {
        // change camera color to show that image was saved
        ofSetColor(ofColor::lightPink);
    }
    else
    {
        // default color
        ofSetColor(ofColor::white);
    }
    ofPushMatrix();
    ofTranslate(cameraButtonRect.getCenter());
    ofScale(1.0f / cameraButton.getHeight() * cameraButtonRect.getHeight());
    ofSetRectMode(OF_RECTMODE_CENTER);
    cameraButton.draw(0, 0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();
}

//--------------------------------------------------------------
    void ofApp::mousePressed(int x, int y, int button) {
        handleGroupClick(Hairstyles, x, y);
        handleGroupClick(Accessories, x, y);
        handleGroupClick(Backgrounds, x, y);

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

        // Dragging logic
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

        // if the player hits the restart button
        if (restartBox.hitBox.inside(x, y))
        {
            //top clothes
            for (int i = 0; i < 4; i++)
            {

                topClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.05f);
                topClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);
                itemPositions[i] = topClothesBox.GetPos();
            }

            //bottom clothes
            for (int i = 0; i < 4; i++)
            {
                bottomClothesBox.SetPos(clothesBox.GetPos().x + clothesBox.GetWidth() * 0.25f * i + clothesBox.GetWidth() * 0.04f, clothesBox.GetPos().y + clothesBox.GetHeight() * 0.6f);
                bottomClothesBox.SetSize(clothesBox.GetHeight() * 0.3f, clothesBox.GetHeight() * 0.3f);
                itemPositions[i + 4] = bottomClothesBox.GetPos();
            }
            groupClickDisable(Hairstyles);
            groupClickDisable(Accessories);
            groupClickDisable(Backgrounds);

        }

        if (musicButtonRect.inside(x, y)) {
            toggleBackgroundMusic();  // Toggle music when the button is clicked
        }

        if (cameraButtonRect.inside(x, y))
        {
            //if the character's name is not NULL
            //takePicture(string name);
            //else use default naming
            takePicture(); // take a screen shot of the character
            cameraSound.play();
            characterSaved = true;
        }
        else
        {
            characterSaved = false;
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

void ofApp::handleGroupClick(vector<ClickToSelect>& group, int x, int y) {
    bool toggled = false;

    // Check which image in the group is clicked
    for (int i = 0; i < group.size(); i++) {
        if (group[i].isMouseInside(x, y)) {
            group[i].toggleResult();
            toggled = group[i].isToggled();
        }
    }

    // Disable other images in the group if one is toggled
    if (toggled) {
        for (int i = 0; i < group.size(); i++) {
            if (!group[i].isMouseInside(x, y)) {
                group[i].disable();
            }
        }
    }
}

//disable all itmes of a click to select group
void ofApp::groupClickDisable(vector<ClickToSelect>& group) {
    for (int i = 0; i < group.size(); i++)
    {
        group[i].disable();
    }
}

void ofApp::toggleBackgroundMusic() {
    if (isMusicPlaying) {
        backgroundMusic.stop();
    }
    else {
        backgroundMusic.play();
    }
    isMusicPlaying = !isMusicPlaying;
}

// Screen shot character and increment saves
void ofApp::takePicture()
{
    ofImage screenshot;
    static int count = 0;
    // we start at '0' and can increment to 3 digits (ex. max = 999)
    string filename = "character_" + ofToString(count, 3, '0') + ".png";
    screenshot.grabScreen(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY(), characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());
    screenshot.save(filename);
    count++;
}

// We can save the image with the character's name too
void ofApp::takePicture(string name)
{
    ofImage screenshot;
    string filename = name + ".png";
    screenshot.grabScreen(characterSnapRegion.GetPosX(), characterSnapRegion.GetPosY(), characterSnapRegion.GetWidth(), characterSnapRegion.GetHeight());
    screenshot.save(filename);
}