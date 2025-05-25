/**
 * @file rom.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 25, 2025
 * 
 * @brief Contains the class definition for `Rom_File` and prototypes for supporting functions.
 * 
 */

#ifndef ROM_H
#define ROM_H

#include <string>

class Rom_File {
public:
    // Class constructors
    Rom_File();

    // Accessors
    std::string        get_name() { return name; }
    std::string        get_md5()  { return md5; }
    std::string        get_sha1() { return sha1; }
    unsigned long long get_size() { return size; }

    // Mutators
    void set_name(std::string n)        { name = n;}
    void set_md5(std::string m)         { md5 = m;}
    void set_sha1(std::string s)        { sha1 = s;}
    void set_size(unsigned long long s) { size = s;}


private:
    std::string name, md5, sha1;
    unsigned long long size;
};

/**
 * 
 */
Rom_File * allocate_Rom_File (unsigned int, bool);

/**
 * 
 */
void deallocate_Rom_File (Rom_File *);

/**
 * 
 */
unsigned int populate_Rom_File (Rom_File[], std::string, unsigned int, bool);


#endif
