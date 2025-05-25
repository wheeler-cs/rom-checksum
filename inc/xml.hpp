/**
 * @file xml.hpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 25, 2025
 * 
 * @brief Holds the class definition for Xml and other function prototypes.
 * 
 */


#ifndef XML_H
#define XML_H

#define MAX_LIST_SIZE 50000
#define XML_HEADER "<?xml version=\"1.0\"?>"
#define XML_HEADER_SIZE 21

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rom.hpp"

class Xml {
public:

    // Class constructors
    Xml();
    Xml (std::string n,
         std::string d,
         std::string a,
         std::string h);

    // Accessors
    std::string  get_name()                   { return name; }
    std::string  get_description()            { return description; }
    std::string  get_author()                 { return author; }
    std::string  get_homepage()               { return homepage; }
    Rom_File     get_game(unsigned int index) { return list[index]; }
    Rom_File *   get_list()                   { return &list[0]; }
    unsigned int get_list_size()              { return list_size; }

    // Mutators
    void set_name        (std::string n)  { name = n; }
    void set_description (std::string d)  { description = d; }
    void set_author      (std::string a)  { author = a; }
    void set_homepage    (std::string h)  { homepage = h; }
    void set_list_size   (unsigned int i) { list_size = i; }
    bool set_rom         (Rom_File r, unsigned int index);
    bool append_rom      (Rom_File r);

    // Rom searching
    Rom_File* search_rom_md5 (std::string key);
    Rom_File* search_rom_sha1 (std::string key);
    Rom_File* search_rom_size (unsigned long long key);

private:
    std::string name, description, author, homepage;

    Rom_File list [MAX_LIST_SIZE];
    unsigned int list_size;
};

/** @brief Allocates memory for a new `Xml` class instance.
 * 
 * @param size The size of the array of `Xml` instances to be allocated.
 * @param f_silence Flag that determines if message should be sent to stdout.
 * 
 * @return Newly-allocated `Xml` instance.
 * 
 */
Xml * allocate_Xml(unsigned int, bool);


/** @brief Deallocates the memory allocated an `Xml` class instance.
 * 
 * @param xml_ptr Pointer to memory associated with an `Xml` instance.
 * 
 * @note Deletes the memory and handles the dangling pointer.
 * 
 */
void deallocate_Xml(Xml *);

bool load_file (std::string f_name, std::vector <std::string> &xml_data);
bool verify_xml (std::vector <std::string> &xml_data);
std::string find_in_xml_header (std::string keyword, std::vector <std::string> &xml_data);
unsigned int find_in_xml_body (std::string keyword, Rom_File rom_list[], std::vector <std::string> &xml_data);
std::string find_in_string (std::string keyword, std::string input);

#endif
