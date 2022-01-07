#include "core.h"

Xml* allocate_Xml (unsigned int size, bool is_silent) {
    switch (is_silent) {
        case 0:
            std::cout << "\nAllocating XML memory..." << std::flush;
    }
    return (new Xml[size]);
}


void deallocate_Xml (Xml* xml_ptr) {
    delete[] xml_ptr;
}


Rom_File* allocate_Rom_File (unsigned int size, bool is_silent) {
    switch (is_silent) {
        case 0:
            std::cout << "\nAllocating ROM memory..." << std::flush;
    }

    return (new Rom_File[size]);
}


void deallocate_Rom_File (Rom_File* rom_ptr) {
    delete[] rom_ptr;
}


unsigned int populate_Xml (Xml xml_data[], std::string xml_dir, unsigned int size, bool is_silent) {
    std::string* dir_list = new std::string[size];
    unsigned int list_size = 0;

    std::vector <char> temp_xml_data;

    list_size = populate_dir_entries (xml_dir, dir_list, size);

    switch (is_silent) {
        case 0:
            std::cout << "\nLoading XML..." << std::flush;
    }

    for (unsigned int i = 0; i < list_size; i++) {
        temp_xml_data = load_file (dir_list[i]);

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


unsigned int populate_Rom_File (Rom_File rom_data[], std::string rom_dir, unsigned int size, bool is_silent) {
    std::string* dir_list = new std::string[size];
    unsigned int list_size = 0;

    list_size = populate_dir_entries (rom_dir, dir_list, size);

    switch (is_silent) {
        case 0:
            std::cout << "\nLoading ROMs..." << std::flush;
    }

    for (unsigned int i = 0; i < list_size; i++) {
        rom_data[i].set_name (dir_list[i]);
        rom_data[i].set_md5 (generate_md5 (dir_list[i]));
        rom_data[i].set_sha1 (generate_sha1 (dir_list[i]));
    }

    delete[] dir_list;

    return list_size;

}


void verify_roms (Xml xml_data[], unsigned int xml_list_size, Rom_File rom_data[], unsigned int rom_list_size, bool is_silent) {
    Rom_File* r_ptr_md5 = NULL, *r_ptr_sha1 = NULL;

    for (unsigned int rom_index = 0; rom_index < rom_list_size; rom_index++) {
        for (unsigned int xml_index = 0; xml_index < xml_list_size; xml_index++) {
            r_ptr_md5 = xml_data[xml_index].search_rom_md5 (rom_data[rom_index].get_md5());
            r_ptr_sha1 = xml_data[xml_index].search_rom_sha1 (rom_data[rom_index].get_sha1());
            if ((r_ptr_md5 != NULL) && (r_ptr_sha1 != NULL))
                break;
        }
        if ((r_ptr_md5 == NULL) || (r_ptr_sha1 == NULL))
            std::cerr << "\n\n! Could not verify: " << rom_data[rom_index].get_name();
        else if (!(is_silent))
            std::cout << "\n\n" << rom_data[rom_index].get_name() << ":\n\t" << r_ptr_md5->get_name();

    }
}