//
//  score.hpp
//  FlappyBird-mobile
//
//  Created by Harish Kumav V on 31/07/18.
//

#ifndef score_hpp
#define score_hpp

class ScoreManager {
public:
    void setScore(int);
    int getScore();
    static ScoreManager* getInstance();
private:
    int score = 0;
};
#endif /* score_hpp */
