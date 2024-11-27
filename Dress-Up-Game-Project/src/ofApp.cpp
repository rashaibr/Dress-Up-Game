#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Load images
    ofImage imageToSelect1, imageResult1;
    imageToSelect1.load("imageToSelect1.jpg");
    imageResult1.load("imageResult1.jpg");

    // Add clickable image to the vector
    ClickToSelectImages.push_back(ClickToSelect(imageToSelect1, imageResult1, 50, 50));

    ofLogNotice() << "Setup complete.";
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update logic if needed
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        // Always draw the clickable images
        ClickToSelectImages[i].draw();

        // Draw the result image only if toggled on
        ClickToSelectImages[i].displayResultImage(100, 100);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    for (int i = 0; i < ClickToSelectImages.size(); i++) {
        if (ClickToSelectImages[i].isMouseInside(x, y)) {
            ClickToSelectImages[i].toggleResult(); // Toggle the clicked state
            ofLogNotice() << "Image " << i << " toggled to: " << ClickToSelectImages[i].isClicked;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
