/**
 * @file ups.hpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 18, 2025
 * 
 * @brief Defines class and methods for handling IPS-format binary patches.
 * 
 */


#ifndef UPS_HPP
#define UPS_HPP

#include "cryptopp/config_int.h"
#include "cryptopp/crc.h"

using namespace CryptoPP;

#include <fstream>
#include <cstdint>
#include <string>
#include <vector>



static const std::string UPS_MAGIC {"UPS1"};


struct UPS_Chunk {
    unsigned int address;
    
    std::vector <uint8_t> data;
};
/**
 * 
 */


class UPS {
public:

    // Class constructors
    UPS() {};

    // Patching operations
    /** @brief Validates a patch file.
     * 
     * @param f_name Path to patch file to be validated.
     * 
     * @returns If the patch file has `UPS_MAGIC` as its first four bytes.
     * 
     * @note Also loads checksums for input, output, and patch files from the end of the patch.
     * 
     */
    bool validate_patch(std::string);


    /** @brief Loads a UPS patch file in chunks.
     * 
     * @param f_name Parse and load patch chunks into instance.
     * 
     */
    void load_patch(std::string);


    /** @brief Applys a loaded patch file to the target.
     * 
     * @param f_name
     * 
     */
    void apply_patch(std::string);

private:
    std::vector <struct UPS_Chunk> chunks;

    word32 input_crc, output_crc, patch_crc;
};
/**
 * 
 */


#endif
