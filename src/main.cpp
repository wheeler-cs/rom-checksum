#include "core.h"
#include "file.h"
#include "hash.h"
#include "rom.h"
#include "xml.h"

int main(int argc, char** argv) {
    bool is_silent = true;
    std::string data_directory = "data", rom_directory = "roms";

    // XML
    Xml* xml_data = allocate_Xml (DIRECTORY_LIST_SIZE, is_silent);
    unsigned int xml_list_size = populate_Xml (xml_data, data_directory, DIRECTORY_LIST_SIZE, is_silent);


    // Roms
    std::string rom_list[MAX_LIST_SIZE];
    Rom_File* rom_data = allocate_Rom_File (MAX_LIST_SIZE, is_silent);
    unsigned int rom_list_size = populate_Rom_File (rom_data, rom_directory, MAX_LIST_SIZE, is_silent);


    // Verify
    verify_roms (xml_data, xml_list_size, rom_data, rom_list_size, is_silent);


    // Deallocate memory
    deallocate_Xml (xml_data);
    deallocate_Rom_File (rom_data);

    // Terminate program
    std::cout << std::endl;
    return 0;
}