#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> location_list;
	vector<float> deg_list;

	for (int i = 0; i < 35; i++) {

		location_list.push_back(glm::vec2(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 50, ofGetWidth() - 50),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 50, ofGetHeight() - 50)));
		deg_list.push_back(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
	}

	for (int i = 0; i < location_list.size(); i++) {

		ofNoFill();
		for (int k = i + 1; k < location_list.size(); k++) {

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 80) {

				distance > 60 ? ofSetColor(39, ofMap(distance, 60, 80, 255, 0)) : ofSetColor(39);
				
				auto handle_1 = location_list[i] + glm::vec2(50 * cos(deg_list[i] * DEG_TO_RAD), 50 * sin(deg_list[i] * DEG_TO_RAD));
				auto handle_2 = location_list[k] + glm::vec2(50 * cos(deg_list[k] * DEG_TO_RAD), 50 * sin(deg_list[k] * DEG_TO_RAD));

				ofBeginShape();
				ofVertex(location_list[i]);
				ofBezierVertex(handle_1, handle_2, location_list[k]);
				ofEndShape();
			}
		}

		ofFill();
		ofSetColor(39);
		ofDrawCircle(location_list[i], 5);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}