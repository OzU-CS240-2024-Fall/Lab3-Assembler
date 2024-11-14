#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    
    FILE *input,*output_hex, *output_bin;
    char output_file4hex[256];
    char output_file4bin[256];

    if (argc != 2){
    	fprintf(stderr,"Please provide an input file! (e.g., exercise1.s \n");
    	fprintf(stderr,"Example Usage: ./assembler exercise1.s\n");
        return -1;
    }
    
    input = fopen(argv[1],"r");
    const char *dot = strrchr(argv[1], '.'); //get the name of the file to generate output files
    if (dot) {
        // Copy the part before the extension
        size_t basename_len = dot - argv[1];
        strncpy(output_file4hex, argv[1], basename_len);
        strncpy(output_file4bin, argv[1], basename_len);
        output_file4hex[basename_len] = '\0';
        output_file4bin[basename_len] = '\0';

        // Append proper suffix
        strcat(output_file4hex, ".hex");
        strcat(output_file4bin, ".bin");
    }else{
    	fprintf(stderr,"Please provide a proper input file (with suffix \".s\")\n");
        return -1;
    }
        
    output_hex = fopen(output_file4hex,"w"); //this will open an output file to keep instructions in hex form as a text
    output_bin = fopen(output_file4bin,"wb"); //this will open an output file to keep instructions in hex form as a binary

    if( input == NULL || output_hex == NULL || output_bin == NULL) {
        fprintf(stderr,"Couldn't access file\n");
        return -1;
    }

    //you need to implement a function that reads and parses the content of the input file.
    //each line of the input file would have a RISC-V assembly instruction, and you should
    //convert it to machine code encoded in HEX.
    //Then, you should add each HEX code into output files: 
    	//one in text form (so you can open it with regular text editor); 
    	//and one in binary form (so you can use it to generate executable with riscv32-unknown-elf-as and riscv32-unknown-elf-ld; then run it with Spike)
    	//note that instructions are stored in little-endian order in RISC-V memory. 
    	//This means if you have an instruction whose HEX representation is 0FF00293 (and stored in .hex file as 0FF00293),
    	//then it should be stored as 9302F00F into .bin file (last byte stored first).
    
    //You may find the below code snippet helpful when you want to into output files.
    //HEX representation as a string	
    char hex_instruction[9];  // 8 hex digits + null terminator for 32-bit instructions
    strcpy(hex_instruction, "00000293");
    //you need to calculate HEX representation it for each instruction in the file    
    //then, you can write it to .hex output file, as a string
    fprintf(output_hex, "%s\n", hex_instruction);
    
    
    //Also, write instruction into binary output file in little-endian format
    //To do so, first convert string representation to binary 
    uint32_t instruction = (uint32_t) strtol(hex_instruction, NULL, 16);
    // Then write it to binary output file in little-endian format
    for (int i = 0; i < 4; i++) {
    	uint8_t byte = (instruction >> (i * 8)) & 0xFF;
    	fwrite(&byte, sizeof(uint8_t), 1, output_bin);
    }
    

    fclose(input);
    fclose(output_hex);
    fclose(output_bin);

    return 0;

}
