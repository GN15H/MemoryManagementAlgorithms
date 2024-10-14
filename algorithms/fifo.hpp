#pragma once

#include <vector>
#include <limits>
#include "../models/mAlgorithm.hpp"
#include "../ioManager/ioManager.hpp"

class Fifo : protected MAlgorithm {

protected:
    int count;

public:
    Fifo(const std::vector<int>& processVec, unsigned int frames) : MAlgorithm(processVec, frames), count(0){}

    void fifo(){
        if(processVec.size() == 0 || frames == 0) return;
        std::cout<<"aver "<<memoryVec[0].size()<<" aver 2 "<<memoryVec[1].size();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        memoryVec[0].emplace_back(processVec[0]);
        for(int i=1; i<memoryVec.size(); i++){
            addProcess(i,processVec[i]);
        }
        IoManager::print(memoryVec,processVec, frames, fails);
    }


protected:
    void addCount(unsigned int amount){
        count = (count + amount) % frames;
    }

    void addProcess(unsigned int memoryPos, int process){
        memoryVec[memoryPos] = memoryVec[memoryPos-1];
        if(MAlgorithm::isInMemory(memoryPos, process)) return;
        fails++;
        if(memoryVec[memoryPos].size()<frames){
            memoryVec[memoryPos].emplace_back(process);
            return;
        }
        memoryVec[memoryPos][count] = process;
        addCount(1);
    }

};

