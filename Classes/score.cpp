//
//  score.cpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 31/07/18.
//

#include <stdio.h>
#include "score.hpp"


int ScoreManager::getScore() {
    return score;
}

void ScoreManager::setScore(int s) {
    score = s;
}

static ScoreManager *instance = nullptr;
ScoreManager* ScoreManager::getInstance() {
    if (instance == nullptr) {
        instance = new ScoreManager();
        CCLOG("INSIDE: %d", instance->getScore());
    }
    
    return instance;
}

