#pragma once

#include <string>
#include <vector>

int ComputeScore(std::string const &framesScore);
void SplitFramesInput(std::string const &framesScore, const char delim, std::vector<std::string> &out);
