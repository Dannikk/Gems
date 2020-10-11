#include <SFML/Graphics.hpp>

using namespace sf; // подключаем пространство имён sf

int main()
{
  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(VideoMode(800, 450), "SFML Works!");
	int hor = 0, vert = 0;

  // Главный цикл приложения: выполняется, пока открыто окно
  while (window.isOpen())
  {
	// Обрабатываем очередь событий в цикле
	Event event;
	while (window.pollEvent(event))
	{
	  // Пользователь нажал на «крестик» и хочет закрыть окно?
	  if (event.type == Event::Closed) {
		printf("closing...\n");
		window.close(); // тогда закрываем его
	  }
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
	window.clear(Color(250, 220, 100, 0));

	// Создаём фигуру: круг радиусом 50
	CircleShape circle(50.f);

	// Закрашиваем наш круг 
	circle.setFillColor(Color(230, 0, 230));
	//printf("m = %lf\n", m);
	printf("now hor = %d, vert = %d\n\n", hor, vert);
	circle.move(10 * hor, 10 * vert);
	 
	// Отрисовка круга
	window.draw(circle);


	// Отрисовка окна
	window.display();
  }

  return 0;
}