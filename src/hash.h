#ifndef HASH_H
#define HASH_H

#include "cryptopp/cryptlib.h"
#include "cryptopp/channels.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/md5.h"
#include "cryptopp/sha.h"

using namespace CryptoPP;

#include <algorithm>
#include <fstream>

std::string generate_md5 (std::string f_name);
std::string generate_sha1 (std::string f_name);
unsigned long long generate_f_size (std::string f_name);

#endif