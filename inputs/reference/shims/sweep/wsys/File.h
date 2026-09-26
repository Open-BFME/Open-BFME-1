/*
**  Westwood wsys/File.h shim — minimal declarations for sweep compilation
*/

#pragma once

#include <wpaudio/altypes.h>

class FileClass {
public:
    static FileClass* Open(const char* name);
    int Size();
    int Read(void* buffer, int size);
    int Seek(int pos, int whence);
    void Close();
};

