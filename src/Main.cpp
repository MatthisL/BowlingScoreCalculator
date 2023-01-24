#include <iostream>
#include <sstream>

#include "Main.h"
#include "FrameScore.h"
#include "Globals.h"

int main(int argc, char* argv[])
{
    // Print welcome message and instructions.
    std::cout << "Welcome to the American Ten-Pin Bowling Score Calculator.\n";
    std::cout << "Usage for input : \n";
    std::cout << "  - \"X\" indicates a strike,\n";
    std::cout << "  - \"/\" indicates a spare,\n";
    std::cout << "  - \"-\" indicates a miss\n";
    std::cout << "  - Use a space to separate each frame\"s score.\n";
    std::cout << "  - Type \"exit\" to quit.\n";
    std::cout << "Examples :\n";
    std::cout << "  - \"X X X X X X X X X X X X\" => indicates (12 rolls: 12 strikes)\n";
    std::cout << "  - \"9- 9- 9- 9- 9- 9- 9- 9- 9- 9-\"  => indicates (20 rolls: 10 pairs of 9 and miss)\n";
    std::cout << "  - \"5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/5\" => indicates (21 rolls: 10 pairs of 5 and spare, with a final 5)\n";

    // Ask for input and register it.
    std::cout << "Please enter an input for the score of the frames of a line of bowling : ";

    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input == "exit")
            return 0;
        
        // Start the computation.
        int lineScore = ComputeScore(input);

        // Show result.
        std::cout << "Bowling Line Score : " << lineScore << "\n";

        // Ask for another input.
        std::cout << "Please enter an input for the score of the frames of a line of bowling : ";
    }

    // Everything went right, exit process with success code.
    return 0;
}

/**
 * Try to compute the score of a line of bowling.
 * @param framesInput A string containing the input of all the frames of the line.
 * @return The computed score for the given line.
 */
int ComputeScore(std::string const &framesInput)
{
    // First, parse the frames score into a vector to separate them.
    std::vector<std::string> parsedFramesScore;
    SplitFramesInput(framesInput, frameScoreDelimitation, parsedFramesScore);

    // Secondly, create each frame for this bowling line.
    std::vector<FrameScore> bowlingLine;
    for (auto it = std::begin(parsedFramesScore); it != end(parsedFramesScore); ++it)
    {
        std::string frame = it->data();
        
        // Check validity.
        if (frame.empty() || frame.length() > 3)
            continue;
        
        switch (frame.length())
        {
        case 1:
            bowlingLine.emplace_back(FrameScore(frame[0]));
            break;
        case 2:
            bowlingLine.emplace_back(FrameScore(frame[0], frame[1]));
            break;
        case 3:
            bowlingLine.emplace_back(FrameScore(frame[0], frame[1], frame[2]));
            break;
        default:
            std::cout << "Invalid Frame Input\n";
            break;
        }
    }

    // Finally, apply strike/spare bonuses and compute total.
    int lineScore = 0;    
    for (auto it = std::begin(bowlingLine); it != end(bowlingLine); ++it)
    {
        int frameIndex = it - bowlingLine.begin();
        
        if (it->IsStrike && frameIndex < NumberOfFrame - 1) // Don't apply bonus for last frame.
        {
            auto nextFrame = it + 1;
            it->Bonus += nextFrame->GetFrameScore();
            if (nextFrame->IsStrike)
                it->Bonus += (nextFrame + 1)->Roll1;
        }

        if (it->IsSpare && frameIndex < NumberOfFrame - 1) // Don't apply bonus for last frame.
        {
            auto nextFrame = it + 1;
            it->Bonus += nextFrame->Roll1;
        }

        lineScore += it->GetFrameScore();
    }
        
    return lineScore;
}

/**
 * Take the string containing the frames score of the line of bowling and split them into a vector.
 * @param framesInput The string containing the frames input.
 * @param delim The char delimiting each frame score.
 * @param out The container reference receiving the split frames score. 
 */
void SplitFramesInput(std::string const &framesInput, const char delim, std::vector<std::string> &out)
{
    // Construct a stream from the string.
    std::stringstream ss(framesInput);

    // Split string with delim and add each substring in the out vector.
    std::string row;
    while (std::getline(ss, row, delim))
    {
        out.push_back(row);
    }
}
