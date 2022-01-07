#ifndef FILE_H
#define FILE_H

#define DIRECTORY_LIST_SIZE 25


#include <iostream>



#include <string>

#include <dirent.h>

unsigned int populate_dir_entries (std::string directory, std::string entry_list [], unsigned int list_size);

#endif