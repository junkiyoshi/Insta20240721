#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto R = 300;
	auto r = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.025), 0, 1, -120, 120);

	ofColor color;
	for (int i = 0; i < 4; i++) {

		float v_start = ofGetFrameNum() * 6 + i * 90;

		color.setHsb(ofMap(i, 0, 18, 0, 255), 100, 200);

		for (float v = v_start; v < v_start + 60; v += 0.5) {

			auto u = v * 15 + i * 10;
			auto location = this->make_point(R, r, u, v);
			auto next_u = (v + 0.5) * 15 + i * 10;
			auto next = this->make_point(R, r, next_u, v + 0.5);

			ofSetColor(255, ofMap(v, v_start, v_start + 60, 0, 255));
			ofDrawLine(location, next);
		}
	}

	this->cam.end();

	/*
	int start = 180;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}