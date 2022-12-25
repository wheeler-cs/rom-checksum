/* File: rom.h
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1428
 * 
 * File contains definition for the Rom_File class.
 * 
 * See rom.cpp for function definitions.
*/

#ifndef ROM_H
#define ROM_H

#include <string>

class Rom_File {
public:
    // Class constructors
    Rom_File();

    // Accessors
    std::string get_name();
    std::string get_md5();
    std::string get_sha1();
    unsigned long long get_size();

    // Mutators
    void set_name (std::string s);
    void set_md5 (std::string s);
    void set_sha1 (std::string s);
    void set_size (unsigned long long i);


private:
    std::string name;
    
    std::string md5, sha1;

    unsigned long long size;
};

#endif
