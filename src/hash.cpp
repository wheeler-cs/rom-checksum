#include "hash.h"


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