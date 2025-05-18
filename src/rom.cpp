/* File: rom.cpp
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1431
 * 
 * File contains definitions for the Rom_File class functions, along with a basic constructor.
 * 
 * See rom.h for class definition and member data.
*/

#include "rom.hpp"


// Class constructors

Rom_File::Rom_File() {
    name = "";
    
    md5 = "";
    sha1 = "";

    size = 0;
}


// Accessors

std::string Rom_File::get_name() {
    return name;
}


std::string Rom_File::get_md5() {
    return md5;
}


std::string Rom_File::get_sha1() {
    return sha1;
}


unsigned long long Rom_File::get_size() {
    return size;
}


// Mutators

void Rom_File::set_name (std::string s) {
    name = s;
}


void Rom_File::set_md5 (std::string s) {
    md5 = s;
}


void Rom_File::set_sha1 (std::string s) {
    sha1 = s;
}


void Rom_File::set_size (unsigned long long i) {
    size = i;
}
