#ifndef UTIL_H
#define UTIL_H

#pragma once
#include <string>
#include <fstream>

using namespace std;

class Util{
    public:
        std::string convertToTime(long int input_seconds);
        std::string getProgressBar(std::string percent);
        std::ifstream getStream(std::string path);
};


std::string Util::convertToTime(long int input_seconds){


}

std::string Util::getProgressBar(std::string percent){


}

std::ifstream Util::getStream(std::string path){


}













#endif