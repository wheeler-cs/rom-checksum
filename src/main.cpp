/* File: main.cpp
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1445
 * 
 * File contains main, which interfaces with other functions to load XML data, generate information for input files,
 * and handle memeory management.
 * 
 * See other files within program.
*/

#include "core.h"
#include "file.h"
#include "hash.h"
#include "rom.h"
#include "xml.h"

int main(int argc, char** argv) {
    bool is_silent = false;
    std::string data_directory = "data", rom_directory = "roms";

    // Handle CLI arguments
    handle_args (argc, argv, &data_directory, &rom_directory, &is_silent);


    // Alocate memory
    Xml *xml_data = allocate_Xml (DIRECTORY_LIST_SIZE, is_silent);
    Rom_File *rom_data = allocate_Rom_File (MAX_LIST_SIZE, is_silent);


    // Load XML data
    unsigned int xml_list_size = populate_Xml (xml_data, data_directory, DIRECTORY_LIST_SIZE, is_silent);


    // Hash rom files
    std::string rom_list[MAX_LIST_SIZE];
    unsigned int rom_list_size = populate_Rom_File (rom_data, rom_directory, MAX_LIST_SIZE, is_silent);


    // Verify rom data
    verify_roms (xml_data, xml_list_size, rom_data, rom_list_size, is_silent);


    // Deallocate memory
    deallocate_Xml (xml_data);
    deallocate_Rom_File (rom_data);


    // Terminate program
    std::cout << std::endl;
    return 0;
}