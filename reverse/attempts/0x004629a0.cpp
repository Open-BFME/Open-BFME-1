// ?_bfme_closeAptScreen@@YAXABVAsciiString@@@Z
// partial score=0.4 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// ?_bfme_closeAptScreen@@YAXABVAsciiString@@@Z
// Retail 0x004629A0, 97 bytes. Copies the name, builds a hashtable iterator
// against the global at 0x012F19A4 via begin() at ILT 0x0001BDC9, hands both
// to 0x00462540, then thiscall-searches the WindowManager at 0x012F1990
// (ILT 0x0000F547 -> 0x00461040).

#include "StringInline.h"

struct HtIterator
{
	void *node;
	void *table;
};

class NameTable
{
public:
	HtIterator begin();
};

class WindowManager
{
public:
	void findScreen( const AsciiString &name );
};

void eraseScreen( HtIterator it, AsciiString name );

NameTable *const g_nameTable = (NameTable *)0x012F19A4;
WindowManager *const g_windowManager = (WindowManager *)0x012F1990;

// ?_bfme_closeAptScreen@@YAXABVAsciiString@@@Z present-unmatched
void _bfme_closeAptScreen( const AsciiString &name )
{
	eraseScreen( g_nameTable->begin(), name );
	g_windowManager->findScreen( name );
}
