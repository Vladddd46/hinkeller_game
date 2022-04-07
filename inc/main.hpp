#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "loadTextures.hpp"
#include "Character.hpp"
#include "config.hpp"
#include "Background.hpp"
#include "FallingObject.hpp"
#include "Score.hpp"

void closeWindowEventCheck(sf::RenderWindow &window);
void handleCharacterMovements(Character &character, float time);