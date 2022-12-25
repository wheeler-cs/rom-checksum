/* File: core.h
 * Author: Lieutenant Debaser
 * Last Update (yyyy-mm-dd_hhMM): 2022-01-27_1341
 * 
 * File contains prototypes for functions that tie together rest of the files (hence the name 'core'). The parameters
 * required to interface with functions defined in core.cpp can easily be seen here.
 * 
 * See core.cpp for function definitions.
*/

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>

#include "file.h"
#include "hash.h"
#include "rom.h"
#include "xml.h"

void handle_args (int argc,
                  char** argv,
                  std::string *data_dir,
                  std::string *rom_dir, 
                  bool *is_silent);

Xml* allocate_Xml (unsigned int size, bool is_silent);
void deallocate_Xml (Xml* xml_ptr);
Rom_File* allocate_Rom_File (unsigned int size, bool is_silent);
void deallocate_Rom_File (Rom_File* rom_ptr);
unsigned int populate_Xml (Xml xml_data[], std::string xml_dir, unsigned int size, bool is_silent);
unsigned int populate_Rom_File (Rom_File rom_data[], std::string rom_dir, unsigned int size, bool is_silent);

void verify_roms (Xml xml_data[],
                  unsigned int xml_list_size,
                  Rom_File rom_data[],
                  unsigned int rom_list_size, 
                  bool is_silent);

#endif
