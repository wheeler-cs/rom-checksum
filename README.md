# rom-checksum
A program for verifying the checksums of ROM of files.

# Compilation and Usage
This program utilize the Crypto++ library and the C++ 11 standard. Installation instructions for Crypto++ will vary from platform to platform, but the source code and latest releases can be found on the [Crypto++ GitHub Page](https://github.com/weidai11/cryptopp).

The program can be compiled on Linux as follows:
<code>
    <p>cd rom-checksum
    <p>mkdir build
    <p>make all
</code>

This will output an executable named "rom-checksum" in the "build" directory. Execute the program with the "-h" argument for a list of commands that can be used.

The default directory for XML files is the <code>data</code> directory, while the default directory for ROMs is the <code>roms</code> directory. This can be changed with the <code>-d</code> and <code>-r</code> arguments respectively.

Compiling on Windows will most likely involve adding the Crypto++ library to Visual Studio and compiling within that.

# XML Data Files
XML data files can be obtained from various sources. The most common source for disc-based systems will be [Redump](http://redump.org/), and [No-Intro's Dat-o-matic](https://datomatic.no-intro.org/) will have cartridge-based systems. I want to make abundantly clear that these are <b>not</b> ROMs. They are data files containing the hash values of various games that have been compiled by numerous users.

# Legal
This program is provided as-is with absolutely no warranty and no guarantee of fitness for an application of any kind. This program also cannot be used to create, transfer, or otherwise aid in the illegal distribution of copyrighted material. This tool is intended only to verify dumps of roms made by the user for personal use.
