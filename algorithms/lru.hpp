#pragma once

#include <vector>
#include <limits>
#include "../models/mAlgorithm.hpp"
#include "../ioManager/ioManager.hpp"

class LRU : private MAlgorithm {

private:

public:
    LRU(const std::vector<int>& processVec, unsigned int frames) : MAlgorithm(processVec, frames){}

    void lru(){
        if(processVec.size() == 0 || frames == 0) return;

        memoryVec[0].emplace_back(processVec[0]);
        for(int i=1; i<memoryVec.size(); i++){
            addProcess(i,processVec[i]);
        }
        IoManager::print(memoryVec,processVec, frames, fails);
    }


private:

    void addProcess(unsigned int memoryPos, int process){
        memoryVec[memoryPos] = memoryVec[memoryPos-1];
        if(MAlgorithm::isInMemory(memoryPos, process)) return;
        fails++;
        if(memoryVec[memoryPos].size()<frames){
            memoryVec[memoryPos].emplace_back(process);
            return;
        }
        memoryVec[memoryPos][leastRecentlyUsed(memoryPos)] = process;
    }


    unsigned int leastRecentlyUsed(unsigned int memoryPos){
        std::vector<unsigned int> futureUsage(frames, 0);
        for(int i=0;i<frames;i++){
            for(int j=memoryPos;j>=0; j--){
                if(memoryVec[memoryPos][i] == processVec[j]){
                    futureUsage[i] = memoryPos-j;
                    break;
                }
            }
        }
        int pos = 0;
        unsigned int value = 0;
        for(int i = 0; i<frames; i++){
            if(futureUsage[i] > value){
                value = futureUsage[i];
                pos = i;
            }
        }
        return pos;
    }


};

