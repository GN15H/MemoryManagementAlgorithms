#pragma once

#include <vector>
#include <limits>
#include "../models/mAlgorithm.hpp"
#include "../ioManager/ioManager.hpp"

class Optimal : private MAlgorithm {

private:

public:
    Optimal(const std::vector<int>& processVec, unsigned int frames) : MAlgorithm(processVec, frames){}

    void optimal(){
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
        if(memoryPos<frames){
            memoryVec[memoryPos].emplace_back(process);
            return;
        }
        memoryVec[memoryPos][leastUsedBeforehand(memoryPos)] = process;
    }


    unsigned int leastUsedBeforehand(unsigned int memoryPos){
        std::vector<unsigned int> futureUsage(frames, std::numeric_limits<unsigned int>::max());
        for(int i=0;i<frames;i++){
            for(int j=memoryPos;j<processVec.size(); j++){
                if(memoryVec[memoryPos][i] == processVec[j]){
                    futureUsage[i] = j;
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

