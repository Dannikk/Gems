// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Field.h"

Field::Field()
{
  //this->gems(ARRAY_SIZE);
  //this->gems = new Ordinary_Gem [ARRAY_SIZE];
  //Gem* tempptr;
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    //tempptr = new Ordinary_Gem();
    this->gems.push_back((Gem*)new Ordinary_Gem());
    //this->gems.push_back(make_shared<Ordinary_Gem>());
  }
  numberHLGems = 0;
  hLightGem = 0;
  seriesSize = 1;
}

void Field::fieldInit()
{
  ////this->gems(ARRAY_SIZE);
  ////this->gems = new Ordinary_Gem [ARRAY_SIZE];
  ////Gem* tempptr;
  //for (unsigned short int i = 0; i < ARRAY_SIZE; i++) 
  //{
  //  //tempptr = new Ordinary_Gem();
  //  this->gems.push_back((Gem*)new Ordinary_Gem());
  //  //this->gems.push_back(make_shared<Ordinary_Gem>());
  //}
  //numberHLGems = 0;
  //hLightGem = 0;
}

void Field::drawField(sf::RenderWindow& window)
{
  //cout << "drawing all gems" << endl;
  for (unsigned int i = 0; i < ARRAY_SIZE; i++)
  {
    // Вычисление позиции плашки для отрисовки
    sf::Vector2f position(i % my_SIZE * CELL_SIZE + LEFT_INDENT, i / my_SIZE * CELL_SIZE + UP_INDENT);
    if (gems[i] != NULL)
    {
      gems[i]->drawGem(window, position);
    }
  }
}

void Field::handleMouseClick(sf::Vector2i pos)
{
  unsigned short int number, x = pos.x, y = pos.y;
  number = (x - LEFT_INDENT) / CELL_SIZE + (y - UP_INDENT) / CELL_SIZE * my_SIZE;

  switch (this->numberHLGems) {
  case 0:				  //NO gem is highlighted
    //printf("num of gem = %hu\n", number);
    gems[number]->chooseGem();
    this->numberHLGems++;
    printf("flag = %hu\n", number);
    hLightGem = number;
    break;
  case 1:						  //Only 1(one) gem is highlighted
    if (isItNeighbour(number)) {	  //New gem is neighbour of previous one
      //printf("num of gem = %hu\n", number);
      this->numberHLGems = 0;
      gems[number]->chooseGem();			
      //printf("flag = %hu\n", highlighted_gems);

      //Swap number and hlightgem gems
      //printf("Swap for number = %hu and hlightgem = %hu\n", number, hlightgem);
      swapGems(this->gems[number], this->gems[hLightGem]);
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

void Field::swapGems(Gem* a, Gem* b)
{
  //easy swap
  //only position swap, without animation

  gemColor temp = a->color;

  //Gem* tmp = this->gems[a];

  //printf("Swap: %d color = %hu, %d color = %hu\n", a, this->gems[a]->color, b, this->gems[b]->color);
  //printf("Swap: %d color = %hu, %d color = %hu\n", a, a->color, b, b->color);
  //gemColor temp = a.color;

  a->setColor(b->color);
  b->setColor(temp);

  //printf("(swapGems)Now gem[%d] = %d, gem[%d] = %d\n", a, this->gems[a]->color, b, this->gems[b]->color);
  //swap(this->gems[a], this->gems[b]);
  //swap(*(Ordinary_Gem*)a, *(Ordinary_Gem*)b);
  //tmp = this->gems[a];
  //this->gems[a] = this->gems[b];
  //this->gems[b] = (Ordinary_Gem*)tmp;

  //printf("(swapGems)But now gem[%d] = %d, gem[%d] = %d\n", a, this->gems[a]->color, b, this->gems[b]->color);
  
  /*a.unchooseGem();
  a.flag = false;
  b.unchooseGem();
  b.flag = false;*/

  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    gems[i]->unchooseGem();
    gems[i]->flag = 0;
  }

}

void Field::shiftUpperGems(sf::RenderWindow& window, vector<int>& gems2shift, vector<int>& streak, unsigned short int& height)
{
  //unsigned short int height;
  unsigned short int shiftSize = 1;             // Useless variable
  short int j = 0;
  //suppose that gems2shift.size() != 0

  //define height of streak
  //height = defineHeightOfStreak(streak);

  //define shiftSize for vector<int> gems2shift
  if (height <= my_SIZE)
    shiftSize = height * CELL_SIZE / ANIMATION_SPEED;

  printf("Let's shift upper gems by %hu pixels, height = %hu\n", shiftSize, height);
  for (unsigned short int j = 0; j < shiftSize; j++) 
  {
    window.clear();

    for (unsigned short int i = 0; i < gems2shift.size(); i++)
    {
      //Shift all gems besides gems from streak by dy untill 
      //move
      gems[gems2shift[i]]->shape.move(0.f, ANIMATION_SPEED);
      
    }

    //cout << "move number = " << j << endl;
    for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
    {
      if (gems[i] != NULL)
      {
        gems[i]->drawGem(window);
      }
      else
      {
        //cout << "(shiftUpperGems) NULL = " << i << endl;
      }
    }

    window.display();
  }

  //streak.clear();
  cout << "__Animation has stopped" << endl;
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    if (gems[i] == NULL)
      cout << "And these gems are NULL " << i << endl;
  }
  //
  //Sleep(5000);
  //Shift pointers

  shiftPointers(height, streak);

  cout << "__After shiftPointers" << endl;
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    if (gems[i] == NULL)
      cout << "And these gems are NULL " << i << endl;
  }
  //
  //Sleep(5000);
  
}

