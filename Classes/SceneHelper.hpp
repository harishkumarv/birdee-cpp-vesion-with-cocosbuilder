//
//  SceneHelper.hpp
//  FlappyBird
//
//  Created by Harish Kumav V on 26/07/18.
//

#ifndef SceneHelper_hpp
#define SceneHelper_hpp

#include "cocos2d.h"
#include "cocos-ext.h"

#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocosbuilder;

class SceneHelper {
private:
    static NodeLoaderLibrary* loader;
    static NodeLoaderLibrary* registerNodeLoaders();
    
public:
    static Node* LoadFromFile(const std::string& ccbName);
};

#endif /* SceneHelper_hpp */
