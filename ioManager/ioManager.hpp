#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class IoManager
{
public:
    static void readProcesses(std::vector<int> &processVec){
        std::ifstream inputFile("procesos.txt"); 
        if (!inputFile){
            std::cerr << "Error abriendo archivo." << std::endl;
            return;
        }
        int num;
        while (inputFile >> num) processVec.emplace_back(num);
        inputFile.close();
    }

    static void print(const std::vector<std::vector<int>> &memoryVec, const std::vector<int> &processVec, unsigned int frames, unsigned int fails){
        if (processVec.size() == 0)
            return;
        printProcessVec(processVec);
        printInputFails(memoryVec, frames);
        for (int i = 0; i < frames; i++){
            for (int j = 0; j < memoryVec.size(); j++){
                if (i >= memoryVec[j].size())
                    std::cout << "   ";
                else
                    std::cout << memoryVec[j][i] << "  ";
            }
            std::cout << "\n";
        }
        printOutputFails(memoryVec, frames);
        std::cout << "Cantidad de fallos: " << fails <<"\n"<<std::endl;
    }

    static void print(const std::vector<std::vector<int>> &memoryVec, const std::vector<int> &processVec, const std::vector<int>& extraLifeVec ,unsigned int frames, unsigned int fails){
        if (processVec.size() == 0)
            return;
        printProcessVec(processVec);
        printInputFails(memoryVec, frames);
        for (int i = 0; i < frames; i++){
            for (int j = 0; j < memoryVec.size(); j++){
                if (i >= memoryVec[j].size())
                    std::cout << "   ";
                else
                    std::cout << memoryVec[j][i] << (extraLifeVec[j] == i ? "* " : "  ");
            }
            std::cout << "\n";
        }
        printOutputFails(memoryVec, frames);
        std::cout << "Cantidad de fallos: " << fails <<"\n"<<std::endl;
    }

private:
    static void printProcessVec(const std::vector<int> &processVec){
        for (int process : processVec) std::cout << process << "  ";
        std::cout << "\n";
    }

    static void printInputFails(const std::vector<std::vector<int>> &memoryVec, unsigned int frames){
        int i = 0;
        //for (; i < frames; i++) std::cout << "|  ";
        for (; i < memoryVec.size(); i++) if (memoryVec[i] != memoryVec[i - 1]) std::cout << "|  "; else std::cout << "   ";
        std::cout << "\n";
        i = 0;
        //for (; i < frames; i++) std::cout << "v  "; 
        for (; i < memoryVec.size(); i++) if (memoryVec[i] != memoryVec[i - 1]) std::cout << "v  "; else std::cout << "   ";
        std::cout << "\n";
    }

    static void printOutputFails(const std::vector<std::vector<int>> &memoryVec, unsigned int frames){
        int i = 0;
        for (; i < frames; i++) std::cout << "   ";
        for (; i < memoryVec.size(); i++) if (memoryVec[i] != memoryVec[i - 1]) std::cout << "|  "; else std::cout << "   ";
        std::cout << "\n";
        i = 0;
        for (; i < frames; i++) std::cout << "   ";
        for (; i < memoryVec.size(); i++) if (memoryVec[i] != memoryVec[i - 1]) std::cout << "v  "; else std::cout << "   ";
        std::cout << "\n";
        i = 0;
        for (; i < frames; i++) std::cout << "   "; 
        for (; i < memoryVec.size(); i++) if (memoryVec[i] != memoryVec[i - 1]) std::cout << memoryVec[i - 1][indexDifference(memoryVec, i, frames)] << "  "; else std::cout << "   ";
        std::cout << "\n";
    }

    static unsigned int indexDifference(const std::vector<std::vector<int>> &memoryVec, unsigned int memoryPos, unsigned int frames){
        for (int i = 0; i < frames; i++)
            if (memoryVec[memoryPos - 1][i] != memoryVec[memoryPos][i])
                return i;
        return 0;
    }
};