#ifndef UTIL_HH
#define UTIL_HH

#include <fstream>
#include <filesystem>
#include <string>
#include <zlib.h>
#include <assert.h>
#include <sha256.hh>
using std::string;

namespace fs = std::filesystem;

class Util {

    public:
        string GetFileHash(string path);
        void Packager(string path);
        int Compress(string source, string dest);
        int Decompress(string source, string dest);

};


#endif 