// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "Field.h"
#include <vector>
#include <iterator>
#include "Windows.h"

using namespace sf; // подключаем пространство имён sf

int main()
{
  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(VideoMode(1200, 675), "SFML Works!");
  window.setFramerateLimit(60);
  //window.setVerticalSyncEnabled(true);

  //int hor = 0, vert = 0;
  //sf::Texture texture;
  //texture.loadFromFile("C:\\Users\\nikit\\VisualStudio\\sfml_studying\\circle_gems.jpg");
  //sf::Sprite sprite(texture);

  //Gem gem;
  Field field;
  vector<int> streak;

  // Главный цикл приложения: выполняется, пока открыто окно
  while (window.isOpen())
  {
    // Обрабатываем очередь событий в цикле
    Event event;
    
    while (window.pollEvent(event))
    { 

      // Пользователь щёлкнул мышкой?
      if (event.type == Event::MouseButtonPressed)
      {
        Vector2i position = Mouse::getPosition(window);
        //printf("(%d, %d)\n", position.x, position.y);
        field.handleMouseClick(position);
      }

      // Пользователь нажал на «крестик» и хочет закрыть окно?
      if (event.type == Event::Closed) {
        printf("closing...\n");
        window.close(); // тогда закрываем его
      }

      //User have clicked any keyboard key
      if (event.type == Event::KeyPressed)
      {
        printf("Keyboard\n");
        if (event.key.code == Keyboard::Escape)
        {
          cout << "closing" << endl;
          window.close();
        }
        /*switch (event.key.code) {
        case Keyboard::Right:
          printf("Right\n");
          hor++;
          break;
        case Keyboard::Left:
          printf("Left\n");
          hor--;
          break;
        case Keyboard::Up:
          printf("Up\n");
          vert--;
          break;
        case Keyboard::Down:
          printf("Down\n");
          vert++;
          break;
        }*/
      }
    }
    // Установка цвета фона
    window.clear();

    streak = field.findStreak();
    //cout << "findStreak has stopped" << endl;

    if (streak.size() > 0) {
      printf("Streak is: ");
        for (int i = 0; i < streak.size(); i++) {

          printf("%i - %d, ", streak[i], field.gems[streak[i]]->color);
          
        }
    printf("\n");
    //Sleep(5000);
    field.destroyGemStreak(window, streak);
    printf("(Source.cpp) destr has stopped\n");
    }
    //field.gems[0]->shape.setScale(2.f, 1.f);
    field.drawField(window);
    //printf("drawing has stopped\n");

    /*sprite.setPosition(50.f, 50.f);
    Vector2f scl = sprite.getScale();
    printf("scl.x = %lf, scl.y = %lf\n", scl.x, scl.y);
    sprite.setScale(scl / 2.f);
    window.draw(sprite);*/
     

    // Отрисовка круга
    //window.draw(circle);

    // Отрисовка окна
    window.display();
    
  }

  return 0;
}