#include <iostream>
#include <stdio.h>
#include "cpu.h"

void Cpu::cycle()
{   int opcode;
    uint16_t inst = inst_fetch();
    std::cout << "inst is " << inst << std::endl;
    opcode = (inst >> 15) &1;
    
    switch (opcode){
        case 1:{
            int comp = 0;
            // flag
            bool a = (((inst >> 12) & 1) == 1);
            // dest dest = (inst >> 3 & 0x7);
            // uint8_t jump = (uint8_t)(inst & 0x7);
            // if (jump == 0x7){
            //     pc = reg_A;
            //     break;
            // }
            std::cout << "case 1"<<std::endl;
            // pc = pc +1;
            // std::cout<< unsigned(pc) << std::endl;
            // break;
            
                switch((inst >> 6) & 0x3f){
                    case 0x2a:
                        comp = 0;
                        break;
                    case 0x3f:
                        comp = 1;
                        break;
                    case 0x3a:
                        comp = -1;
                        break;
                    case 0x0b:
                        comp = reg_D;
                        break;
                    case 0x30:
                    /* bitwise trick
                    bool f;         // conditional flag
                    unsigned int m; // the bit mask
                    unsigned int w; // the word to modify:  if (f) w |= m; else w &= ~m; 

                    w ^= (-f ^ w) & m;
                    */

                    comp = (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x0d:
                        comp = !reg_D;
                        break;
                    case 0x31:
                        comp = (int) !((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x0f:
                        comp = -reg_D;
                        break;
                    case 0x33:
                        comp = -(int)(int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x1f:
                        comp = reg_D + 1;
                        break;
                    case 0x37:
                        comp =  (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ))+ 1;
                        break;
                    case 0x0e:
                        comp = reg_D -1;
                        break;
                    case 0x32:
                        comp = (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) )) - 1;
                        break;
                    case 0x02:
                        comp = reg_D + (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x13:
                        comp = reg_D - (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x07:
                        comp = (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) )) - reg_D;
                        break;
                    case 0x00:
                        comp = reg_D &  (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    case 0x15:
                        comp = reg_D |  (int)((reg_A ^ ((-(!a) ^ reg_A) & 0xff) )|( data_mem[reg_A] ^((-(a) ^ data_mem[reg_A]) & 0xff) ));
                        break;
                    
                }

                switch(inst>>3 & 0x7){
                    case null_dest:
                        break;
                    case M:
                        data_mem[reg_A] = comp;
                        break;
                    case D:
                        reg_D = comp;
                        break;
                    case MD:
                        data_mem[reg_A] = comp;
                        reg_D = comp;
                        break;
                    case A:
                        reg_A = comp;
                        break;
                    case AM:
                        data_mem[reg_A] = comp;
                        reg_A = comp;
                        break;
                    case AD:
                        reg_A = comp;
                        reg_D = comp;
                        break;
                    case AMD:
                        reg_D = comp;
                        data_mem[reg_A] = comp;
                        reg_A = comp;
                        break;
                }
                switch(inst & 0x7){
                    case null_jump:
                        pc = pc + 1;
                        break;
                    case JGT:
                        if (comp > 0){
                            pc = reg_A;
                            break;
                        }
                        pc = pc + 1;
                        break;
                    case JEQ:
                        if (comp == 0){
                                pc = reg_A;
                                break;
                        }
                        pc = pc + 1;
                        break;
                    case JGE:
                        if (comp >= 0){
                                pc = reg_A;
                                break;
                        }
                        pc = pc + 1;
                        break;
                    case JLT:
                        if (comp < 0){
                            pc = reg_A;
                            break;
                        }
                        pc = pc + 1;
                        break;
                    case JNE:
                        if (comp != 0){
                            pc = reg_A;
                            break;
                        }
                        pc = pc + 1;
                        break;
                    case JLE:
                        if (comp <= 0){
                            pc = reg_A;
                            break;
                        }
                        pc = pc + 1;
                        break;
                    case JMP:
                        pc = reg_A;
                        break;
                }
                break;
            }
        case 0:{
            std::cout << "case 2"<<std::endl;
            reg_A = (0xffff & inst);
            pc = pc +1;
            std::cout<<  unsigned(pc)  << std::endl;
            break;
        }
    }
    std::cout << "test"<<std::endl;
}

uint16_t Cpu::inst_fetch()
{
    if (pc > 1){
        exit(0);
    }
    printf("fetch %x\n", inst_mem[pc]);
    uint16_t inst = inst_mem[pc];
    return inst;
}

Cpu::Cpu()
{
    std::cout <<"start"<<std::endl;
    inst_mem = (uint16_t *)malloc(200*sizeof(uint16_t));
    pc = 0;
}

bool Cpu::load_bin(FILE *read_ptr)
{
    if (fread(inst_mem ,4,1, read_ptr) == 0){
        return false;
    }
    for (int i = 0; i <2; i++){
        printf("%x\n", inst_mem[i]);
    }

    return true; 
}
Cpu::~Cpu(){
    free(inst_mem);
}