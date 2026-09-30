// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "always.h"
#include "refcount.h"
#include "wwstring.h"
#include "vector.h"
#include <string.h>

struct FontCharsClassCharDataStruct;
class FontCharsBuffer;

class FontCharsClassGdiState
{
public:
	FontCharsClassGdiState() throw();

	int m_refs;
	void *m_oldBitmap;
	void *m_bitmap;
	void *m_bits;
	void *m_dc;
};

// Retail global 0x0134AEAC (targets/game/reverse/dir32_addresses.csv).
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

struct Gen_t_0093fa90_p4pod
{
	char m_body[4];
};

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};

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

typedef _STL::pair<const int, Gen_t_0093fa90_p4pod> Rva0093FA90TreePair;
typedef _STL::_Rb_tree<int, Rva0093FA90TreePair, _STL::_Select1st<Rva0093FA90TreePair>,
	_STL::less<int>, _STL::allocator<Rva0093FA90TreePair> > Rva0093FA90Tree;

struct FontCharsMapNode
{
	unsigned char m_color;
	unsigned char m_padding[3];
	FontCharsMapNode *m_parent;
	FontCharsMapNode *m_left;
	FontCharsMapNode *m_right;
	unsigned short m_key;
	FontCharsClassCharDataStruct *m_value;
};

class FontCharDataTree
{
public:
	FontCharDataTree()
	{
		m_header = 0;
		m_header = (FontCharsMapNode *)_STL::__new_alloc::allocate(0x18);
		m_count = 0;
		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
	}

	~FontCharDataTree() throw()
	{
		((Rva0093FA90Tree *)this)->~Rva0093FA90Tree();
	}

	FontCharsMapNode *m_header;
	unsigned int m_count;
	unsigned int m_padding;
};

class FontCharsClass : public W3DMPO, public RefCountClass
{
public:
	FontCharsClass();
	virtual ~FontCharsClass();

	FontCharsClass *m_alternateUnicodeFont;
	StringClass m_name;
	DynamicVectorClass<FontCharsBuffer *> m_bufferList;
	int m_currPixelOffset;
	int m_charHeight;
	int m_charAscent;
	int m_charOverhang;
	int m_pixelOverlap;
	int m_pointSize;
	int m_extraSetting;
	StringClass m_gdiFontName;
	void *m_gdiBitmapBits;
	FontCharsClassCharDataStruct *m_asciiCharArray[256];
	FontCharsClassCharDataStruct **m_unicodeCharArray;
	FontCharDataTree m_charMap;
	unsigned short m_firstUnicodeChar;
	unsigned short m_lastUnicodeChar;
	bool m_isBold;
};

FontCharsClass::FontCharsClass()
	: m_currPixelOffset(0),
	  m_charHeight(0),
	  m_charAscent(0),
	  m_charOverhang(0),
	  m_pixelOverlap(0),
	  m_pointSize(0),
	  m_extraSetting(1),
	  m_gdiBitmapBits(0),
	  m_unicodeCharArray(0),
	  m_firstUnicodeChar(0xffff),
	  m_lastUnicodeChar(0),
	  m_isBold(false)
{
	FontCharsClassGdiState *gdiState = g_fontCharsGdiState0134AEAC;
	if (gdiState == 0)
	{
		gdiState = new FontCharsClassGdiState;
		g_fontCharsGdiState0134AEAC = gdiState;
	}

	++gdiState->m_refs;
	m_alternateUnicodeFont = 0;
	::memset(m_asciiCharArray, 0, sizeof(m_asciiCharArray));
}

