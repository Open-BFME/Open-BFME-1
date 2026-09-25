// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
#include <windows.h>
#include <string.h>
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *);
extern int Rva012AA3D8[1024];
extern void Rva00882F20SetFlag();
extern void Rva00882F30SetFlag();
class Rva00882F80 { public: static void store(int); };
extern void Rva00882FB0ResizeDwordTable(unsigned int);
extern void d_00883040(unsigned int, unsigned int);

// Retail 00105DF0 reads the 1024-dword table at VA012AA3D8.
// Signed division by two truncates toward zero before the count is passed
// to the table setter. PE imports independently identify GetCommandLineA,
// _strlwr and strstr. The spaces in the last two switch strings are retail.
void Rva00105DF0()
{
    for (int index = 1; index < 1025; ++index)
        d_00883040(index * 4, Rva012AA3D8[index - 1] / 2);
    char *commandLine = _strlwr(GetCommandLineA());
    bool zeroFill;
    if (commandLine && strstr(commandLine, "-nozerofillmemory") &&
        !strstr(commandLine, "--nozerofillmemory"))
        zeroFill = false;
    else
        zeroFill = true;
    Rva00882F20SetFlag();
    if (commandLine) {
        if (!zeroFill)
            Rva00882F30SetFlag();
        if (strstr(commandLine, " -poolbigblocks"))
            Rva00882FB0ResizeDwordTable(0x400000);
        if (strstr(commandLine, " -bigmemorysentinals"))
            Rva00882F80::store(50);
    }
}
