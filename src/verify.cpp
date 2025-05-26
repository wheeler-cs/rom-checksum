/**
 * @file verify.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
 * 
 * @brief Function definitions for file verification.
 * 
 */

#include "verify.hpp"

#include "file.hpp"


void do_verification(Arguments * args)
{
    // Load XML reference data
    Xml *      xml_data = allocate_Xml(DIRECTORY_LIST_SIZE, args->get_is_silent());
    unsigned int xml_list_size = populate_Xml(xml_data, args->get_data_dir(), DIRECTORY_LIST_SIZE, args->get_is_silent());

    // Hash rom files
    Rom_File * rom_data = allocate_Rom_File(MAX_LIST_SIZE, args->get_is_silent());
    std::string rom_list[MAX_LIST_SIZE];
    unsigned int rom_list_size = populate_Rom_File(rom_data, args->get_rom_dir(), MAX_LIST_SIZE, args->get_is_silent());

    // Verify rom data against known data
    verify_roms(xml_data, xml_list_size, rom_data, rom_list_size, args->get_is_silent());

    // Deallocate memory
    deallocate_Xml(xml_data);
    deallocate_Rom_File(rom_data);
}


// Verify roms by comparing generated values to known values
void verify_roms (Xml xml_data[], unsigned int xml_list_size, Rom_File rom_data[], unsigned int rom_list_size, bool is_silent) {
    // Pointers used to verify rom data
    Rom_File *r_ptr_md5 {NULL},
             *r_ptr_sha1 {NULL},
             *r_ptr_size {NULL};

    if(!is_silent)
        std::cout << "\nValidating files...\n" << std::flush;

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
            std::cout << "\n" << rom_data[rom_index].get_name() << ": " << r_ptr_md5->get_name();

    }
}
