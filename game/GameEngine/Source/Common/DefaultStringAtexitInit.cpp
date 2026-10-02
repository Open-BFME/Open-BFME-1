// cl: /DNDEBUG /MD /EHsc
struct BfmeStringData3AF0
{
    unsigned short m_refCount;
};

// The shared empty string block at 0x012D5298 is defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp as
// EAStringC::StringDataC g_rva012D5298Empty.  Only the refcount word at +0 is
// touched here, so the TU keeps its own view of the block and casts at use.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;
void bfmeGoEMIa();
void bfmeGoEMIb();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DC50InitializeDefaultString()
{
    ++((BfmeStringData3AF0 *)&g_rva012D5298Empty)->m_refCount;
    atexit(bfmeGoEMIa);
}

void bfmeRva00C6DC70InitializeDefaultString()
{
    ++((BfmeStringData3AF0 *)&g_rva012D5298Empty)->m_refCount;
    atexit(bfmeGoEMIb);
}
