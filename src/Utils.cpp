#include "Utils.hpp"

// closes window if user exit window.
void closeWindowEventCheck(sf::RenderWindow &window) {
    // event for closing window
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


// Moves character depending on button user press.
void handleCharacterMovements(Character &character, float time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        character.move_left(time);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        character.move_right(time);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        character.stay();
    }
}


/* @brief: makes fall all objects, which have attribute isFalling==true
 * @param:
 *        fallingObjects - list of objects, which can fall.
 *        time - ...
 */
void makeObjectsFall(FallingObjectArrayType &fallingObjects, float time) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY; i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            fallingObjects[i].fall(time);
        }
    }
}

// draws each falling object.
void drawFallingObjects(sf::RenderWindow &window, FallingObjectArrayType &fallingObjects) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].getIsFalling()==true) {
            window.draw(fallingObjects[i].sprite);
        }
    }
}


// Falling objects, which are out of screen become not falling.
// Property ifFalling in this objects is set false.
void disableObjectsWhichAreOutOfScreen(FallingObjectArrayType &fallingObjects, int maxHighOfGameWindow) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].sprite.getPosition().y > maxHighOfGameWindow+100) {
            fallingObjects[i].setIsFalling(false);
        }
    }
}


// Checks whether user object and falling object intersects.
// returns number of intersections.
int checkIfCharacterCaughtObject(Character &character, 
                                 FallingObjectArrayType &fallingObjects,
                                 bool &chachaCought) {
    int numberOfCaughtObjects = 0;

    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if(character.sprite.getGlobalBounds().intersects(fallingObjects[i].sprite.getGlobalBounds()) 
           && fallingObjects[i].getIsFalling()==true) {
            numberOfCaughtObjects += 1;
            chachaCought = fallingObjects[i].getIsMagicObject();
            fallingObjects[i].setIsFalling(false);
            if (fallingObjects[i].getIsFriendly() == false) {
                return -1;
            };
        }
    }
    return numberOfCaughtObjects;
}

void enableNewFallingObjects(FallingObjectArrayType &fallingObjects, 
                             int number, 
                             int widthOfGameWindow, 
                             int minFallSpeed, 
                             int maxFallSpeed,
                             int probabilityOfUnfriendlyObjectSpawn,
                             std::map<std::string, sf::Texture> &texturesForFallingObjects,
                             bool sheepsFalling) {
    for (int i=0;i<MAX_FALLING_OBJECTS_IN_ARRAY;i++) {
        if (fallingObjects[i].getIsFalling()==false && number > 0) {
            FallingObject newFallingObject = FallingObject();
            fallingObjects[i] = newFallingObject;

            fallingObjects[i].setIsFalling(true);
            fallingObjects[i].spawn(rand()%(widthOfGameWindow-25), -10);
            fallingObjects[i].setSpeed(rand()%maxFallSpeed+minFallSpeed);

            if (sheepsFalling) {
                fallingObjects[i].setTexture(texturesForFallingObjects["sheep"]);
            }
            else if (rand()%probabilityOfUnfriendlyObjectSpawn+1 == 1) {
                // unfriendly objects
                fallingObjects[i].setTexture(texturesForFallingObjects["bomb"]);
                fallingObjects[i].setIsFriendly(false);
            }
            else {
                // friendly objects

                // propability of chacha fall.
                if ((rand()%100)<PROBABILITY_OF_CHACHA_SPAWN_IN_PERCENT) {
                    fallingObjects[i].setTexture(texturesForFallingObjects["chacha"]);
                    fallingObjects[i].setIsMagicObject(true);
                }
                else {
                    fallingObjects[i].setTexture(texturesForFallingObjects["hinkalli"]);
                }
                fallingObjects[i].setIsFriendly(true);
            }
            number--;
        }
    }
}
