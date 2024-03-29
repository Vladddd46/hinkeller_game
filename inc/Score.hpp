#ifndef SCORE_HPP
#define SCORE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Score {
private:
    sf::Font MyFont;
public:
    sf::Text text;

    Score(std::string fontPath, sf::Color color, int posX, int posY);
    
    void setScore(std::string score);

    void setScore(int score);
};
#endif//SCORE_HPP
