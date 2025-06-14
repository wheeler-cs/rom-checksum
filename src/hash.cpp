/**
 * @file hash.cpp
 * @author Anna Wheeler (wheeler-cs)
 * 
 * @brief File contains a single-threaded and multi-threaded definition for generate_file_info and support functions for
 * the multi-threaded version. MULTITHREAD_ENABLE decides which of these functions are used.
 * 
 * @see hash.hpp
 * 
 */

#include "hash.hpp"

#ifdef MULTITHREAD_ENABLE

#include <thread>

void generate_file_info (std::string f_name, std::string &md5, std::string &sha1, unsigned long long &size) {

    std::thread *t_md5 = new std::thread {generate_md5, f_name, &md5};
    std::thread *t_sha = new std::thread {generate_sha1, f_name, &sha1};
    std::thread *t_fsz = new std::thread {calculate_file_size, f_name, &size};

    t_md5->join();
    t_sha->join();
    t_fsz->join();

    delete t_md5;
    delete t_sha;
    delete t_fsz;

}

#else

void generate_file_info (std::string f_name, std::string &md5, std::string &sha1, unsigned long long &size) {
    // Reset file info variables for next calculation
    md5 = sha1 = "";
    size = 0;

    generate_md5(f_name, &md5);
    generate_sha1(f_name, &sha1);
    calculate_file_size(f_name, &size);
}

#endif


void generate_md5 (std::string f_name, std::string *md5) {
    *md5 = "";

    Weak1::MD5 hash;

    HashFilter h_filter (hash, new HexEncoder (new StringSink (*md5)));
    ChannelSwitch c_switch;
    c_switch.AddDefaultRoute (h_filter);
    FileSource (f_name.c_str(), true, new Redirector (c_switch));
    // Ensure hash is all lowercase
    for (unsigned int i = 0; i < md5->size(); i++) {
        (*md5)[i] = (char) tolower ((*md5)[i]);
    }
}


void generate_sha1 (std::string f_name, std::string *sha1) {
    *sha1 = "";

    SHA1 hash;
    HashFilter h_filter (hash, new HexEncoder (new StringSink (*sha1)));
    ChannelSwitch c_switch;
    c_switch.AddDefaultRoute (h_filter);
    FileSource (f_name.c_str(), true, new Redirector (c_switch));
    // Ensure hash is all lowercase
    for (unsigned int i = 0; i < sha1->size(); i++) {
        (*sha1)[i] = (char) tolower ((*sha1)[i]);
    }
}


void calculate_file_size (std::string f_name, unsigned long long *f_size) {
    std::ifstream s_check (f_name.c_str());
    if (s_check.is_open()) {
        s_check.seekg (0, std::ios::end);
        *f_size = (unsigned long long) s_check.tellg();
        s_check.close();
    }
}
