#include "Field.h"

Field::Field()
{
  fieldInit();
}

void Field::fieldInit()
{
  //this->gems(ARRAY_SIZE);

  this->gems = new Ordinary_Gem [ARRAY_SIZE];
  /*Ordinary_Gem *tempptr;
  printf("\nsize = %d\n", gems.size());
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++) 
  {
    tempptr = &Ordinary_Gem();
    this->gems.push_back(tempptr);
  }*/


  numberHLGems = 0;
  hLightGem = 0;
}

void Field::drawField(sf::RenderWindow& window)
{
  printf("Lets draw all gems\n");

  for (unsigned int i = 0; i < ARRAY_SIZE; i++)
  {
    printf("now %hu gem\n", i);
    // Вычисление позиции плашки для отрисовки
    sf::Vector2f position(i % my_SIZE * CELL_SIZE + LEFT_INDENT, i / my_SIZE * CELL_SIZE + UP_INDENT);
    printf("%lf %lf\n", position.x, position.y);

    gems[i].drawGem(window, position);
  }
}

void Field::handleMouseClick(sf::Vector2i pos)
{
  unsigned short int number, x = pos.x, y = pos.y;
  number = (x - LEFT_INDENT) / CELL_SIZE + (y - UP_INDENT) / CELL_SIZE * my_SIZE;

  switch (numberHLGems) {
  case 0:				  //NO gem is highlighted
    //printf("num of gem = %hu\n", number);
    gems[number].chooseGem();
    numberHLGems++;
    //printf("flag = %hu\n", highlighted_gems);
    hLightGem = number;
    break;
  case 1:						  //Only 1(one) gem is highlighted
    if (isItNeighbour(number)) {	  //New gem is neighbour of previous one
      //printf("num of gem = %hu\n", number);
      numberHLGems = 0;
      gems[number].chooseGem();			
      //printf("flag = %hu\n", highlighted_gems);

      //Swap number and hlightgem gems
      //printf("Swap for number = %hu and hlightgem = %hu\n", number, hlightgem);
      swapGems(gems[number], gems[hLightGem]);
    }
    else {						  //New gem is NOT neighbour of previous one
      //

    }
    break;
  default:
    break;
  }

 // if (flag < 2) {
    //if (flag == 1 && IsItNeighbor(number)) {
    //  printf("num of gem = %hu\n", number);
    //  gems[number].Choose();
    //  flag = 0;
    //  printf("flag = %hu\n", flag);
    //  
    //  //Swap number and hlightgem gems
    //  printf("Swap for number = %hu and hlightgem = %hu\n", number, hlightgem);
    //  SwapGems(gems[number], gems[hlightgem]);
    //}
    //else {
    //  flag = 0;
    //  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
    //  {
    //	gems[i].Unchoose();
    //	gems[i].flag = 0;
    //  }
    //}
    //if (flag == 0) {
    //  printf("num of gem = %hu\n", number);
    //  gems[number].Choose();
    //  flag++;
    //  printf("flag = %hu\n", flag);
    //  hlightgem = number;
    //}
 // }

}

bool Field::isItNeighbour(short int neigbour)
{

  if (neigbour - my_SIZE == hLightGem || neigbour + my_SIZE == hLightGem)
    return true;
  if (neigbour - 1 == hLightGem || neigbour + 1 == hLightGem)
    return true;

  return false;
}

void Field::swapGems(Gem& a, Gem& b)
{
  //easy swap
  //only position swap, without animation

  printf("Swap: 1 color = %hu, 2 color = %hu\n", a.color, b.color);
  gemColor temp = a.color;

  a.setColor(b.color);
  b.setColor(temp);

  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    gems[i].unchooseGem();
    //gems[i].flag = 0;
  }

}

