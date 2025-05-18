/** 
 * @file core.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 18, 2025
 *
 * File contains definitions for functions that bind together functionality of the rest of the files (hence the name
 * 'core'). Memory allocation and deallocation for Xml and Rom_File data structures is handled here, along with loading
 * data from inputs files.
 * 
 * @see core.hpp
 * 
*/


#include "core.hpp"


// Allocate the memory needed to store XML data
Xml* allocate_Xml (unsigned int size, bool is_silent) {
    if(!is_silent)
        std::cout << "\nAllocating XML memory..." << std::flush;
    return (new Xml[size]);
}


// Deallocate memory allocated for XML data
void deallocate_Xml (Xml* xml_ptr) {
    delete[] xml_ptr;
}


// Allocate the memory needed to store ROM data
Rom_File* allocate_Rom_File (unsigned int size, bool is_silent) {
    if(!is_silent)
        std::cout << "\nAllocating ROM memory..." << std::flush;

    return (new Rom_File[size]);
}


// Deallocate memory allocated for ROM data
void deallocate_Rom_File (Rom_File* rom_ptr) {
    delete[] rom_ptr;
}


// Populate a list of XML files in the 'data' directory
unsigned int populate_Xml (Xml xml_data[], std::string xml_dir, unsigned int size, bool is_silent) {
    std::string* dir_list {new std::string[size]};
    unsigned int list_size {0};

    std::vector <std::string> temp_xml_data;

    list_size = populate_dir_entries (xml_dir, dir_list, size);

    if(!is_silent)
        std::cout << "\nLoading XML data..." << std::flush;

    for (unsigned int i = 0; i < list_size; i++) {
        load_file (dir_list[i], temp_xml_data);

        // If XML file is valid, load data that is found in header into Xml class
        if (verify_xml (temp_xml_data)) {
            xml_data[i].set_name (find_in_xml_header ("name", temp_xml_data));
            xml_data[i].set_description (find_in_xml_header ("description", temp_xml_data));
            xml_data[i].set_author (find_in_xml_header ("author", temp_xml_data));
            xml_data[i].set_homepage (find_in_xml_header ("homepage", temp_xml_data));
            xml_data[i].set_list_size (find_in_xml_body ("rom", xml_data[i].get_list(), temp_xml_data));
        }
        else {
            std::cerr << '\n' << dir_list[i] << " is not a valid XML file!";
        }

        temp_xml_data.clear();
    }

    delete[] dir_list;

    return list_size;
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
