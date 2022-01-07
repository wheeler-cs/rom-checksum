#include "rom.h"

Rom_File::Rom_File() {
    name = "";
    
    md5 = "";
    sha1 = "";

    size = 0;
}


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