/**
 * 
 */

#include "ups.hpp"

// Class constructors

IPS::IPS() {

}


// Mutators

bool IPS::load_patch(std::string f_name) {

    std::ifstream ips_read;
    ips_read.open (f_name, std::ios::binary);

    if (ips_read.is_open()) {
        char buffer[UPS_HEADER.length()]; // <- Coming from #define in C, this is cursed
        ips_read.read(buffer, UPS_HEADER.length());

        std::cout << buffer;

        while(true) {
            struct IPS_Record record;

            this->records.push_back(record);
        }
    }

    return false;
}
