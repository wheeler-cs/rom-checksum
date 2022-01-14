#include "file.h"

// Get a list of files within a given directory
unsigned int populate_dir_entries (std::string directory, std::string entry_list [], unsigned int list_size) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    std::string dir_string = "";

    unsigned int f_quant = 0, temp_int = 0;

    // Open directory and get list of files within that directory
    if ((dir_ptr = opendir (directory.c_str())) != NULL) {
        for (f_quant = 0; ((dirent_ptr = readdir (dir_ptr)) != NULL) && (f_quant < list_size); ) {
            dir_string = directory + '/' + dirent_ptr->d_name;    // Cast C-string to C++ string

            // Ignore file if it's the . or .. directories
            if ((dir_string == directory + "/.") || (dir_string == directory + "/..")) {
                continue;
            }
            // Recursively call funciton if a directory is found
            else if (dirent_ptr->d_type == DT_DIR) {
                std::string* temp_list = new std::string[list_size];
                temp_int += populate_dir_entries (dir_string, temp_list, list_size);

                for (unsigned int j = f_quant; (j < (f_quant + temp_int)) && (j < list_size); j++) {
                    entry_list[j] = temp_list[j - f_quant];
                }

                f_quant += temp_int;
                temp_int = 0;
                delete[] temp_list;
            }
            // Add file to list
            else {
                entry_list[f_quant] = dir_string;
                f_quant++;
            }
        }
        closedir (dir_ptr);
    }
    else {
        std::cerr << "\nCould not open " << directory << " for reading!";
    }

    return f_quant;
}