/**
 * @file xml.cpp
 * @author Anna Wheeler (wheeler-cs)
 * @date May 26, 2025
 * 
 * @brief Contains function definitions for the `Xml` class, along with additional supporting functions.
 * 
 */

#include "xml.hpp"

#include "file.hpp"

// Class constructors

Xml::Xml() {
    name = "";
    description = "";
    author = "";
    homepage = "";
    list_size = 0;
}


Xml::Xml (std::string n, std::string d, std::string a, std::string h) {

    name = n;
    description = d;
    author = a;
    homepage = h;
    list_size = 0;
}


bool Xml::set_rom (Rom_File r, unsigned int index) {
    if (index < MAX_LIST_SIZE) {
        list[index] = r;
        return true;
    }

    return false;
}


bool Xml::append_rom (Rom_File r) {
    if (list_size < MAX_LIST_SIZE) {
        list[list_size] = r;
        list_size++;
        return true;
    }

    return false;
}


// =====================================================================================================================
// Rom searching functions

Rom_File* Xml::search_rom_md5 (std::string key) {
    for (unsigned int i = 0; i < list_size; i++) {
        if (key == list[i].get_md5())
            return &list[i];
    }

    return NULL;
}


Rom_File* Xml::search_rom_sha1 (std::string key) {
    for (unsigned int i = 0; i < list_size; i++) {
        if (key == list[i].get_sha1())
            return &list[i];
    }

    return NULL;
}


Rom_File* Xml::search_rom_size (unsigned long long key) {
    for (unsigned int i = 0; i < list_size; i++) {
        if (key == list[i].get_size())
            return &list[i];
    }

    return NULL;
}


Xml * allocate_Xml(unsigned int size, bool f_silence)
{
    if(!f_silence)
    {
        std::cout << "\nAllocating XML memory..." << std::flush;
    }

    return(new Xml[size]);
}


void deallocate_Xml(Xml * xml_ptr)
{
    delete[] xml_ptr;
    xml_ptr = NULL;
}


bool load_file (std::string f_name, std::vector <std::string> &xml_data)
{
    // Store original size of data for load success check
    unsigned int starting_data_len = xml_data.size();

    std::ifstream xml_read;
    xml_read.open(f_name.c_str());

    if (xml_read.is_open()) {
        std::string buffer;

        getline(xml_read, buffer);
        while(!(xml_read.eof())) {
            // Check for certain characters and delete them if necessary
            buffer.erase(remove(buffer.begin(), buffer.end(), '\r'), buffer.end());   // Carridge Return (thanks Windows)
            buffer.erase(remove(buffer.begin(), buffer.end(), '\t'), buffer.end());   // Tab

            xml_data.push_back(buffer);

            getline(xml_read, buffer);
        }

        xml_read.close();
    }

    // See if any change is size occurred
    return(starting_data_len > xml_data.size());
}


// Populate a list of XML files in the 'data' directory
unsigned int populate_Xml (Xml xml_data[], std::string xml_dir, unsigned int size, bool is_silent) {
    std::string* dir_list {new std::string[size]};
    unsigned int list_size {0};

    std::vector <std::string> temp_xml_data;

    list_size = populate_dir_entries (xml_dir, dir_list, size);

    if(!is_silent)
        std::cout << "\nLoading XML data..." << std::flush;

    for (unsigned int i = 0; i < list_size; i++) {
        load_file (dir_list[i], temp_xml_data);

        // If XML file is valid, load data that is found in header into Xml class
        if (verify_xml (temp_xml_data)) {
            xml_data[i].set_name (find_in_xml_header ("name", temp_xml_data));
            xml_data[i].set_description (find_in_xml_header ("description", temp_xml_data));
            xml_data[i].set_author (find_in_xml_header ("author", temp_xml_data));
            xml_data[i].set_homepage (find_in_xml_header ("homepage", temp_xml_data));
            xml_data[i].set_list_size (find_in_xml_body ("rom", xml_data[i].get_list(), temp_xml_data));
        }
        else {
            std::cerr << '\n' << dir_list[i] << " is not a valid XML file!";
        }

        temp_xml_data.clear();
    }

    delete[] dir_list;

    return list_size;
}

// Ensure that an input file has the XML_HEADER on its first line
bool verify_xml (std::vector <std::string> &xml_data) {

    if (xml_data[0] == XML_HEADER)
    {
        return true;
    }

    return false;
}


