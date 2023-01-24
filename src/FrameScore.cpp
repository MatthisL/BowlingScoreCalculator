#include "FrameScore.h"

#include "Globals.h"

FrameScore::FrameScore(char roll1Input)
{
    Roll1 = 0;
    Roll2 = 0;
    Bonus = 0;
    IsStrike = false;
    IsSpare = false;

    if (roll1Input == strikeToken)
    {
        Roll1 = 10;
        IsStrike = true;
    }
}

FrameScore::FrameScore(char roll1Input, char roll2Input)
{
    Roll1 = 0;
    Roll2 = 0;
    Bonus = 0;
    IsStrike = false;
    IsSpare = false;

    if (roll1Input != missToken)
    {
        Roll1 = roll1Input - '0';
    }
        
    if (roll2Input == spareToken)
    {
        Roll2 = 10 - Roll1;
        IsSpare = true;
    }
    else if (roll2Input != missToken)
    {
        Roll2 = roll2Input - '0';
    }
}

FrameScore::FrameScore(char roll1Input, char roll2Input, char roll3Input)
{
    Roll1 = 0;
    Roll2 = 0;
    Bonus = 0;
    IsStrike = false;
    IsSpare = false;
        
    if (roll1Input != missToken)
    {
        Roll1 = roll1Input - '0';
    }
        
    if (roll2Input == spareToken)
    {
        Roll2 = 10 - Roll1;
    }
    else if (roll2Input != missToken)
    {
        Roll2 = roll2Input - '0';
    }

    // Last roll, can be strike or spare. Applied as bonus.
    switch (roll3Input)
    {
    case strikeToken:
        Bonus = 10;
        break;
    case spareToken:
        Bonus = 10 - Roll2;
        break;
    case missToken:
        Bonus = 0;
        break;
    default:
        Bonus = roll3Input - '0';
        break;
    }
}

int FrameScore::GetFrameScore()
{
    return Roll1 + Roll2 + Bonus;
}
