//
//  RestartScreenScene.hpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 30/07/18.
//

#ifndef RestartScreenScene_h
#define RestartScreenScene_h

#include "cocos-ext.h"
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "score.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocosbuilder;

class RestartScreenScene : public Layer, public CCBMemberVariableAssigner, public CCBSelectorResolver{
public:
    RestartScreenScene();
    void onPlayPressed(Ref*, Control::EventType);
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) override;
    Control::Handler onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) override;
    bool onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) override;
    CREATE_FUNC(RestartScreenScene);
    Label *score;
    virtual bool init() override;
    void update(float) override;
};

class RestartScreenSceneLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~RestartScreenSceneLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RestartScreenSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RestartScreenScene);
};
#endif /* RestartScreenScene_h */

