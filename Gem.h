#pragma once
#include <SFML/Graphics.hpp>
//#include "Field.h"

const unsigned short int COLORS = 6;

enum gemColor {
  Red,
  Green,
  Blue,
  Yellow,
  Cyan,
  White
};


class Gem /*public sf::Drawable, public sf::Transformable*/
{
  public:
    sf::Texture texture, tex_focus;      //Ordinary and highlighted textures
    sf::CircleShape shape;               //Gem shape
    gemColor color;                      //Gem color
    sf::Vector2f position;               //Gem position
    bool flag;                           //Sign that the gem is highlighted
  public:
    Gem();
    virtual void abstr() = 0;
    void drawGem(sf::RenderWindow& window, sf::Vector2f position);
    void drawGem(sf::RenderWindow& window);
    void chooseGem();
    void unchooseGem();
    void setColor(gemColor& color);
    void makeGemInvisible();
    //void CheckStrike();

    //~Gem();
  private:
    sf::Color chooseRandomColor();
};

