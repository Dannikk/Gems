#pragma once
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "Ordinary_Gem.h"
#include <vector>
#include "Windows.h"
#include <iostream>
#include <memory>
//#include <stdio.h>

using namespace std;

const unsigned short int my_SIZE = 6;                       // Размер игрового поля в плашках
const unsigned short int ARRAY_SIZE = my_SIZE * my_SIZE;    // Размер массива
//const int FIELD_SIZE = 600;                               // Размер игрового поля в пикселях
const unsigned short int CELL_SIZE = 105;                   // Размер плашки в пикселях
const unsigned short int LEFT_INDENT = 100;                 // Left indent of game field
const unsigned short int UP_INDENT = 30;                    // Right indent of game field
const unsigned short int ANIMATION_SPEED = 5;               // Speed of movement of gems

class Field/* : public sf::Drawable, public sf::Transformable*/
{
  public:
    vector<Gem*> gems;
    //Gem* gems;
    unsigned short int numberHLGems;
    short int hLightGem;
    unsigned short int seriesSize;

  public:
    Field();
    void fieldInit();
    void drawField(sf::RenderWindow& window);
    void handleMouseClick(sf::Vector2i pos);
    bool isItNeighbour(short int neigbour);
    vector<int> findStreak();
    void swapGems(Gem* a, Gem* b);
    void shiftUpperGems(sf::RenderWindow& window, vector<int>& gems2shift, vector<int>& streak, unsigned short int& height);
    void destroyGemStreak(sf::RenderWindow& window, vector<int>& streak);

    
  private:
    unsigned short int defineHeightOfStreak(vector<int> streak);
    bool defineOrientOfStreak(vector<int> streak);
    void generateNewGems(sf::RenderWindow& window);
    void shiftPointers(unsigned short int& height, vector<int>& streak);

};

