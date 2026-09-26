// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// FontCharsClass::~FontCharsClass at 0x00940010 (348 B), the BFME shape of the
// Zero Hour destructor in render2dsentence.cpp. Identity: the matched scalar
// deleting destructor at 0x00940770 (FontCharsClassDeletingDestructor.cpp)
// calls this body, and it installs the FontCharsClass vtable 0x0113CE8C that
// the matched constructor at 0x00940610 installs.
//
// BFME moved the bitmap and memory DC out of the font into one process-wide,
// reference-counted FontCharsClassGdiState (constructed at 0x0093C340, pointer
// at VA 0x0134AEAC). The destructor drains the buffer list, frees the font,
// frees the character arrays and drops its reference on that shared state.
//
// Retail's unwind map (tools/eh_info.py 0x00940010) has four states: the
// RefCountClass base, +0x0c, +0x10 and +0x44. The +0x450 tree has none and
// no state is written around the inlined buffer-list destructor, so retail
// knew that operator delete, operator delete[] and Free_Character_Arrays do
// not throw (docs/shape_levers.md, the throw() row for EH state stores).
void __cdecl operator delete(void *) throw();
void __cdecl operator delete[](void *) throw();

#include "always.h"
#include "refcount.h"
#include "wwstring.h"
#include "vector.h"
#include <windows.h>

// Only the destructor of the +0x450 STLport tree is called here (out of line,
// 0x0093FA90), so the tree is a shell reproducing the ledger's decorated name.
struct Gen_t_0093fa90_p4pod
{
	char m_body[4];
};

namespace _STL
{
template <class T1, class T2> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	~_Rb_tree();

private:
	char m_body[12];
};
}

typedef _STL::pair<const int, Gen_t_0093fa90_p4pod> FontCharsTree00940010Pair;
typedef _STL::_Rb_tree<int, FontCharsTree00940010Pair, _STL::_Select1st<FontCharsTree00940010Pair>,
	_STL::less<int>, _STL::allocator<FontCharsTree00940010Pair> > FontCharsTree00940010;

struct FontCharsClassCharDataStruct;
class FontCharsBuffer;

// A BufferList entry as this body reads it: the array at +0 is deleted with
// delete[], then the entry itself with delete.
struct FontCharsBufferEntry00940010
{
	unsigned short *m_ownedArray;
};

// Field names follow the matched ??0FontCharsClassGdiState@@QAE@XZ in
// render2dsentence.cpp; the release is the body retail also keeps out of
// line at 0x0093C400.
class FontCharsClassGdiState
{
public:
	~FontCharsClassGdiState()
	{
		if (m_bitmap != 0) {
			::SelectObject(m_dc, m_oldBitmap);
			::DeleteObject(m_bitmap);
			m_bitmap = 0;
		}
		if (m_dc != 0) {
			::DeleteDC(m_dc);
			m_dc = 0;
		}
	}

	int m_refs;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;
	void *m_bits;
	HDC m_dc;
};

// VA 0x0134AEAC: the shared GDI state the constructor at 0x00940610 creates.
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

class FontCharsClass : public W3DMPO, public RefCountClass
{
public:
	FontCharsClass();
	virtual ~FontCharsClass();

private:
	void Free_Character_Arrays() throw();

	void *m_dword08;
	StringClass m_name;
	DynamicVectorClass<FontCharsBuffer *> m_bufferList;
	int m_dword28[7];
	StringClass m_gdiFontName;
	HFONT m_gdiFont;
	void *m_dword4c[257];
	FontCharsTree00940010 m_tree450;
};

FontCharsClass::~FontCharsClass()
{
	while (m_bufferList.Count()) {
		FontCharsBufferEntry00940010 *buffer = (FontCharsBufferEntry00940010 *)m_bufferList[0];
		if (buffer != 0) {
			delete[] buffer->m_ownedArray;
			delete buffer;
		}
		m_bufferList.Delete(0);
	}

	if (m_gdiFont != 0) {
		::DeleteObject(m_gdiFont);
		m_gdiFont = 0;
	}

	Free_Character_Arrays();

	g_fontCharsGdiState0134AEAC->m_refs--;
	if (g_fontCharsGdiState0134AEAC->m_refs == 0) {
		delete g_fontCharsGdiState0134AEAC;
		g_fontCharsGdiState0134AEAC = 0;
	}
}
