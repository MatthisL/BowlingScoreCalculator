#pragma once

/**
 * Struct containing data about a frame in a bowling line.
 */
struct FrameScore
{
    // Constructor for a strike frame.
    FrameScore(char roll1Input);
    // Constructor for a regular frame.
    FrameScore(char roll1Input, char roll2Input);
    // Constructor for a last frame (if spare or strike).
    FrameScore(char roll1Input, char roll2Input, char roll3Input);

    // The number of pin hit in the first roll.
    int Roll1;
    // The number of pin hit in the second roll.
    int Roll2;
    // The bonus for this frame (strike, spare, or third bonus roll at the 10th frame).
    int Bonus;

    // Is this frame scores a strike ?
    bool IsStrike;
    // Is this frame scores a spare ?    
    bool IsSpare;

    int GetFrameScore();
};

