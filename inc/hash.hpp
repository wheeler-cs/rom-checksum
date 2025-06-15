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


void generate_file_info(std::string, std::string &, std::string &, unsigned long long &);


/** @brief Calculates the CRC32 hash for a file.
 * 
 * This function is capable of hashing either part of or the entirety of the target file.
 * 
 * @param f_name Path to the file to be hashed by the function.
 * @param byte_limit Number of bytes from the file that should be used to generate the file.
 * 
 * @note A value of 0 for `byte_limit` will use the entire file as input.
 * 
 * @returns The CRC32 hash of bytes from the target file.
 * 
 */
word32 generate_crc32(const std::string &, size_t);


void generate_md5(std::string, std::string *);
void generate_md5(std::string, std::string *, size_t);
void generate_sha1(std::string, std::string *);
void calculate_file_size(std::string, unsigned long long *);


#endif
