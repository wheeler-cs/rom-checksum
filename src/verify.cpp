/**
 * @file verify.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 25, 2025
 * 
 * @brief Function definitions for file verification.
 * 
 */

#include "verify.hpp"

// Verify roms by comparing generated values to known values
void verify_roms (Xml xml_data[], unsigned int xml_list_size, Rom_File rom_data[], unsigned int rom_list_size, bool is_silent) {
    // Pointers used to verify rom data
    Rom_File *r_ptr_md5 {NULL},
             *r_ptr_sha1 {NULL},
             *r_ptr_size {NULL};

    if(!is_silent)
        std::cout << "\nValidating files..." << std::flush;

    // Compare rom data to data loaded in from XML data files
    for (unsigned int rom_index = 0; rom_index < rom_list_size; rom_index++) {
        for (unsigned int xml_index = 0; xml_index < xml_list_size; xml_index++) {
            r_ptr_md5 = r_ptr_sha1 = r_ptr_size = NULL;

            // Use pointers to Rom_File class instances to determine if a match was found
            r_ptr_md5 = xml_data[xml_index].search_rom_md5 (rom_data[rom_index].get_md5());
            r_ptr_sha1 = xml_data[xml_index].search_rom_sha1 (rom_data[rom_index].get_sha1());
            r_ptr_size = xml_data[xml_index].search_rom_size (rom_data[rom_index].get_size());
            if ((r_ptr_md5 != NULL) && (r_ptr_sha1 != NULL) && (r_ptr_size != NULL))
                break;
        }
        // If at least one of the pointers was NULL, a match was not found
        if ((r_ptr_md5 == NULL) || (r_ptr_sha1 == NULL) || (r_ptr_size == NULL))
            std::cerr << "\n\n! Could not verify: " << rom_data[rom_index].get_name();
        else if (!is_silent)
            std::cout << "\n\n" << rom_data[rom_index].get_name() << ":\n\t" << r_ptr_md5->get_name();

    }
}
