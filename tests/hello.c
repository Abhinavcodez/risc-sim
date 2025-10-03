void _start() {
    volatile unsigned char *memory = (unsigned char*)0x0;
    memory[0] = 0xFF; // first byte triggers GPU in your sim
    while(1);
}