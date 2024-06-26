#include "../include/memory.h"

const u8 font[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4  
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void memory_initialize(Memory *memory)
{
    memset(memory, 0, sizeof(Memory));

    memcpy(memory->RAM + FONT_OFFSET, font, 80);

	memory->PC = BASE_ADDRESS;
	return;
}

bool memory_rom_read(int argc, char *argv[], Memory *memory)
{
	if (argc < 2)
    {
		fprintf(stderr, "Rom file is not provided.\n");	
		return false;
	}

	FILE *file = fopen(argv[1], "rb");
	if (!file)
    {
		fprintf(stderr, "Could not read rom.\n");
		return false;
	}
	
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	fread(memory->RAM + BASE_ADDRESS, 8, size, file);
	return true;
}	
