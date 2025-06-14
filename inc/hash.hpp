/**
 * @file hash.hpp
 * @author Anna Wheeler (wheeler-cs)
 * 
 * @brief File acts as an entry point for the CryptoPP library. Also contains function prototypes for generating
 * information about a file, including hashes and file size.
 * 
 * @note If MULTITHREAD_ENABLE is set during compilation, adds the capabilities of multithreading to the program when
 * getting file information.
 * 
 * @see hash.cpp
 * 
 */

#ifndef HASH_H
#define HASH_H

#include "cryptopp/cryptlib.h"
#include "cryptopp/channels.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/md5.h"
#include "cryptopp/sha.h"

#include "cryptopp/config_int.h"
#include "cryptopp/crc.h"

using namespace CryptoPP;

#include <algorithm>
#include <fstream>


void generate_file_info (std::string f_name, std::string &md5, std::string &sha1, unsigned long long &size);
void generate_md5 (std::string f_name, std::string *md5);
void generate_sha1 (std::string f_name, std::string *sha1);
void calculate_file_size (std::string f_name, unsigned long long *f_size);


#endif
