//
//  IntroScene.hpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#ifndef IntroScene_h
#define IntroScene_h

#include "cocos2d.h"
#include "cocos-ext.h"

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocosbuilder;

class IntroScene : public Layer, public CCBMemberVariableAssigner, public CCBSelectorResolver{
public:
    IntroScene();
    void onEnterTransitionDidFinish();
    void onPlayPressed(Ref*, Control::EventType);

    SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) override;
    Control::Handler onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) override;
    bool onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) override;
    CREATE_FUNC(IntroScene);
};

class IntroSceneLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~IntroSceneLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(IntroSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(IntroScene);
};
#endif /* IntroScene_h */
