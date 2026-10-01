// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Constructor: copy the name into a StringBase, look it up through the
// singleton at 0x012ED604, store the pointer at this+0.

#include "ascii_string.h"

class Rva0007F560Factory
{
public:
	void *lookup( const AsciiString &name );
};

class Rva000946B0G;
extern Rva000946B0G *g_rva000946b0;
#define g_rva0007F560Factory ((Rva0007F560Factory *)g_rva000946b0)

class Rva0007F560
{
public:
	Rva0007F560( const char *name );

private:
	void *m_ptr;
};

Rva0007F560::Rva0007F560( const char *name )
{
	AsciiString tmp( name );
	m_ptr = g_rva0007F560Factory->lookup( tmp );
}
