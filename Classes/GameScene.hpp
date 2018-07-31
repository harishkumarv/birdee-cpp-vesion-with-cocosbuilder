//
//  GameScene.hpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "cocos-ext.h"

#include "cocosbuilder/CocosBuilder.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocosbuilder;

class GameScene : public Layer, public CCBMemberVariableAssigner, public CCBSelectorResolver{
public:
    GameScene();
    void onEnterTransitionDidFinish() override;
    void update(float) override;
    virtual bool init() override;
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
    void killBird();
    PhysicsWorld *sceneWorld;
    int worldAdded = 0;
    Sprite *pipeSafeArea;
    Label *scoreCard;
    int score = 0;
    Sprite* bird;
    int gameState = 0;
    
    void createPipes(float);
    void removePipe(Sprite*);
    void setPhysicsWorld(PhysicsWorld *world) {
        sceneWorld = world;
    };
    PhysicsBody* createPhysicsBody(Sprite *s);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) override;
    Control::Handler onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) override;
    bool onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) override;
    CREATE_FUNC(GameScene);
    bool onContactBegin(PhysicsContact &contact);
    bool onContactSeparate(PhysicsContact &contact);
};

class GameSceneLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GameSceneLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
};
#endif /* GameScene_h */
