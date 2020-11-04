// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Gem.h"
#include <iostream>

using namespace std;

Gem::Gem()
{
  this->shape = sf::CircleShape(50.f);

  //load simple texture
  this->texture.loadFromFile("C:\\Users\\nikit\\Downloads\\circle_gem.png");

  //load focused texture
  this->tex_focus.loadFromFile("C:\\Users\\nikit\\Downloads\\circle_gem_light.png");
  //printf("__constr__");
  //Choose random color for gem
  //sf::Color color = chooseRandomColor();

  this->shape.setTexture(&this->texture, true);
  this->shape.setFillColor(chooseRandomColor());
  this->flag = 0;

}

Gem::Gem(const Gem& cop)
{
  texture = cop.texture;
  tex_focus = cop.tex_focus;
  shape = cop.shape;
  color = cop.color;
  position = cop.position;
  flag = cop.color;
  cout << "copy gem" << endl;
}

void Gem::drawGem(sf::RenderWindow &window, sf::Vector2f pos) 
{
  
  this->position = pos;
  this->shape.setPosition(pos);

  window.draw(this->shape);
}

void Gem::drawGem(sf::RenderWindow& window)
{
  window.draw(this->shape);
}

void Gem::chooseGem() 
{
  this->shape.setTexture(&this->tex_focus, true);
  this->flag = true;
}

void Gem::unchooseGem() 
{
  this->shape.setTexture(&this->texture, true);
  this->flag = false;
}

Gem::~Gem()
{
 

  printf("__destruct__ %d\n", this->color);
}

sf::Color Gem::chooseRandomColor() 
{
  //Choose int from 1 to COLORS(=6)
  unsigned short int clr = rand() % COLORS;
  //printf("Random color is %hu\n", clr);

  this->color = (gemColor)clr;

  //Return color
  switch (clr) {
  case gemColor::Red:
    return sf::Color::Red;
    break;
  case gemColor::Green:
    return sf::Color::Green;
    break;
  case gemColor::Blue:
    return sf::Color::Blue;
    break;
  case gemColor::Yellow:
    return sf::Color::Yellow;
    break;
  case gemColor::Cyan:
    return sf::Color::Cyan;
    break;
  case gemColor::White:
    return sf::Color::White;
    break;
  }

}

void Gem::setColor(gemColor& clr)
{
  this->color = clr;

  switch (clr) {
  case gemColor::Red:
    this->shape.setFillColor(sf::Color::Red);
    break;
  case gemColor::Green:
    this->shape.setFillColor(sf::Color::Green);
    break;
  case gemColor::Blue:
    this->shape.setFillColor(sf::Color::Blue);
    break;
  case gemColor::Yellow:
    this->shape.setFillColor(sf::Color::Yellow);
    break;
  case gemColor::Cyan:
    this->shape.setFillColor(sf::Color::Cyan);
    break;
  case gemColor::White:
    this->shape.setFillColor(sf::Color::White);
    break;
  }

}

void Gem::makeGemInvisible() 
{
  this->shape.setFillColor(sf::Color::Black);
}