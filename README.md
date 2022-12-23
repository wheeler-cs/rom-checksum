# rom-checksum
A program for ensuring the validity of ROMs using checksums.

# Compilation and Execution
## Required Environment
This program requires a C++ compiler capable of implementing the C++11 standard. The only external library used is the
[Crypto++ library](https://github.com/weidai11/cryptopp) for generating hashes. Installation instructions will vary
from platform to platform. For Windows, a wrapper for the `dirent.h` file that is commonly found on Linux systems will
also need to be obtained and implemented into your workflow.

## Compiling
Once the environment is set up, the program can be compiled as follows:

`> git clone https://github.com/wheeler-cs/rom-checksum`

`> cd rom-checksum`

`> mkdir build`

`> make all`

If you desire multithreading, `make all-mt` can be issued instead. This will handle compiling all multithread-enabled
files.

## Usage
The executable "./build/rom-check" will be generated. The `-h` option can be used to get a list of parameters that can
be used during execution. If no parameters need to be specified, `make run` can be issued to run the program with its
default behavior.

## Data Directories
ROMs should be placed in the "roms/" folder and XML files should be placed in the "data/" folder. Bother of these
folders should be in the same directory as the "rom-check" executable. These directories can also be overwritten with
the `-r` and `-d` arguments respectively.

## Data Files
The format of the data files used is the same as those used by [Redump](http://redump.org/) or
[No-Intro](https://datomatic.no-intro.org/). Custom XML files could also be written to follow this style and allow for
more files to be hashed, such as executables or data files.

# Legal
## Warranty
The program and source code are provided as-is without any sort of warranty or guarantee of fitness for an application
of any kind. The end-user, and the end-user alone, accepts full responsibility for the consequences of using anything
taken or derived (directly or indirectly) from the content of this repository. This includes any potential loss of
data or other kinds of damages.

## License
All source code, unless specified otherwise, is licensed under the MIT license. For more information regarding what all
that entails, please refer to the "LICENSE" file or [this page](https://mit-license.org/).

## Piracy
This tool is not developed with the intent of facilitating the act of piracy. No copyrighted material (including video
game ROMs, video game source code, console BIOS, etc.) can be generated, copied, downloaded, or otherwise manifested
using the software present in this repository.

# Contributing
I am always interested in what other people think needs to be changed or improved with the program. Pull requests are
also welcome, so long as they are conducive to the progress of the program.
