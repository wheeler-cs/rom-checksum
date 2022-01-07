#include "xml.h"

Xml::Xml() {
    name = "";
    description = "";
    author = "";
    homepage = "";
    list_size = 0;
}


Xml::Xml (std::string n, 
          std::string d,
          std::string a,
          std::string h) {

    name = n;
    description = d;
    author = a;
    homepage = h;
    list_size = 0;
}


std::string Xml::get_name() {
    return name;
}


std::string Xml::get_description() {
    return description;
}


std::string Xml::get_author() {
    return author;
}


std::string Xml::get_homepage() {
    return homepage;
}


Rom_File Xml::get_game (unsigned int index) {
    return list [index];
}


Rom_File* Xml::get_list() {
    return &list[0];
}


unsigned int Xml::get_list_size() {
    return list_size;
}


void Xml::set_name (std::string s) {
    name = s;
}


void Xml::set_description (std::string s) {
    description = s;
}


void Xml::set_author (std::string s) {
    author = s;
}


void Xml::set_homepage (std::string s) {
    homepage = s;
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


void Xml::set_list_size (unsigned int i) {
    list_size = i;
}


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


std::vector <char> load_file (std::string f_name) {
    std::vector <char> xml_data;

    std::ifstream xml_read;
    xml_read.open (f_name.c_str());

    if (xml_read.is_open()) {
        char buffer;

        while (true) {
            xml_read >> std::noskipws >> buffer;
            if (xml_read.eof())
                break;
            
            xml_data.push_back (buffer);

        }

        xml_read.close();
    }

    return xml_data;
}


bool verify_xml (std::vector <char> &xml_data) {
    std::string header;

    for (int i = 0; i < XML_HEADER_SIZE; i++) {
        header += xml_data[i];
    }

    if (header == XML_HEADER)
        return true;
    else
        return false;
}


std::string find_in_xml_header (std::string keyword, std::vector <char> &xml_data) {
    /* This function is a mess, and I'm not very good at writing text parsers to begin with. In the future, this code
     * may be rewritten for readability and speed (it double-checks characters in a lot of places). For now, it serves
     * its purpose pretty alright.
    */
    const std::string keyword_tag_start = '<' + keyword + '>',
                      keyword_tag_end = "</" + keyword + '>',
                      header_tag_start = "<header>",
                      header_tag_end = "</header>";

    unsigned int keyword_start = 0, keyword_end = 1, 
                 header_start = 0, header_end = 1;

    std::string data_string = "";

    // Find the <header> and </header> positions
    for (unsigned int i = 0; i < xml_data.size(); i++) {
        // Search for the <header> tag
        if (xml_data[i] == header_tag_start[0]) {
            for (unsigned int j = 1; j < header_tag_start.size(); j++) {
                if (xml_data[i+j] != header_tag_start[j])
                    break;
                else if (j == (header_tag_start.size() - 1)) {
                    header_start = i + j;
                    break;
                }
            }
        }
        // Search for the </header> tag
        if (xml_data[i] == header_tag_end[0]) {
            for (unsigned int j = 1; j < header_tag_end.size(); j++) {
                if (xml_data[i+j] != header_tag_end[j])
                    break;
                else if (j == (header_tag_end.size() - 1)) {
                    header_end = (i + j) - (header_tag_end.size() - 1);
                    break;
                }
            }
        }
        if ((header_start > 0) && (header_end > 1))
            break;
    }

    // Find the keyword tag start and end locations
    if ((header_start > 0) && (header_end > 1)) {
        for (unsigned int i = header_start; i < header_end; i++) {
            // Find the keyword start tag location
            if (xml_data[i] == keyword_tag_start[0]) {
                for (unsigned int j = 1; j < keyword_tag_start.size(); j++) {
                    if (xml_data[i+j] != keyword_tag_start[j])
                        break;
                    else if (j == (keyword_tag_start.size() - 1)) {
                        keyword_start = i + j;
                        break;
                    }
                }
            }
            // Find the keyword end tag location
            if (xml_data[i] == keyword_tag_end[0]) {
                for (unsigned int j = 1; j < keyword_tag_end.size(); j++) {
                    if (xml_data[i+j] != keyword_tag_end[j])
                        break;
                    else if (j == (keyword_tag_end.size() - 1)) {
                        keyword_end = (i + j) - (keyword_tag_end.size() - 1);
                        break;
                    }
                }
            }
            if ((keyword_start > 0) && (keyword_end > 1))
                break;
        }
    }

    // Get the string of data stored in the keyword tag
    if ((keyword_start > 0) && (keyword_end > 1)) {
        for (unsigned int i = keyword_start + 1; i < keyword_end; i++) {
            data_string += xml_data[i];
        }
    }

    return data_string;

}


unsigned int find_in_xml_body (std::string keyword, Rom_File rom_list[], std::vector <char> &xml_data) {

    // Set up keywords for search operation
    const std::string keyword_tag_start = '<' + keyword,
                      keyword_tag_end = "/>";

    unsigned int keyword_start = 0, keyword_end = 1, list_size = 0;

    std::vector <char> data_string;

    // Search for the locations of where the keyword tag starts and ends
    for (unsigned int i = 0; i < xml_data.size(); i++) {
        if (xml_data[i] == keyword_tag_start[0]) {
            for (unsigned int j = 1; j < keyword_tag_start.size(); j++) {
                if (xml_data[i+j] != keyword_tag_start[j])
                    break;
                else if (j == (keyword_tag_start.size() - 1)) {     // Start tag match has been found
                    keyword_start = i + j;
                    break;
                }
            }
        }
        if (xml_data[i] == keyword_tag_end[0]) {
            for (unsigned int j = 1; j < keyword_tag_end.size(); j++) {
                if (xml_data[i+j] != keyword_tag_end[j])
                    break;
                else if (j == (keyword_tag_end.size() - 1)) {       // End tag match has been found
                    keyword_end = (i + j) - (keyword_tag_end.size() - 1);
                    break;
                }
            }
        }
        // If the keyword start and end locations have been found
        if ((keyword_start != 0) && (keyword_end > keyword_start)) {

            for (unsigned int j = keyword_start + 1; j < keyword_end; j++) {
                data_string.push_back (xml_data[j]);
            }
            // Load tag data into a Rom_File class instance if the list is not full
            std::string size_str = "";
            unsigned long long converted_size = 0;

            if (list_size + 1 < MAX_LIST_SIZE) {
                rom_list[list_size].set_name (find_in_char_vector ("name", data_string));
                rom_list[list_size].set_md5 (find_in_char_vector ("md5", data_string));
                rom_list[list_size].set_sha1 (find_in_char_vector ("sha1", data_string));
                size_str = find_in_char_vector ("size", data_string);

                // Error-catching code for stoull conversion function
                try {
                    converted_size = stoull (size_str, nullptr, 10);
                    rom_list[list_size].set_size (converted_size);
                }
                catch (const std::invalid_argument &ia) {
                    std::cerr << "\n! String Conversion Error: " << ia.what() << " IA"
                              << "\n\tEntry: " << rom_list[list_size].get_name()
                              << "\n\t Size: " << size_str;
                }
                catch (const std::out_of_range &oor) {
                    std::cerr << "\n! String Conversion Error: " << oor.what() << " OOR"
                              << "\n\tEntry: " << rom_list[list_size].get_name()
                              << "\n\t Size: " << size_str;
                }

                list_size++;
            }
            else
                break;

            // Reset variables for next search and load
            data_string.clear();
            keyword_start = 0;
            keyword_end = 1;
        }
    }

    return list_size;
}



std::string find_in_char_vector (std::string keyword, std::vector <char> &data_string) {

    // Set up keywords for search operation
    const std::string keyword_start_tag = keyword + "=\"",
                      keyword_end_tag = "\"";

    unsigned int keyword_start = 0, keyword_end = 1;

    std::string keyword_data = "";

    // Search for the data within the tag
    for (unsigned int i = 0; i < data_string.size(); i++) {
        if (data_string[i] == keyword_start_tag[0]) {
            for (unsigned int j = 1; j < keyword_start_tag.size(); j++) {
                if (data_string[i+j] != keyword_start_tag[j])
                    break;
                else if (j == (keyword_start_tag.size() - 1)) {
                    keyword_start = i + j;
                    break;
                }
            }
        }
        if (data_string[i] == keyword_end_tag[0]) {
            keyword_end = i;
        }

        // If the desired data has been found in the character vector
        if ((keyword_start != 0) && (keyword_end > keyword_start)){
            // Convert characters in vector into a C++ string that can be returned
            for (unsigned int j = keyword_start + 1; j < keyword_end; j++) {
                if (data_string[j] != '"')
                    keyword_data += data_string[j];
            }

            break;
        }
    }

    return keyword_data;
}