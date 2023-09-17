/* 
*/
// Define Including Guards
#ifndef PATH_H
#define PATH_H

#pragma once                // Guards again multiple includes, overlaps 
#include <string>

using namespace std;

enum CPUStates {
    S_USER = 1,
    S_NICE,
    S_SYSTEM,
    S_IDLE,
    S_IOWAIT,
    S_IRQ,
    S_SOFTIRQ,
    S_STEAL,
    S_GUEST,
    S_GUEST_NICE
};

// Just return the value of paths so we don't have to write them each time
class Path {
    public:
        static string basePath() 
        {
            return "/proc/";
        }
        static string cmdPath()
        {
            return "/cmdline";
        }
        static string statusPath()
        {
            return "/status";
        }
        static string statPath()
        {
            return "stat";
        }
        static string upTimePath()
        {
            return "uptime";
        }
        static string memInfoPath()
        {
            return "meminfo";
        }
        static string versionPath()
        {
            return "version";
        }
};



#endif // PATH_H