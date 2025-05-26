/**
 * @file xml.hpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
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
    std::string  get_name()                   { return this->name; }
    std::string  get_description()            { return this->description; }
    std::string  get_author()                 { return this->author; }
    std::string  get_homepage()               { return this->homepage; }
    Rom_File     get_game(unsigned int index) { return this->list[index]; }
    Rom_File *   get_list()                   { return &(this->list[0]); }
    unsigned int get_list_size()              { return this->list_size; }

    // Mutators
    void set_name        (std::string n)  { this->name = n; }
    void set_description (std::string d)  { this->description = d; }
    void set_author      (std::string a)  { this->author = a; }
    void set_homepage    (std::string h)  { this->homepage = h; }
    void set_list_size   (unsigned int i) { this->list_size = i; }
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


/** @brief The load the contents of a file into a structure and preprocess it.
 * 
 * @param f_name Name of file to be loaded into memory.
 * @param xml_data Vector to store newly-loaded data.
 * 
 * @returns If the load operation was a success.
 * 
 */
bool load_file (std::string, std::vector <std::string> &);


/** @brief Populates `Xml` instance metadata for all data files.
 * 
 * @param xml_data `Xml` class instances to store metadata about data files.
 * @param xml_dir Directory containing properly-formatted data files.
 * @param size The upper limit on number of files that can be loaded.
 * @param is_silent Flag indicating if information is printed to stdout.
 * 
 * @returns The number of data files attempted to be loaded.
 * 
 */
unsigned int populate_Xml(Xml[], std::string, unsigned int, bool);


bool verify_xml (std::vector <std::string> &xml_data);
std::string find_in_xml_header (std::string keyword, std::vector <std::string> &xml_data);
unsigned int find_in_xml_body (std::string keyword, Rom_File rom_list[], std::vector <std::string> &xml_data);
std::string find_in_string (std::string keyword, std::string input);

#endif
