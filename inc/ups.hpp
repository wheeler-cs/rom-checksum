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


#include <fstream>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


const std::string UPS_HEADER {"UPS1"};


struct IPS_Record {
    unsigned int address;
    
    std::vector <uint8_t> data;
};


class IPS {
public:

    // Class constructors
    IPS();

    // Mutators
    bool load_patch (std::string f_name);

private:
    std::vector <struct IPS_Record> records;

};


#endif
