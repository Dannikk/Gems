#pragma once
#include "Gem.h"
#include <iostream>

using namespace std;

class Ordinary_Gem : public Gem
{
public:
  void Gem::abstr() override;
  //Ordinary_Gem(const Ordinary_Gem& cop);
};

