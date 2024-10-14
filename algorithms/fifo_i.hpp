#pragma once

#include <vector>
#include <limits>
#include "../models/mAlgorithm.hpp"
#include "../ioManager/ioManager.hpp"

class Fifo_i : private MAlgorithm {

private:

    int extraLife;
    std::vector<int> extraLifeVec;

public:
    Fifo_i(const std::vector<int>& processVec, unsigned int frames) : MAlgorithm(processVec, frames), extraLife(-1), extraLifeVec(processVec.size(), -1){}

    void fifo_i(){
        if(processVec.size() == 0 || frames == 0) return;

        memoryVec[0].emplace_back(processVec[0]);
        for(int i=1; i<memoryVec.size(); i++){
            addProcess(i,processVec[i]);
            extraLifeVec[i] = extraLife;
        }
        IoManager::print(memoryVec,processVec, extraLifeVec,frames, fails);
    }


private:

    void addProcess(unsigned int memoryPos, int process){
        memoryVec[memoryPos] = memoryVec[memoryPos-1];
        if(isInMemory(memoryPos, process)) return;
        fails++;
        if(memoryVec[memoryPos].size()<frames){
            memoryVec[memoryPos].emplace_back(process);
            return;
        }
        memoryVec[memoryPos][firstIn(memoryPos)] = process;
    }

    bool isInMemory(const unsigned int memoryPos, int process) {
        for(int i=0; i<memoryVec[memoryPos].size(); i++){
            if(memoryVec[memoryPos][i] == process){
                extraLife = i;
                return true;
            }
        }
        return false;
    }

    unsigned int firstIn(unsigned int memoryPos){
        std::vector<unsigned int> inTime(frames, std::numeric_limits<unsigned int>::max());
        for(int i=0;i<frames;i++){
            for(int j=memoryPos;j>=0; j--){
                if(i >= memoryVec[j].size() || memoryVec[memoryPos][i] != memoryVec[j][i]){
                    inTime[i] = memoryPos-j;
                    break;
                }
            }
        }
        int pos = 0;
        unsigned int value = 0;
        for(int i = 0; i<frames; i++){
            if(inTime[i] > value){
                value = inTime[i];
                pos = i;
            }
        }
        if(extraLife != pos) return pos;
        extraLife = -1;
        inTime[pos] = 0;
        pos=0;
        value=0;
        for(int i = 0; i<frames; i++){
            if(inTime[i] > value){
                value = inTime[i];
                pos = i;
            }
        }
        return pos;
    }

};