// Search for specific text within the XML's <header> section
std::string find_in_xml_header (std::string keyword, std::vector <std::string> &xml_data) {
    const std::string keyword_start_tag {'<' + keyword + '>'},
                      keyword_end_tag {"</" + keyword + '>'},
                      header_start_tag {"<header>"},
                      header_end_tag {"</header>"};

    unsigned int header_start_pos {0}, header_end_pos {0};

    std::string data_string {""};   // Variable to be returned at the end of the function

    // Find the <header> and </header> locations
    for (unsigned int line_i = 0; line_i < xml_data.size(); line_i++) {
        // Check for the header_start_tag
        if (xml_data[line_i] == header_start_tag) {
            header_start_pos = line_i;
        }
        // Check for the header_end_tag
        else if (xml_data[line_i] == header_end_tag) {
            header_end_pos = line_i;
        }
        // Stop loop if both the header start and end tags have been found
        if ((header_start_pos != 0) && (header_start_pos < header_end_pos))
            break;
    }

    // If the headers were successfully found, find the keyword within the headers 
    if ((header_start_pos != 0) && (header_end_pos != 0)) {
        size_t keyword_start_pos {}, keyword_end_pos {};

        // Search lines in header for desired information
        for (unsigned int header_i = header_start_pos; header_i < header_end_pos; header_i++) {
            keyword_start_pos = xml_data[header_i].find (keyword_start_tag);
            keyword_end_pos = xml_data[header_i].find (keyword_end_tag);
            if ((keyword_start_pos != std::string::npos) && (keyword_end_pos != std::string::npos)) {
                for (unsigned int line_i = keyword_start_pos + keyword_start_tag.size(); line_i < keyword_end_pos; line_i++) {
                    data_string += xml_data[header_i][line_i];
                }
                break;
            }
        }
    }

    return data_string;
    // Empty string = No match found
    // String with data = Match found
}


// Search for specific text within the XML's body
unsigned int find_in_xml_body (std::string keyword, Rom_File rom_list[], std::vector <std::string> &xml_data) {
    const std::string keyword_start_tag {'<' + keyword},
                      keyword_end_tag {"/>"};

    unsigned int list_size {0};

    std::string data_string {""};

    size_t keyword_start_pos {}, keyword_end_pos {};

    // Search through XML data for all instances of desired information
    for (unsigned int line_i = 0; line_i < xml_data.size(); line_i++) {
        keyword_start_pos = xml_data[line_i].find (keyword_start_tag);
        keyword_end_pos = xml_data[line_i].find (keyword_end_tag);

        // A match has been found for the data
        if ((keyword_start_pos != std::string::npos) && (keyword_end_pos != std::string::npos)) {
            // Variables used to convert string to long
            std::string size_str {""};
            unsigned long long size_long {0};

            data_string = "";

            for (unsigned int data_i = keyword_start_pos + keyword_start_tag.size(); data_i < keyword_end_pos; data_i++) {
                data_string += xml_data[line_i][data_i];
            }

            if (list_size + 1 < MAX_LIST_SIZE) {
                // Load data from line into rom structure
                rom_list[list_size].set_name (find_in_string ("name", data_string));
                rom_list[list_size].set_md5  (find_in_string ("md5" , data_string));
                rom_list[list_size].set_sha1 (find_in_string ("sha1", data_string));

                // Attempt to convert data related to size from a string to a long
                size_str = find_in_string ("size", data_string);
                try {
                    size_long = stoull (size_str, nullptr, 10);
                    rom_list[list_size].set_size (size_long);
                }
                catch (const std::invalid_argument &bad_arg) {  // Argument was not an integer
                    std::cerr << "\n! String to Long Conversion Error: " << bad_arg.what() << ", Bad Arg."
                              << "\n\tEntry: " << rom_list[list_size].get_name()
                              << "\n\t Size: " << size_str;
                }
                catch (const std::out_of_range &bad_range) {    // Argument is out of range
                    std::cerr << "\n! String to Long Conversion Error: " << bad_range.what() << ", Out of Range"
                              << "\n\tEntry: " << rom_list[list_size].get_name()
                              << "\n\t Size: " << size_str;
                }

                list_size++;
            }
            else {
                break;
            }
        }
    }

    return list_size;
}


// Find a string of text within a string
std::string find_in_string (std::string keyword, std::string input) {

    const std::string keyword_start_tag {keyword + "=\""},
                      keyword_end_tag {"\""};

    size_t keyword_start_pos {}, keyword_end_pos {};

    std::string data_string {""};

    // Find the location of the start tag
    keyword_start_pos = input.find (keyword_start_tag);

    if (keyword_start_pos != std::string::npos) {
        // Find the end tag in a location that comes after the start tag
        keyword_end_pos = input.find (keyword_end_tag, keyword_start_pos + keyword_start_tag.size() + 1);

        // Data has been found if the start tag and end tag are not npos
        if ((keyword_end_pos != std::string::npos) && (keyword_end_pos > keyword_start_pos)) {
            for (unsigned int j = keyword_start_pos + keyword_start_tag.size(); j < keyword_end_pos; j++) {
                data_string += input[j];
            }
        }
    }

    return data_string;
}
