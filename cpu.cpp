#include <iostream>
#include <stdio.h>
#include "cpu.h"

void Cpu::cycle()
{   int opcode;
    uint16_t inst = inst_fetch();

    opcode = (inst >> 15) &1;
    
    switch (opcode){
        case 1:{
            int comp = 0;
            // flag
            bool a = (((inst >> 12) & 1) == 1);
                /* bitwise trick
                    bool f;         // conditional flag
                    unsigned int m; // the bit mask
                    unsigned int w; // the word to modify:  if (f) w |= m; else w &= ~m; 

                    w ^= (-f ^ w) & m;
                */
            uint16_t mask_for_M = (0xff ^ ((-a ^ 0xff) & 0xff));
            uint16_t mask_for_A = (0xff ^ ((-(!a) ^ 0xff) & 0xff));

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
                    case 0x0c:
                        comp = reg_D;
                        break;
                    case 0x30:


                    comp =(reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M);
                        break;
                    case 0x0d:
                        comp = !reg_D;
                        break;
                    case 0x31:
                        comp = (int) !(reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M);
                        break;
                    case 0x0f:
                        comp = -reg_D;
                        break;
                    case 0x33:
                        comp = -(int)(reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M);
                        break;
                    case 0x1f:
                        comp = reg_D + 1;
                        break;
                    case 0x37:
                        comp =  (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M))+ 1;
                        break;
                    case 0x0e:
                        comp = reg_D -1;
                        break;
                    case 0x32:
                        comp = (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M)) - 1;
                        break;
                    case 0x02:
                        comp = reg_D + (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M));
                        break;
                    case 0x13:
                        comp = reg_D - (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M));
                        break;
                    case 0x07:
                        comp = (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M)) - reg_D;
                        break;
                    case 0x00:
                        comp = reg_D &  (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M));
                        break;
                    case 0x15:
                        comp = reg_D |  (int)((reg_A & mask_for_A)|(data_mem[reg_A] & mask_for_M));
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

            reg_A = (0xffff & inst);
            pc = pc +1;

            break;
        }
    }

}

uint16_t Cpu::inst_fetch()
{

    uint16_t inst = inst_mem[pc];
    return inst;
}

Cpu::Cpu()
{

    inst_mem = (uint16_t *)malloc(200*sizeof(uint16_t));
    data_mem = (uint16_t *) malloc(200 *sizeof(uint16_t));
    pc = 0;
}

bool Cpu::load_bin(FILE *read_ptr)
{
    if (fread(inst_mem ,40,1, read_ptr) == 0){
        return false;
    }

    return true; 
}
Cpu::~Cpu(){
    free(inst_mem);
    free(data_mem);
}