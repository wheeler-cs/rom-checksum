/**
 * @file arguments.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
 * 
 * @brief Contains definitions for functions too large to fit in the header.
 * 
 * @see arguments.hpp
 * 
 */

#include "arguments.hpp"


#include <iostream>


Arguments::Arguments() {
    this->is_silent = false;

    this->op_mode = MODE_VERIFY;

    this->rom_dir    = "./roms/";
    this->data_dir   = "./data/";
    this->patch_file = "./patch.ups";
}


Arguments::Arguments(unsigned int argc, char ** argv) : Arguments()
{
    // Start `i` at 1 to skip executable's name
    for (unsigned int i = 1; (i < argc) && (this->op_mode != MODE_STOP); i++)
    {
        // 'roms' directory set for files to be validated
        if ((std::string(argv[i]) == "-r") || (std::string(argv[i]) == "--roms"))
        {
            if (i + 1 < argc)
            {
                this->rom_dir = argv[i + 1];
                i++;
            }
            else
            {
                std::cerr << "\n[ERR] Missing argument for rom directory";
            }
        }
        // 'data' directory set for XML reference files
        else if ((std::string(argv[i]) == "-d") || (std::string(argv[i]) == "--data"))
        {
            if (i + 1 < argc)
            {
                this->data_dir = argv[i + 1];
                this->op_mode = MODE_VERIFY;
                i++;
            }
            else
            {
                std::cerr << "\n[ERR] Missing argument for data directory";
            }
        }
        // Patch file for ROM hacks
        else if ((std::string(argv[i]) == "-p") || (std::string(argv[i]) == "--patch"))
        {
            if (i + 1 < argc)
            {
                this->patch_file = argv[i + 1];
                this->op_mode = MODE_PATCH;
                i++;
            }
            else
            {
                std::cerr << "\n[ERR] Missing argument for input patch";
            }
        }
        // Run program silently
        else if ((std::string(argv[i]) == "-s") || (std::string(argv[i]) == "--silent"))
        {
            this->is_silent = true;
        }
        // Print a help menu about usage
        else if ((std::string(argv[i]) == "-h") || (std::string(argv[i]) == "--help"))
        {
            this->print_help();
            this->op_mode = MODE_STOP;
        }
        // Unknown argument was provided
        else
        {
            std::cerr << "\n[ERR] Unhandled argument: " << std::string(argv[i]);
            this->op_mode = MODE_STOP;
        }
    }
}


void Arguments::print_args()
{
    std::cout << "\n +------------------+"
              << "\n |      Flags       |"
              << "\n +------------------+"
              << "\n  Op Mode: " << this->op_mode
              << "\n   Silent: ";
    if(this->is_silent)
    {
        std::cout << 'Y';
    }
    else
    {
        std::cout << 'N';
    }
    std::cout << "\n\n"
              << "\n +------------------+"
              << "\n |   Directories    |"
              << "\n +------------------+"
              << "\n  ROM: " << this->rom_dir
              << "\n DATA: " << this->data_dir;
    std::cout << "\n"
              << "\n +------------------+"
              << "\n |      Files       |"
              << "\n +------------------+"
              << "\n PATCH: " << this->patch_file;

    std::cout << std::endl;
}


void Arguments::print_help()
{
    std::cout << "\nOptions: "
          << "\n\t-s: Do not send program output to terminal (errors are still sent to std::cerr)."
          << "\n\t-r [directory]: Define the directory containing the roms to be checked."
          << "\n\t-d [directory]: Define the directory containing XML data files for verification."
          << "\n\t-p [file]: Define the patch file for patching."
          << '\n' << std::endl;
}