vector<int> Field::findStreak()
{
  gemColor nextc, currc;
  //unsigned short int strike = 0;
  vector<int> streak_gems;
  //
  //find horizontal streak
  //
  for (unsigned short int i = 0; i < my_SIZE; i++) 
  {
    this->seriesSize = 1;
    for (unsigned short int j = 0; j < my_SIZE - 1; j++)
    {
      currc = gems[i * my_SIZE + j]->color;
      nextc = gems[i * my_SIZE + j + 1]->color;
      streak_gems.push_back(i * my_SIZE + j);

      if (nextc == currc) {
        this->seriesSize++;
        streak_gems.push_back(i * my_SIZE + j + 1);
      }
      else {
        if (this->seriesSize < 3) {
          streak_gems.clear();
          this->seriesSize = 1;
        }
        else {
          streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
          return streak_gems;
        }
      }
    }
    if (this->seriesSize >= 3) {
      streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
      return streak_gems;
    }
    else
      streak_gems.clear();
  }
  streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
  //
  //find vertical streak
  //
  if (streak_gems.size() == 0) {
    for (unsigned short int j = 0; j < my_SIZE; j++)
    {
      this->seriesSize = 1;
      for (unsigned short int i = 0; i < my_SIZE - 1; i++)
      {
        currc = gems[i * my_SIZE + j]->color;
        nextc = gems[(i + 1) * my_SIZE + j]->color;
        streak_gems.push_back(i * my_SIZE + j);

        if (nextc == currc) {
          this->seriesSize++;
          streak_gems.push_back((i + 1) * my_SIZE + j);
        }
        else {
          if (this->seriesSize < 3) {
            streak_gems.clear();
            this->seriesSize = 1;
          }
          else {
            streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
            return streak_gems;
          }
        }
      }
      if (this->seriesSize >= 3) {
        streak_gems.erase(std::unique(streak_gems.begin(), streak_gems.end()), streak_gems.end());
        return streak_gems;
      }
      else
        streak_gems.clear();
      }
    }
  return streak_gems;
}

