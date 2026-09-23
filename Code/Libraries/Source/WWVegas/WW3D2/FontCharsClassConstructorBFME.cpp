// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

#define g_fontCharsGdiState (*(FontCharsClassGdiState **)0x0134aeac)

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

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
		typedef void (__fastcall *Rva0093FA90TreeDestructor)(FontCharDataTree *, void *);
		// The retail cleanup reads the tree through ECX and ignores EDX.
		((Rva0093FA90TreeDestructor)0x00D3FA90)(this, 0);
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
	FontCharsClassGdiState *gdiState = g_fontCharsGdiState;
	if (gdiState == 0)
	{
		gdiState = new FontCharsClassGdiState;
		g_fontCharsGdiState = gdiState;
	}

	++gdiState->m_refs;
	m_alternateUnicodeFont = 0;
	::memset(m_asciiCharArray, 0, sizeof(m_asciiCharArray));
}

