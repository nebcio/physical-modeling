#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetBackgroundColor(ofColor::black);

    gui.setup();
    gui.add(dt.setup("dt", 0.001, 0.001, 1));
    gui.add(numParticle.setup("Num Alive Particles", 1000, 300, maxNumParticles));
    
    particleSystems.push_back(ParticleSystem(maxNumParticles));
    particleSystems.push_back(ParticleSystem(maxNumParticles));


    particleSystems[0].addEmitter(std::make_shared<FireballEmitter>(500, ofVec3f(40, 20, 40), 2));
    particleSystems[0].addEmitter(std::make_shared<FireballEmitter>(500, ofVec3f(40, 20, -40), 2));
    particleSystems[0].addEmitter(std::make_shared<FireballEmitter>(500, ofVec3f(-40, 20, -40), 2));
    particleSystems[0].addEmitter(std::make_shared<FireballEmitter>(500, ofVec3f(-40, 20, 40), 2));

    particleSystems[0].addUpdater(std::make_shared<TimeUpdater>());
    particleSystems[0].addUpdater(std::make_shared<EulerUpdater>());
    particleSystems[0].addUpdater(std::make_shared<ColorUpdater>(ofVec3f(0, 0, 0)));
    particleSystems[0].addUpdater(std::make_shared<GravityUpdater>(0.0f));
    
    
    particleSystems[1].addEmitter(std::make_shared<AshEmitter>(500, ofVec3f(0, 0, 0), true));
    particleSystems[1].addUpdater(std::make_shared<TimeUpdater>());
    particleSystems[1].addUpdater(std::make_shared<EulerUpdater>());
    particleSystems[1].addUpdater(std::make_shared<GravityUpdater>(0.0f));

    // ofDisableAlphaBlending();
    ofDisableArbTex();
    ofEnableDepthTest();

    light.setPosition(0, 200, 0);

    ground.set(1000, 3, 1000);
    ground.setPosition(0, -3, 0);

    floor.set(100, 20, 100);
    floor.setPosition(0, 10, 0);

    background.set(1000.f, 100);

    // brickImage.load("brick.png");
    // brickTexture.allocate(brickImage.getWidth(), brickImage.getHeight(), GL_RGB);
    // brickTexture.loadData(brickImage.getPixels());

    backgroundImage.load("bg1.jpg");
    backgroundTexture.allocate(backgroundImage.getWidth(), backgroundImage.getHeight(), GL_RGB);
    backgroundTexture.loadData(backgroundImage.getPixels());
}

//--------------------------------------------------------------
void ofApp::update()
{
    for(auto &system : particleSystems)
        system.update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    cam.begin();
    light.enable();

    backgroundImage.getTexture().bind();
        background.draw();
    backgroundImage.getTexture().unbind();

    // brickTexture.bind();
    ofSetColor(ofColor(5, 20, 40));
        ground.draw();
    // brickTexture.unbind();
    
    ofSetColor(ofColor::darkGray);
    floor.draw();

    for (auto& system : particleSystems)
        system.draw();

    light.disable();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}
