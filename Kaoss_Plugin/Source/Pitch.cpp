/*
  ==============================================================================

    Pitch.cpp
    Created: 15 Dec 2021 8:55:31pm
    Author:  ClarVik

  ==============================================================================
*/

#include "Pitch.h"

void Pitch::updateParams(int x, int y)
{
    if (y == 0) {
        mpProcessor1->setPitchSemiTones(0);
        mpProcessor2->setPitchSemiTones(0);
    }
    else {
        mpProcessor1->setPitchSemiTones((float)(-12 + (x / 100.) * 24));
        mpProcessor2->setPitchSemiTones((float)(-12 + (x / 100.) * 24));
    }
}

