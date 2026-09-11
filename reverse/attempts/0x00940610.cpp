// ??0FontCharsClass@@QAE@XZ
// partial score=0.70 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

#include <new.h>

typedef unsigned short uint16;

class W3DMPO
{
};

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();

	int NumRefs;

protected:
	virtual ~RefCountClass();
};

class StringClass
{
public:
	StringClass(int initialLength = 0, bool temporary = false)
		: m_buffer(*(char **)0x012d9124)
	{
		Get_String(initialLength, temporary);
		m_buffer[0] = *(char *)0x0134ecc8;
	}
	~StringClass();

private:
	void Get_String(int length, bool temporary);
	char *m_buffer;
};

template <class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0)
		: m_vector(0), m_vectorMax(size), m_isValid(true),
		  m_isAllocated(false)
	{
	}
	virtual ~VectorClass();

	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_padding[2];
};

template <class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0)
		: VectorClass<T>(size, array), m_activeCount(0), m_growthStep(10)
	{
	}
	virtual ~DynamicVectorClass();

	int m_activeCount;
	int m_growthStep;
};

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};
}

struct FontCharMapNode
{
	unsigned char m_body[0x18];
};

class FontCharDataTree
{
public:
	FontCharDataTree()
	{
		m_header = 0;
		m_header = (FontCharMapNode *)_STL::__new_alloc::allocate(0x18);
		m_size = 0;
		m_header->m_body[0] = 0;
		*(int *)(m_header->m_body + 4) = 0;
		*(FontCharMapNode **)(m_header->m_body + 8) = m_header;
		*(FontCharMapNode **)(m_header->m_body + 0xc) = m_header;
	}

	FontCharMapNode *m_header;
	int m_size;
};

class FontCharsClassGdiState
{
public:
	FontCharsClassGdiState();

	int m_refs;
	void *m_oldBitmap;
	void *m_bitmap;
	int m_unused;
	void *m_dc;
};

#define g_fontCharsGdiState (*(FontCharsClassGdiState **)0x0134aeac)

class FontCharsClass : public W3DMPO, public RefCountClass
{
public:
	FontCharsClass();
	virtual ~FontCharsClass();

	FontCharsClass *m_alternateUnicodeFont;

private:
	StringClass m_name;
	DynamicVectorClass<void *> m_bufferList;
	int m_currPixelOffset;
	int m_charHeight;
	int m_charAscent;
	int m_charOverhang;
	int m_pixelOverlap;
	int m_pointSize;
	int m_extraSetting;
	StringClass m_gdiFontName;
	void *m_gdiBitmapBits;
	void *m_asciiCharArray[256];
	void *m_unicodeCharArray;
	FontCharDataTree m_charMap;
	uint16 m_firstUnicodeChar;
	uint16 m_lastUnicodeChar;
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
	if (g_fontCharsGdiState == 0)
	{
		g_fontCharsGdiState = new FontCharsClassGdiState;
	}
	++g_fontCharsGdiState->m_refs;

	m_alternateUnicodeFont = 0;
	for (int index = 0; index < 256; ++index)
		m_asciiCharArray[index] = 0;
}
