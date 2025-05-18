/* File: xml.h
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1441
 * 
 * File contains Xml-interfacing class definition along with prototypes for various text-handling functions. Various
 * constant definitions are also defined here, including the maximum number of entries that can be loaded from an XML
 * file and the header of an XML header.
 * 
 * See xml.cpp for function definitions.
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
    std::string get_name();
    std::string get_description();
    std::string get_author();
    std::string get_homepage();
    Rom_File get_game (unsigned int index);
    Rom_File* get_list();
    unsigned int get_list_size();

    // Mutators
    void set_name (std::string s);
    void set_description (std::string s);
    void set_author (std::string s);
    void set_homepage (std::string s);
    bool set_rom (Rom_File r, unsigned int index);
    bool append_rom (Rom_File r);
    void set_list_size (unsigned int i);

    // Rom searching
    Rom_File* search_rom_md5 (std::string key);
    Rom_File* search_rom_sha1 (std::string key);
    Rom_File* search_rom_size (unsigned long long key);

private:
    std::string name, description, author, homepage;

    Rom_File list [MAX_LIST_SIZE];
    unsigned int list_size;
};

bool load_file (std::string f_name, std::vector <std::string> &xml_data);
bool verify_xml (std::vector <std::string> &xml_data);
std::string find_in_xml_header (std::string keyword, std::vector <std::string> &xml_data);
unsigned int find_in_xml_body (std::string keyword, Rom_File rom_list[], std::vector <std::string> &xml_data);
std::string find_in_string (std::string keyword, std::string input);

#endif
