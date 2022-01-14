#include "hash.h"


// Generate the md5 hash value of a file
std::string generate_md5 (std::string f_name) {
    std::string str_md5;
    Weak1::MD5 md5;

    HashFilter h_filter (md5, new HexEncoder (new StringSink (str_md5)));

    ChannelSwitch c_switch;
    c_switch.AddDefaultRoute (h_filter);

    FileSource (f_name.c_str (), true, new Redirector (c_switch));

    // Ensure all alphabetical characters of the hash are lower-case
    for (unsigned int i = 0; i < str_md5.size(); i++)
        str_md5[i] = (char) tolower (str_md5[i]);

    return str_md5;
}


// Generate the sha1 hash value of a file
std::string generate_sha1 (std::string f_name) {
    std::string str_sha1;
    SHA1 sha1;

    HashFilter h_filter (sha1, new HexEncoder (new StringSink (str_sha1)));

    ChannelSwitch c_switch;
    c_switch.AddDefaultRoute (h_filter);

    FileSource (f_name.c_str(), true, new Redirector (c_switch));

    // Ensure all alphabetical characters of the hash are lower-case
    for (unsigned int i = 0; i < str_sha1.size(); i++)
        str_sha1[i] = (char) tolower (str_sha1[i]);

    return str_sha1;
}


// Get the size of a file as a quantity of bytes
unsigned long long generate_f_size (std::string f_name) {
    unsigned long long f_size = 0;

    std::ifstream size_check;
    size_check.open (f_name.c_str(), std::ios::binary);

    if (size_check.is_open()) {
        size_check.seekg (0, std::ios::end);
        f_size = (unsigned long long) size_check.tellg();
    }

    return f_size;
}