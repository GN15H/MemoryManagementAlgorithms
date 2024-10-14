#pragma once

#include <vector>

class MAlgorithm {
protected:
    const std::vector<int>& processVec;
    const unsigned int frames;
    std::vector<std::vector<int>> memoryVec;
    unsigned int fails;

public:
    MAlgorithm(const std::vector<int>& processVec, unsigned int frames): processVec(processVec), frames(frames), fails(1){
        memoryVec = std::vector<std::vector<int>>(processVec.size());
    }

    void printVector(const std::vector<int> vec){
        for(int x: vec){
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
    }

protected: 
    bool isInMemory(const unsigned int memoryPos, int process) const {
        for(int p: memoryVec[memoryPos]){
            if(p == process) return true;
        }
        return false;
    }
};