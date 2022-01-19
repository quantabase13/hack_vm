#include <iostream>
#include <stdio.h>
#include "cpu.h"

void Cpu::cycle()
{   int opcode;
    uint16_t inst = inst_fetch();
    std::cout << "inst is " << inst << std::endl;
    opcode = (inst >> 15) &1;
    
    switch (opcode){
        case 1:
            std::cout << "case 1"<<std::endl;
            pc = pc +1;
            std::cout<< unsigned(pc) << std::endl;
            break;
        case 0:
            std::cout << "case 2"<<std::endl;
            pc = pc +1;
            std::cout<<  unsigned(pc)  << std::endl;
            break;
    }
    std::cout << "test"<<std::endl;
}

uint16_t Cpu::inst_fetch()
{
    if (pc > 1){
        exit(0);
    }
    printf("fetch %x\n", mem[pc]);
    uint16_t inst = mem[pc];
    return inst;
}

Cpu::Cpu()
{
    std::cout <<"start"<<std::endl;
    mem = (uint16_t *)malloc(200*sizeof(uint16_t));
    pc = 0;
}

bool Cpu::load_bin(FILE *read_ptr)
{
    if (fread(mem ,4,1, read_ptr) == 0){
        return false;
    }
    for (int i = 0; i <2; i++){
        printf("%x\n", mem[i]);
    }

    return true; 
}
Cpu::~Cpu(){
    free(mem);
}