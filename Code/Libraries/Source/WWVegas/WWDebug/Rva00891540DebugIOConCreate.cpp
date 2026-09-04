// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /Oy-

#include <new>

extern void *DebugAllocMemory(unsigned size);

class Rva00891540DebugIOCon
{
public:
    __declspec(noinline) Rva00891540DebugIOCon(void);

private:
    char m_body[0x110];
};

__declspec(noinline) Rva00891540DebugIOCon::Rva00891540DebugIOCon(void)
{
}

class Rva00891540DebugIOConFactory
{
public:
    static Rva00891540DebugIOCon *Create(void);
};

// ?Create@Rva00891540DebugIOConFactory@@SAPAVRva00891540DebugIOCon@@XZ
Rva00891540DebugIOCon *Rva00891540DebugIOConFactory::Create(void)
{
    return new (DebugAllocMemory(sizeof(Rva00891540DebugIOCon)))
        Rva00891540DebugIOCon();
}
