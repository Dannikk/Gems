#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "Field.h"
#include <vector>
#include <iterator>

using namespace sf; // подключаем пространство имён sf

int main()
{
  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(VideoMode(1200, 675), "SFML Works!");
  window.setFramerateLimit(60);

  int hor = 0, vert = 0;
  sf::Texture texture;
  texture.loadFromFile("C:\\Users\\nikit\\VisualStudio\\sfml_studying\\circle_gems.jpg");
  sf::Sprite sprite(texture);

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

        //// Если это была левая кнопка мыши, то пробуем выполнить перестановку "пятнашек"
        //if (event.key.code == Mouse::Left)
        //{
        //  // Получаем координаты мыши того места, где был произведён щелчок
        //  Vector2i position = Mouse::getPosition(window);
        //  // Переводим эти координаты в координаты наших блоков
        //  int x = position.x / blockWidht + 1;
        //  int y = position.y / blockWidht + 1;

        //  // Переменные для задания смещения...
        //  int dx = 0; // ...горизонтального...
        //  int dy = 0; // ...и вертикального.

        //  // Если справа пустое место
        //  if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
        //  // Если снизу пустое место
        //  if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
        //  // Если сверху пустое место
        //  if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
        //  // Если слева пустое место
        //  if (grid[x - 1][y] == 16) { dx = -1; dy = 0; };
        //}
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
          window.close();
        switch (event.key.code) {
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
        }
      }
    }
    // Установка цвета фона
    window.clear();

    // Создаём фигуру: круг радиусом 50
    //CircleShape circle(50.f);
    // Закрашиваем наш круг 
    //circle.setFillColor(Color(230, 0, 230));
    //printf("m = %lf\n", m);
    //printf("now hor = %d, vert = %d\n\n", hor, vert);
    //circle.move(20 * hor, 20 * vert);

    streak = field.findStreak();

    if (streak.size() > 0) {
      printf("Streak is: ");
        for (vector<int>::const_iterator i = streak.begin(); i != streak.end(); i++) {
          printf("%i ", *i);
          
        }
    printf("\n");
    }
    field.destroyGemStreak(window, streak);

    field.drawField(window);
    //printf("q");

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