// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// Pristine-map embed helper with the private EDI Xfer parameter.
// Evidence: targets/game/reverse/identity_evidence/00112a50-embedPristineMap.md
#include "ascii_string.h"
#include "xfer.h"

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *memory);

class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};

class File;

// This interface view covers only the decoded File virtual slots used here.
class Rva00112A50FileView
{
public:
    enum seekMode { START, CURRENT, END };
    virtual void slot00();
    virtual bool open(const char *filename, int access);
    virtual void close();
    virtual int read(void *buffer, int bytes);
    virtual int write(const void *buffer, int bytes);
    virtual int seek(int bytes, seekMode mode);
};

class FileSystem
{
public:
    File *openFile(const char *filename, int access);
};
extern FileSystem *TheFileSystem;

// The shared Xfer header reserves these two BFME block-management slots.
class Rva00112A50BlockView
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual int beginBlock(const char *name);
    virtual void endBlock();
};

// ?embedPristineMap@@YAXVAsciiString@@PAVXfer@@@Z
static __declspec(noinline) void embedPristineMap(AsciiString map, Xfer *xfer)
{
    Rva00112A50FileView *file = reinterpret_cast<Rva00112A50FileView *>(TheFileSystem->openFile(map.str(), 0x41));
    if (file == 0)
        throw XferException(5, 0);
    unsigned int size = file->seek(0, Rva00112A50FileView::END);
    file->seek(0, Rva00112A50FileView::START);
    char *buffer = (char *)::operator new[](size);
    if (buffer == 0)
        throw XferException(5, 0);
    if (file->read(buffer, size) != size)
    {
        ::operator delete[](buffer);
        throw XferException(5, 0);
    }
    file->close();
    reinterpret_cast<Rva00112A50BlockView *>(xfer)->beginBlock("PristineMap");
    (*xfer) == size;
    xfer->XferRawBytes(buffer, size);
    reinterpret_cast<Rva00112A50BlockView *>(xfer)->endBlock();
    ::operator delete[](buffer);
}

// ?forceEmbedPristineMap@@YAXVAsciiString@@PAVXfer@@@Z absent-from-retail
void forceEmbedPristineMap(AsciiString map, Xfer *xfer)
{
    embedPristineMap(map, xfer);
}
