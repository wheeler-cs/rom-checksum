/**
 * @file ups.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 29, 2025
 * 
 * @brief Function definitions for UPS patching operations.
 * 
 */

#include "ups.hpp"

#include <iostream>


bool UPS::validate_patch(std::string f_name)
{
    bool validation {false};
    std::ifstream ups_read;
    ups_read.open(f_name.c_str(), std::ifstream::binary);

    if(ups_read.is_open())
    {
        char buffer[UPS_MAGIC.length()];
        uint8_t temp_checksum[4];

        // Check for magic at start of file
        ups_read.read(buffer, UPS_MAGIC.length());
        if(std::string(buffer) == UPS_MAGIC)
        {
            // Patch checksum
            ups_read.seekg(-4, ups_read.end);
            ups_read.read((char *)temp_checksum, 4);
            this->patch_crc = *(word32 *)temp_checksum; // This is unholy
            // End result checksum
            ups_read.seekg(-8, ups_read.end);
            ups_read.read((char *)temp_checksum, 4);
            this->output_crc = *(word32 *)temp_checksum;
            // Input checksum
            ups_read.seekg(-12, ups_read.end);
            ups_read.read((char *)temp_checksum, 4);
            this->input_crc = *(word32 *)temp_checksum;

            // TODO: Hash the patch file

            validation = true;
        }
    }

    ups_read.close();
    return validation;
}


void UPS::load_patch(std::string f_name) {

    std::ifstream ups_read;
    ups_read.open(f_name, std::ios::binary);

    if (ups_read.is_open()) {
        char buffer[UPS_MAGIC.length()]; // <- Coming from #define in C, this is cursed
        ups_read.read(buffer, UPS_MAGIC.length());

        std::cout << buffer;

        while(true) {
            struct UPS_Chunk chunk;

            this->chunks.push_back(chunk);
        }
    }
}


void UPS::apply_patch(std::string f_name)
{

}
