/**
 * @file verify.hpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
 * 
 * @brief Contains function definitions for file verification.
 * 
 */

#ifndef VERIFY_HPP
#define VERIFY_HPP

#include "arguments.hpp"
#include "rom.hpp"
#include "xml.hpp"


/** @brief Performs the entire verification process.
 * 
 * @param args Parsed command line arguments with program state information.
 * 
 */
void do_verification(Arguments *);

/** @brief Verifies ROMs by comparing generated values against known-good values.
 * 
 * @param xml_data List of `Xml` objects containing loaded reference data.
 * @param xml_list_size Number of `Xml` objects that have been loaded.
 * @param rom_data List of ROM files to be verified.
 * @param rom_list_size Size of the list of ROM files to be verified.
 * @param is_silent Flag indicating if only errors are printed.
 * 
 */
void verify_roms(Xml[], unsigned int, Rom_File[], unsigned int, bool);



#endif
