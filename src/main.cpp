/**
 * @file main.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
 * 
 * File contains main, which interfaces with other functions to load XML data, generate information for input files,
 * and handle memeory management.
 * 
*/

#include "arguments.hpp"
#include "patch.hpp"
#include "verify.hpp"


int main(int argc, char** argv) {
    Arguments args = Arguments();
    if(argc > 1)
    {
        args = Arguments(argc, argv);
    }

    if((args.get_op_mode() != MODE_STOP) && (args.get_op_mode() != MODE_UNDEFINED))
    {
        std::cout << "Running...";
        switch(args.get_op_mode())
        {
            case MODE_VERIFY:
                do_verification(&args);
                break;
            case MODE_PATCH:
                do_patch(&args);
                break;
        }
    }

    // Terminate program
    std::cout << "\n\nOperation complete! Press <enter> to continue..." << std::endl;
    std::string buffer;
    getline(std::cin, buffer);
    return 0;
}
