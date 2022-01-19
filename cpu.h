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
        uint8_t pc;
        uint16_t *mem;
};