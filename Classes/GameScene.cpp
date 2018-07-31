//
//  GameScene.cpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#include "GameScene.hpp"
#include "SceneHelper.hpp"
#include "score.hpp"
#include <cstdlib>

GameScene::GameScene() {
}

SEL_MenuHandler GameScene::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    return nullptr;
}

Control::Handler GameScene::onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) {
    return nullptr;
}
bool GameScene::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "bird", Sprite*, bird);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "scoreCard", Label*, this->scoreCard);
    return false;
}

void GameScene::onEnterTransitionDidFinish() {
}

void GameScene::killBird() {
    Scene* scene = Scene::createWithPhysics();
    ScoreManager *s = ScoreManager::getInstance();
    s->setScore(score/2);
    CCLOG("Score on killing the bird: %d", ScoreManager::getInstance()->getScore());
    
    Node* ourScene = SceneHelper::LoadFromFile("restartscreen");
    scene->addChild(ourScene);
    this->unscheduleUpdate();
    this->unschedule(schedule_selector(GameScene::createPipes));
    Director::getInstance()->replaceScene(scene);
    
    
    gameState = 0;
}

void GameScene::update(float delta){
    if (gameState == 1) {
        if (bird->getPosition().y < 0) {
            this->killBird();
            return;
        }

        auto action = MoveTo::create(0.1, cocos2d::Vec2(bird->getPosition().x, bird->getPosition().y - 3));
        bird->runAction(action);
    }
    
    if (this->worldAdded == 0) {
        this->worldAdded = 1;
        Scene *s = Director::getInstance()->getRunningScene();
        sceneWorld = s->getPhysicsWorld();
        this->setPhysicsWorld(sceneWorld);
        auto ps = PhysicsBody::createBox(bird->getContentSize(), PhysicsMaterial(0, 1, 0));
        bird->setPhysicsBody(ps);
        bird->getPhysicsBody()->setGravityEnable(false);
        ps->setCollisionBitmask(2);
        ps->setContactTestBitmask(1);
        
        Sprite *pipeSafeArea = Sprite::create("pipe-green.png");
        Size size = Director::getInstance()->getVisibleSize();
        pipeSafeArea->setContentSize(Size(size.width - ((size.width/4) - (bird->getContentSize().width)), size.height));
        pipeSafeArea->setAnchorPoint(Vec2(0.0, 0.0));
        pipeSafeArea->setPosition(size.width - pipeSafeArea->getContentSize().width, 0.0);
        pipeSafeArea->setOpacity(0);
        auto p = PhysicsBody::createBox(pipeSafeArea->getContentSize(), PhysicsMaterial(0, 1, 0));
        p->setCollisionBitmask(4);
        p->setContactTestBitmask(1);
        pipeSafeArea->setPhysicsBody(p);
        p->setGravityEnable(false);
        
        this->addChild(pipeSafeArea);
    }
}

bool GameScene::init() {
    if ( !Layer::init() ) {
        CCLOG("Game scene super init failed");
        return false;
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    CCLOG("Game scene super init done");
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameScene::createPipes), 1.0);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
    contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate,this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);
    return true;
}


bool GameScene::onTouchBegan(cocos2d::Touch*, cocos2d::Event*) {
    gameState = 1;
    int height = 0;
    if (bird->getPosition().y > Director::getInstance()->getVisibleSize().height) {
        height = Director::getInstance()->getVisibleSize().height;
    } else {
        height = bird->getPosition().y + 60;
    }
    
    auto action = cocos2d::MoveTo::create(0.2, cocos2d::Vec2(bird->getPosition().x, height));
    bird->runAction(action);
}

void setPipePosition(Sprite* pipe1, Sprite* pipe2) {
    int v1 = rand() % 50;
    int offset = ((50 - (rand() % 100))>0)? 1:-1;
    pipe1->setPosition(550, 60 + (v1 * offset));
    pipe2->setRotation(180);
    pipe2->setPosition(550, 290 + (v1 * offset));
}

void GameScene::createPipes(float dt) {
    if (gameState != 1) return;
    Sprite *pipe1 = Sprite::create( "pipe-green.png");
    Sprite *pipe2 = Sprite::create( "pipe-green.png");

    setPipePosition(pipe1, pipe2);
    
    this->addChild(pipe1);
    this->addChild(pipe2);
    CCLOG("PIPES: %f, %f", pipe1->getPosition().y, pipe2->getPosition().y);
    
    auto action1 = Sequence::create(
                                   MoveTo::create(3, cocos2d::Vec2(-25, pipe1->getPosition().y)),
                                   CallFuncN::create(CC_CALLBACK_0(GameScene::removePipe, this, pipe1)), nullptr);
    
    auto action2 = Sequence::create(
                                   MoveTo::create(3, cocos2d::Vec2(-25, pipe2->getPosition().y)),
                                   CallFuncN::create(CC_CALLBACK_0(GameScene::removePipe, this, pipe2)), nullptr);
    pipe1->runAction(action1);
    pipe2->runAction(action2);
    
    Scene *s = Director::getInstance()->getRunningScene();
    sceneWorld = s->getPhysicsWorld();
    pipe1->setPhysicsBody(createPhysicsBody(pipe1));
    pipe2->setPhysicsBody(createPhysicsBody(pipe2));
}

PhysicsBody* GameScene::createPhysicsBody(Sprite *s) {
    auto ps = PhysicsBody::createBox(s->getContentSize(), PhysicsMaterial(0, 1, 0));
    ps->setGravityEnable(false);
    ps->setCollisionBitmask(1);
    ps->setContactTestBitmask(1);
    return ps;
}

void GameScene::removePipe(Sprite* s) {
    s->removeFromParentAndCleanup(true);
}


bool GameScene::onContactBegin(PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    int aMask = a->getCollisionBitmask();
    int bMask = b->getCollisionBitmask();
    
//    CCLOG("Collision between %d, %d, %d", aMask, bMask, aMask | aMask);
//    if ((aMask | bMask) == 6) {
//        CCLOG("Collision between bird and collision area");
//    } else
//
    if ((aMask | bMask) == 3) {
        CCLOG("Collision between bird and pipe");
        // move to next scene
        this->killBird();
    }

//    else if((aMask | bMask) == 5) {
//        CCLOG("Collision between collision area and pipe");
//    }
//
    return false;
}


bool GameScene::onContactSeparate(PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    int aMask = a->getCollisionBitmask();
    int bMask = b->getCollisionBitmask();

    if ((aMask | bMask) == 5) {
        CCLOG("Score");
        score++;
        ScoreManager *s = ScoreManager::getInstance();
        s->setScore(score/2);
        
        auto p = std::to_string(ScoreManager::getInstance()->getScore());
        auto r = "Score: " + p;
        
        scoreCard->setString(r);
    }

    return false;
}
