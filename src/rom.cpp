/**
 * @file rom.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 25, 2025
 * 
 * @brief Contains function definitions for assisting the `Rom_File` class.
 * 
 */
 
#include "rom.hpp"

#include "file.hpp"
#include "hash.hpp"


// Class constructors

Rom_File::Rom_File() {
    name = "";
    md5 = "";
    sha1 = "";
    size = 0;
}


// Allocate the memory needed to store ROM data
Rom_File * allocate_Rom_File (unsigned int size, bool f_silence) {
    if(!f_silence)
    {
        std::cout << "\nAllocating ROM memory..." << std::flush;
    }

    return (new Rom_File[size]);
}


// Deallocate memory allocated for ROM data
void deallocate_Rom_File (Rom_File* rom_ptr) {
    delete[] rom_ptr;
}


// Populate a list of ROM files in the 'rom' directory
unsigned int populate_Rom_File (Rom_File rom_data[], std::string rom_dir, unsigned int size, bool is_silent) {
    std::string* dir_list {new std::string[size]};
    unsigned int list_size {0};

    list_size = populate_dir_entries (rom_dir, dir_list, size);

    if(!is_silent)
        std::cout << "\nGenerating data for ROMs..." << std::flush;

    std::string md5 {""}, sha1 {""};
    unsigned long long file_size {0};

    // Generate data from rom file to be compared to known values
    for (unsigned int i = 0; i < list_size; i++) {
        rom_data[i].set_name (dir_list[i]);
        generate_file_info (dir_list[i], md5, sha1, file_size);
        rom_data[i].set_md5 (md5);
        rom_data[i].set_sha1 (sha1);
        rom_data[i].set_size (file_size);
    }

    delete[] dir_list;

    return list_size;
}
