#include <SFML/Graphics.hpp>

using namespace sf; // ���������� ������������ ��� sf

int main()
{
  // ������, �������, ����������, �������� ������� ����� ����������
  RenderWindow window(VideoMode(800, 450), "SFML Works!");
	int hor = 0, vert = 0;

  // ������� ���� ����������: �����������, ���� ������� ����
  while (window.isOpen())
  {
	// ������������ ������� ������� � �����
	Event event;
	while (window.pollEvent(event))
	{
	  // ������������ ����� �� �������� � ����� ������� ����?
	  if (event.type == Event::Closed) {
		printf("closing...\n");
		window.close(); // ����� ��������� ���
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
	// ��������� ����� ����
	window.clear(Color(250, 220, 100, 0));

	// ������ ������: ���� �������� 50
	CircleShape circle(50.f);

	// ����������� ��� ���� 
	circle.setFillColor(Color(230, 0, 230));
	//printf("m = %lf\n", m);
	printf("now hor = %d, vert = %d\n\n", hor, vert);
	circle.move(10 * hor, 10 * vert);
	 
	// ��������� �����
	window.draw(circle);


	// ��������� ����
	window.display();
  }

  return 0;
}