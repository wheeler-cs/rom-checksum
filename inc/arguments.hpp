/**
 * @file arguments.hpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 18, 2025
 * 
 * @brief Class definitions and methods for handling command line arguments.
 * 
 * @see arguments.cpp
 * 
 */


#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP


#include <iostream>
#include <string>


enum OpModes
{
    /** Program should stop execution */
    MODE_STOP = 0,
    /** Mode program should run in isn't set yet */
    MODE_UNDEFINED,
    /** Program should run in file verification mode */
    MODE_VERIFY,
    /** Program should run in patcher mode */
    MODE_PATCH,
};


class Arguments 
{
public:
    // Class constructors
    Arguments();

    Arguments (unsigned int, char **);


    // Accessors
    /** Returns flag that indicates silent operation */
    bool         get_is_silent()  { return this->is_silent;  }

    unsigned int get_op_mode()    { return this->op_mode;    }

    /** Returns the target ROM directory */
    std::string  get_rom_dir()    { return this->rom_dir;    }

    /** Return the target data directory */
    std::string  get_data_dir()   { return this->data_dir;   }

    /** Returns the path of the patch file */
    std::string  get_patch_file() { return this->patch_file; }


    // Mutators
    /** Sets the silent operation flag */
    void set_is_silent (bool b)         { this->is_silent  = b; }

    /** Sets the mode of operation for the program */
    void set_op_mode   (unsigned int i) { this->op_mode    = i; }

    /** Sets the target ROM directory */
    void set_rom_dir   (std::string s)  { this->rom_dir    = s; }

    /** Sets the target data directory */
    void set_data_dir  (std::string s)  { this->data_dir   = s; }

    /** Sets the target patch file */
    void set_patch_file(std::string s)  { this->patch_file = s; }


    // Utility
    /** Prints values of member data in a human-readable format */
    void print_args();

    /** Prints a help message indicating program usage */
    void print_help();


private:
    bool is_silent;

    unsigned int op_mode;

    std::string rom_dir, data_dir, patch_file;
};

#endif
