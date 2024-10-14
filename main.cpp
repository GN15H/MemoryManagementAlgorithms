#include <vector>
#include <iostream>
#include <fstream>
#include "algorithms/optimal.hpp"
#include "algorithms/fifo.hpp"
#include "algorithms/lru.hpp"
#include "algorithms/fifo_i.hpp"
#include "models/algorithmsEnum.h"

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  // Windows
    #elif defined(__linux__)
        system("clear");  // Linux
    #elif defined(__APPLE__) || defined(__MACH__)
        system("clear");  // macOS
    #else
        std::cout << "OS not supported." << std::endl;
    #endif
}

void selectAlgorithm(const unsigned int choice){
    std::vector<int> processVec;
    IoManager::readProcesses(processVec);
    unsigned int frames=0;
    std::cout<<"Ingrese la cantidad de marcos ";
    std::cin>>frames;
    std::cout<<std::endl;
    switch (choice){
        case optimal:{
            Optimal opt(processVec,frames);
            opt.optimal();
        break;
        }
        case fifo:{
            Fifo ff(processVec,frames);
            ff.fifo();
        break;
        }
        case lru:{
            LRU lru(processVec,frames);
            lru.lru();
        break;
        }
        case fifo_i:{
            Fifo_i fifoi(processVec,frames);
            fifoi.fifo_i();
        break;
        }
        default:
            std::cout<<"Valor no válido"<<std::endl;
        break;

    }
}

void menu(){
    unsigned int choice = 1;
    while(choice){
        std::cout<<"Ingrese su opción\n0. Salir\n1. Óptimo\n2. Fifo\n3. LRU\n4. Fifo Mejorado\n";
        std::cin>>choice;
        if(choice == 0){
            std::cout<<"Programa terminado";
            return;
        }
        selectAlgorithm(choice);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Oprima enter tecla para continuar" << std::endl;
        std::cin.get();  
        clearConsole();
    }
}

int main(){
    menu();
}