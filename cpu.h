#pragma once


class Cpu
{
    public:
        void cycle();
        bool load_bin(FILE *read_ptr);
    Cpu();
    ~Cpu();
    private:
        uint16_t inst_fetch();
        uint16_t pc;
        uint16_t *inst_mem;
        uint16_t *data_mem;
        uint16_t reg_A;
        int16_t reg_D;
        enum jump{
            null_jump,
            JGT,
            JEQ,
            JGE,
            JLT,
            JNE,
            JLE,
            JMP
        };
        enum dest{
            null_dest,
            M,
            D,
            MD,
            A,
            AM,
            AD,
            AMD
        };
};