/* File
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1402
 * 
 * File contains function prototypes for directory interfacing. Requires the non-standard dirent.h header not found
 * on Windows machines.
 * 
 * See file.cpp for function definitions.
*/

#ifndef FILE_H
#define FILE_H

#define DIRECTORY_LIST_SIZE 25

#include <iostream>
#include <string>

#include <dirent.h>

unsigned int populate_dir_entries (std::string directory, std::string entry_list [], unsigned int list_size);

#endif