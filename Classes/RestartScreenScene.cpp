//
//  RestartScreenScene.cpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#include "RestartScreenScene.hpp"
#include "SceneHelper.hpp"
//#include "score.hpp"

RestartScreenScene::RestartScreenScene() {
    this->score = nullptr;
}

SEL_MenuHandler RestartScreenScene::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    return nullptr;
}

Control::Handler RestartScreenScene::onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStartPressed", RestartScreenScene::onPlayPressed);
    return nullptr;
}
bool RestartScreenScene::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "score", Label*, this->score);
    return false;
}

void RestartScreenScene::onPlayPressed(Ref*, Control::EventType) {
    Scene* scene = Scene::createWithPhysics();
    Node* ourScene = SceneHelper::LoadFromFile("game");
    scene->addChild(ourScene);
    Director::getInstance()->replaceScene(scene);
}


bool RestartScreenScene::init() {
    if ( !Layer::init() ) {
        CCLOG("restart scene super init failed");
        return false;
    }
    this->scheduleUpdate();
    return true;
};


void RestartScreenScene::update(float delta){
    auto s = ScoreManager::getInstance()->getScore();
    auto p = std::to_string(s);
    auto r = "Score: " + p;
    this->score->setString(r);
}
