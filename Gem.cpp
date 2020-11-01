#include "Gem.h"

Gem::Gem()
{
  //sf::IntRect rect(1, 1, 420, 420);
  //sf::CircleShape circle(50.f, 4);
  //this->circ = sf::CircleShape(120.f);
  
  this->shape = sf::CircleShape(50.f);

  //load simple texture
  this->texture.loadFromFile("C:\\Users\\nikit\\Downloads\\circle_gem.png");

  //load focused texture
  this->tex_focus.loadFromFile("C:\\Users\\nikit\\Downloads\\circle_gem_light.png");
  printf("__constr__");
  //Choose random color for gem
  sf::Color color = chooseRandomColor();

  this->shape.setTexture(&this->texture, true);
  this->shape.setFillColor(color);
  this->flag = 0;

  //this->shape.setPosition(10.f, 30.f);

  /*this->circ.setTexture(&this->tex_focus, true);
  this->circ.setPosition(300.f, 30.f);
  this->circ.setFillColor(sf::Color::Red);*/

  /*this->sprite.setTexture(this->texture);
  scl = this->sprite.getScale();
  this->sprite.setScale(scl / 4.f);
  this->sprite.move(80.f, 80.f);*/

  

}

void Gem::drawGem(sf::RenderWindow &window, sf::Vector2f position) 
{
  printf("draw this\n");
  
  this->position = position;
  this->shape.setPosition(position);

  window.draw(this->shape);
  printf("now i'm here\n");
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

//Gem::~Gem()
//{
//  
//}

sf::Color Gem::chooseRandomColor() 
{
  //Choose int from 1 to COLORS(=6)
  unsigned short int color = rand() % COLORS;
  printf("Random color is %hu\n", color);

  this->color = (gemColor)color;

  //Return color
  switch (color) {
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

void Gem::setColor(gemColor& color)
{
  this->color = color;

  switch (color) {
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