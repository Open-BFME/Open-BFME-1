// ?bfmeRefreshEY@BfmeHostEY@@QAEXXZ
// partial score=0.3033 date=2026-10-03
// Retail RVA0094D450 owns1111B, including its reachable trailing release block.
// Native STLport/texture declarations preserve the corrected owner layout.
// Sibling0094D8D0 proves an iterator at+14, between the12B map and+18 holder.
// See identity_evidence/0094d450-atlas-iterator-layout.md.
// Still1116B/764 differing bytes; no strict conversion or new callee binding.
// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

#include "texture.h"

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_referent(0) {}
	RefCountPtr(const RefCountPtr &other) : m_referent(other.m_referent)
	{
		if (m_referent != 0)
			m_referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_referent != 0)
			m_referent->Release_Ref();
	}
	bool operator<(const RefCountPtr &other) const
	{
		return m_referent < other.m_referent;
	}

	T *m_referent;
};

typedef RefCountPtr<TextureClass> TexturePtr;

// Ledger views of the texture handle's out-of-line accessors.
class BfmeThingEF
{
public:
	int bfmeAskEF();
};

class BfmeThingGN
{
public:
	int bfmeAskGN();
};

static __forceinline int textureWidth(TexturePtr &texture)
{
	return ((BfmeThingEF *)&texture)->bfmeAskEF();
}

static __forceinline int textureHeight(TexturePtr &texture)
{
	return ((BfmeThingGN *)&texture)->bfmeAskGN();
}

// The per-texture atlas rectangle (operator[] at 0x0094D370).
struct Rva0094D370Value
{
	int left;
	int top;
	int right;
	int bottom;
};

typedef _STL::map<TexturePtr, Rva0094D370Value> Rva0094D370Map;

// Area-sorted value (the multimap _M_insert at 0x0094CA90).
struct Rva0094CA90Value
{
	Rva0094CA90Value(const TexturePtr &t) : texture(t) {}

	TexturePtr texture;
};

typedef _STL::multimap<unsigned int, Rva0094CA90Value> Rva0094CA90Map;

typedef _STL::pair<const unsigned int, Rva0094CA90Value> Rva0094D450SortedPair;
typedef _STL::_Rb_tree<unsigned int, Rva0094D450SortedPair,
 _STL::_Select1st<Rva0094D450SortedPair>, _STL::less<unsigned int>,
 _STL::allocator<Rva0094D450SortedPair> > Rva0094D450SortedTree;
namespace _STL {
template<> Rva0094D450SortedTree::iterator Rva0094D450SortedTree::_M_insert(
 _Rb_tree_node_base *, _Rb_tree_node_base *, const Rva0094D450SortedPair &, _Rb_tree_node_base *);
template<> Rva0094D450SortedTree::~_Rb_tree();
template<> Rva0094D370Value &Rva0094D370Map::operator[](const TexturePtr &);
}
class BfmeHandleCX;

class BfmePairDW : public _STL::pair<int, TexturePtr>
{
};

BfmePairDW __cdecl bfmeMakePair(const int *first, const BfmeHandleCX *second);

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();
};

class Rva008FC830Surface
{
public:
	void fill(unsigned int value);
};

#pragma comment(linker, "/alternatename:?fill@Rva008FC830Surface@@QAEXI@Z=?d_008fc830@@YAXXZ")

class BfmeThing930A
{
public:
	void bfmeGo930A();
};

class Rva006D6050
{
public:
	void init(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
};

class Rva0094D450Texture
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual bool slot28();
};

extern "C" long __stdcall D3DXLoadSurfaceFromSurface(void *dst, const void *dstPalette,
	const void *dstRect, void *src, const void *srcPalette, const void *srcRect,
	unsigned long filter, unsigned long colorKey);
extern "C" long __stdcall D3DXFilterTexture(IDirect3DBaseTexture8 *texture,
	const void *palette, unsigned long srcLevel, unsigned long filter);

class BfmeHostEY
{
public:
	void bfmeRefreshEY();

	unsigned int m_maxSize;			// +0x00
	unsigned int m_format;			// +0x04
	Rva0094D370Map m_rects;
 Rva0094D370Map::iterator m_rva0094D450_14;			// +0x08
	Rva0094D450Texture *m_texture;		// +0x18
	bool m_dirty;				// +0x1C
	unsigned char m_fill;			// +0x1D
	float m_scaleY;				// +0x20
	float m_scaleX;				// +0x24
};

void BfmeHostEY::bfmeRefreshEY()
{
	m_dirty = false;
	((BfmeThing930A *)&m_texture)->bfmeGo930A();
	m_scaleY = m_scaleX = 1.0f;

	Rva0094CA90Map sorted;
	for (Rva0094D370Map::iterator it = m_rects.begin(); it != m_rects.end(); ++it)
	{
		TexturePtr &texture = (TexturePtr &)it->first;
		int area = textureWidth(texture) * textureHeight(texture);
		sorted.insert(bfmeMakePair(&area, (const BfmeHandleCX *)&texture));
	}

	int size = 1;
	int rows[64];
	rows[0] = 0;
	for (Rva0094CA90Map::reverse_iterator rit = sorted.rbegin(); rit != sorted.rend(); ++rit)
	{
		TexturePtr texture = rit->second.texture;
		int width = (unsigned int)(textureWidth(texture) + 31) >> 5;
		int height = (unsigned int)(textureHeight(texture) + 31) >> 5;
		int row;
		for (;;)
		{
			row = 0;
			int last = size - height;
			for (; row <= last; row++)
			{
				int i;
				for (i = 0; i < height; i++)
				{
					if (rows[row + i] + width > size)
						break;
				}
				if (i == height)
					break;
			}
			if (row <= last)
				break;

			if ((unsigned int)(size * 64) > m_maxSize)
				return;
			int grown = size * 2;
			for (int i = size; i < grown; i++)
				rows[i] = 0;
			size = grown;
		}

		int column = 0;
		for (int i = 0; i < height; i++)
		{
			if (rows[row + i] > column)
				column = rows[row + i];
		}
		for (int i = 0; i < height; i++)
			rows[row + i] = width + column;

		Rva0094D370Value &rect = m_rects[texture];
		rect.left = column << 5;
		rect.top = row << 5;
		rect.right = textureWidth(texture) + rect.left;
		rect.bottom = textureHeight(texture) + rect.top;
	}

	int pixels = size << 5;
	((Rva006D6050 *)&m_texture)->init(pixels, pixels, m_format, 0, 1, 0);
	if (m_texture == 0 || !m_texture->slot28())
		return;

	m_scaleY = m_scaleX = 1.0f / (float)pixels;
	W3DRadarResetSurface destination = ((W3DRadarResetTexture *)&m_texture)->getSurfaceLevel();
	((Rva008FC830Surface *)&destination)->fill(m_fill);

	for (Rva0094D370Map::iterator it = m_rects.begin(); it != m_rects.end(); ++it)
	{
		TexturePtr texture = it->first;
		Rva0094D370Value rect = it->second;
		W3DRadarResetSurface source = ((W3DRadarResetTexture *)&texture)->getSurfaceLevel();
		D3DXLoadSurfaceFromSurface(destination.m_surface, 0, &rect, source.m_surface, 0, 0, 1, 0);
	}

	D3DXFilterTexture(((TextureBaseClass *)&m_texture)->Peek_D3D_Base_Texture(), 0,
		0xffffffff, 0xffffffff);
}
