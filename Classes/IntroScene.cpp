//
//  IntroScene.cpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#include "IntroScene.hpp"
#include "SceneHelper.hpp"

IntroScene::IntroScene() {
}

SEL_MenuHandler IntroScene::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    return nullptr;
}

Control::Handler IntroScene::onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStartPressed", IntroScene::onPlayPressed);
    return nullptr;
}
bool IntroScene::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) {
    return false;
}

void IntroScene::onEnterTransitionDidFinish() {
}

void IntroScene::onPlayPressed(Ref*, Control::EventType) {
    Scene* scene = Scene::createWithPhysics();
    Node* ourScene = SceneHelper::LoadFromFile("game");
    scene->addChild(ourScene);

    Director::getInstance()->pushScene(scene);
}
