//
//  SceneHelper.cpp
//  FlappyBird
//
//  Created by Harish Kumav V on 26/07/18.
//

#include "SceneHelper.hpp"
#include "IntroScene.hpp"
#include "GameScene.hpp"
#include "RestartScreenScene.hpp"

NodeLoaderLibrary* SceneHelper::loader = nullptr;

Node* SceneHelper::LoadFromFile(const std::string& ccbName) {
    if (loader == nullptr) {
        loader = registerNodeLoaders();
        loader->retain();
    }
    
    CCBReader* reader = new CCBReader(loader);
    Node* node = reader->readNodeGraphFromFile(ccbName.c_str());
    return node;
}

NodeLoaderLibrary* SceneHelper::registerNodeLoaders() {
    NodeLoaderLibrary* loaderLib = nullptr;
    if (loaderLib == nullptr) {
        loaderLib = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
        loaderLib->registerNodeLoader("IntroScene", IntroSceneLoader::loader());
        loaderLib->registerNodeLoader("GameScene", GameSceneLoader::loader());
        loaderLib->registerNodeLoader("RestartScene", RestartScreenSceneLoader::loader());
    }
    return loaderLib;
}