void Field::destroyGemStreak(sf::RenderWindow& window, vector<int>& streak) 
{
  vector<int> gems2shift;
  unsigned short int height = defineHeightOfStreak(streak);

  if (streak.size() > 0) {
    short int j;
    //
    //destroying horizontal gems 
    //
    if (height == 1) {
      for (int i = 0; i < streak.size(); i++)
      {
        j = streak[i];
        gems[j]->makeGemInvisible();
        cout << "~ " << j;
        //window.clear();
        //gems[j]->chooseGem();
        //window.draw(gems[j]->shape);
        //window.display();
        //Sleep(1000);
        //

        gems[j]->~Gem();
        gems[j] = NULL;
        j = j - my_SIZE;
        //define gems2shift
        while (j >= 0)
        {
          gems2shift.push_back(j);
          j = j - my_SIZE;
        }
      }
    }
    //
    //destroying vertical gems
    //
    if (height > 1) {
      j = streak[0] - my_SIZE;
      //define gems2shift
      while (j >= 0)
      {
        gems2shift.push_back(j);
        j = j - my_SIZE;
      }
      for (int i = 0; i < streak.size(); i++)
      {
        j = streak[i];
        //gems[j]->makeGemInvisible();
        //

        gems[j]->~Gem();
        gems[j] = NULL;
      }
    }

    if (gems2shift.size() > 0)
    {
      printf("gems2shift: ");
      for (int i = 0; i < gems2shift.size(); i++)
        printf("%i ", gems2shift[i]);
      printf("\n");
      //Sleep(5000);
      shiftUpperGems(window, gems2shift, streak, height);
    }
    else
    {
      
    }
    generateNewGems(window);
    streak.clear();

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
    return (unsigned short int)streak.size();
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

void Field::generateNewGems(sf::RenderWindow& window)
{
  //necessary add animation
  vector<int> ngems;
  sf::Vector2f newpos;
  float rad = 50.f;
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    if (gems[i] == NULL)
    {
      this->gems[i] = (Gem*)new Ordinary_Gem();
      ngems.push_back(i);
      cout << "(generateNewGems) these gems was NULL " << i << endl;
    }
  }
  
  // animation
  for (unsigned short int k = 5; k >=1; k--)
  {
    cout << "scaling" << endl;
    for (unsigned short int i = 0; i < ngems.size(); i++)
    {
      gems[ngems[i]]->shape.setScale(1.f / k, 1.f / k);
    }
    cout << "drawing" << endl;
    window.clear();
    for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
    {
      if (gems[i] != NULL)
      {
        newpos.x = i % my_SIZE * CELL_SIZE + LEFT_INDENT;
        newpos.y = i / my_SIZE * CELL_SIZE + UP_INDENT;
        gems[i]->drawGem(window, newpos);
      }
      else
      {
        cout << "!!!(shiftUpperGems) NULL = " << i << endl;
      }
      
    }
    Sleep(100);
    window.display();
  }

    
    
}

void Field::shiftPointers(unsigned short int& height, vector<int>& streak)
{
  //unsigned short int height = defineHeightOfStreak(streak);
  short int j;

  if (height == 1) 
  {
    for (unsigned short int i = 0; i < streak.size(); i++)
    {
      j = streak[i];

      while (j >= my_SIZE)
      {
        this->gems[j] = this->gems[j - my_SIZE];
        j -= my_SIZE;
      }

      //NUUL upper gems
      cout << "NULL these gems " << streak[i] % my_SIZE << endl;
      this->gems[streak[i] % my_SIZE] = NULL;
    }
  }
  //
  //for height > 1
  cout << "__in shiftPointers" << endl;
  for (unsigned short int i = 0; i < ARRAY_SIZE; i++)
  {
    if (gems[i] == NULL)
      cout << "And these gems are NULL " << i << endl;
  }
  //
  //Sleep(5000);


  if (height > 1)
  {
    short int top = streak[0] % my_SIZE;
    j = streak[0] - my_SIZE;                      //gems over streak
    short int i = streak[height - 1];             //last in streak
    while (j >= 0)
    {
      gems[i] = gems[j];
      i -= my_SIZE;
      j -= my_SIZE;
    }
    
    for (unsigned short int k = 0; k < height; k++)
    {
      gems[top] = NULL;
      cout << "zanulyaem vot eti gems " << top << endl;
      top += my_SIZE;
    }

    /*for (unsigned short int i = height - 1; i >= 0; i--)
    {
      if (j >= 0)
      {
        gems[streak[i]] = gems[j];
        j -= my_SIZE;
      }
      else
      {
        cout << "break forcycle because j = " << j << endl;
        break;
      }
    }*/

    /*while (j >= 0)
    {
      gems[j] = NULL;
      j -= my_SIZE;
    }*/
  }
}