void Field::shiftUpperGems(sf::RenderWindow& window, vector<int> gems2shift, vector<int> streak)
{
  unsigned short int height;
  unsigned short int speed = 1;               //must be float type
  unsigned short int shiftSize = 1;

  //suppose that gems2shift.size() != 0

  //define height of streak
  height = defineHeightOfStreak(streak);

  //define shiftSize for vector<int> gems2shift
  if (height <= my_SIZE)
    shiftSize = height * CELL_SIZE / speed;

  printf("Let's shift upper gems by %hu pixels\n", shiftSize);
  for (unsigned short int j = 0; j < shiftSize; j++) 
  {
    window.clear();

    for (unsigned short int i = 0; i < gems2shift.size(); i++)
    {
      //Shift all gems besides gems from streak by dy untill 
      //move
      gems[gems2shift[i]].shape.move(0.f, speed);
      //set position
      //gems[i].shape.setPosition();
    }

    for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
    {
      gems[i].drawGem(window);
    }

    window.display();
  }
  printf("Animation has stopped\n");
  Sleep(5000);
}

vector<int> Field::findStreak()
{
  gemColor nextc, currc;
  unsigned short int strike = 0;

  vector<int> streak_gems;

  seriesSize = 1;
  for (unsigned short int i = 0; i < my_SIZE; i++) 
  {
    seriesSize = 1;
    for (unsigned short int j = 0; j < my_SIZE - 1; j++)
    {
      currc = gems[i * my_SIZE + j].color;
      nextc = gems[i * my_SIZE + j + 1].color;
      streak_gems.push_back(i * my_SIZE + j);

      if (nextc == currc) {
        seriesSize++;
        streak_gems.push_back(i * my_SIZE + j + 1);
      }
      else {
        if (seriesSize < 3) {
          streak_gems.clear();
          seriesSize = 1;
        }
        else {
          streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
          return streak_gems;
        }
      }
     // if (j != 0)									  //Selected gem is NOT first in row
     // {												  //
        //prevc = gems[i * SIZE + j - 1].color;		  //
        //if (prevc == currc)							  //Colors of previous and current gems identical
        //{											  //
        //  series_size++;							  //Increase series size
        //  //add both gems 2 array
        //  streak_gems.push_back(i * SIZE + j - 1);
        //  streak_gems.push_back(i * SIZE + j);
        //  //printf("ss++\n");
        //}											  
        //else										  
        //{											  
        //  if (series_size >= 2) {
        //	//add gem 2 array
        //	printf("__Series size %hu__\n", series_size);
        //	streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
        //	return streak_gems;
        //  }
        //  else
        //  {
        //	streak_gems.clear();
        //	series_size = 0;							  //Reset the series
        //  }
        //}
     // }
    }
    if (seriesSize >= 3) {
      streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
      return streak_gems;
    }
    else
      streak_gems.clear();
  }
  streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
  return streak_gems;
}

void Field::destroyGemStreak(sf::RenderWindow& window, vector<int> streak) 
{
  vector<int> gems2shift;
  if (streak.size() > 0) {
    short int j;
    //printf("Streak is: ");
    for (int i = 0; i < streak.size(); i++) 
    {
      j = streak[i];
      //printf("invis %d ", j);
      gems[j].makeGemInvisible();
      j = j - my_SIZE;
      while (j >= 0)
      {
        gems2shift.push_back(j);
        j = j - my_SIZE;
      }
    }
    //printf("\n");
    //streak.clear();
  }
  
  if (gems2shift.size() > 0)
  {
    printf("gems2shift: ");
    for (int i = 0; i < gems2shift.size(); i++)
      printf("%i ", gems2shift[i]);
    printf("\n");
    shiftUpperGems(window, gems2shift, streak);
  }
    
}

unsigned short int Field::defineHeightOfStreak(vector<int> streak)
{
  //unsigned short int height = 1;
  if (defineOrientOfStreak(streak) == true)
  {
    return 1;
  }
  else
  {
    return streak.size();
  }
}

bool Field::defineOrientOfStreak(vector<int> streak)
{
  //return true, if streak is horizontal
  for (unsigned short int i = 0; i < streak.size() - 1; i++) 
  {
    if (streak[i + 1] - streak[i] == 1)
      continue;
    else
      return false;
  }
  //return false, if streak is not horizontal
  return true;
}
