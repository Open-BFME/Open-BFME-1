// ?bfmeRefreshEY@BfmeHostEY@@QAEXXZ
// partial score=0.14 date=2026-09-18
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"

#define _STLP_NO_EXCEPTIONS 1
#include <map>

class TextureClass
{
public:
	void Release_Ref();
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(
			reinterpret_cast<char *>(this) + 4);
	}
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(const RefCountPtr &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	T *Peek() const { return Referent; }
	bool operator<(const RefCountPtr &other) const
	{
		return Referent < other.Referent;
	}

	T *Referent;
};

struct Rva0094D370Value
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;
};

typedef _STL::map<RefCountPtr<TextureClass>, Rva0094D370Value,
	_STL::less<RefCountPtr<TextureClass> >,
	_STL::allocator<_STL::pair<const RefCountPtr<TextureClass>,
		Rva0094D370Value> > > Rva0094D370Map;

class BfmeThingCX
{
public:
	int m_bfmeHead;
	unsigned short m_bfmeRefs;
};

class BfmeHandleCX
{
public:
	BfmeHandleCX() : m_bfmeThing(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : m_bfmeThing(other.m_bfmeThing)
	{
		if (m_bfmeThing != 0)
			++m_bfmeThing->m_bfmeRefs;
	}
	~BfmeHandleCX()
	{
		if (m_bfmeThing != 0)
			--m_bfmeThing->m_bfmeRefs;
	}

	BfmeThingCX *m_bfmeThing;
};

class BfmePairDW
{
public:
	BfmePairDW(int tag, const BfmeHandleCX &handle)
		: m_bfmeTag(tag), m_bfmeHandle(handle) {}

	int m_bfmeTag;
	BfmeHandleCX m_bfmeHandle;
};

extern BfmePairDW __cdecl bfmeMakePair(const int *, const BfmeHandleCX *);

class BfmeThing930A
{
public:
	void bfmeGo930A();
};

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

struct Rva0094CA90Value
{
	unsigned int m_texture;
};

typedef _STL::map<unsigned int, Rva0094CA90Value> Rva0094CA90Map;

struct IDirect3DBaseTexture8;

class Rva006D6050
{
public:
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

	void *m_texture;
};

class Rva006D6050Texture
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
	virtual Bool slot28();
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class SurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	W3DRadarResetSurface(const W3DRadarResetSurface &other)
		: m_surface(other.m_surface)
	{
		if (m_surface != 0)
			m_surface->addRef();
	}
	~W3DRadarResetSurface();
	void *peek() const { return m_surface; }

private:
	SurfaceResource *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

	void *m_texture;
};

class Rva008FC830Surface
{
public:
	void clear(unsigned char);
};

#pragma comment(linker, "/alternatename:?clear@Rva008FC830Surface@@QAEXE@Z=?d_008fc830@@YAXXZ")

extern "C" long __stdcall D3DXLoadSurfaceFromSurface(
	void *, const void *, const void *, void *, const void *, const void *,
	unsigned long, unsigned long);
extern "C" long __stdcall D3DXFilterTexture(
	void *, const void *, unsigned long, unsigned long);

extern float g_bfmeDefaultBU;

struct Rva0094D450Rect
{
	int left;
	int top;
	int right;
	int bottom;
};

class BfmeHostEY
{
public:
	void bfmeRefreshEY();

	unsigned char m_bfmeHeadEY[8];
	unsigned char m_bfmeMapEY[4];
	unsigned char m_bfmeGapEY[0x10];
	unsigned char m_bfmeDirtyEY;
	unsigned char m_bfmePadEY[3];
	float m_bfmeSxEY;
	float m_bfmeSyEY;
};

void BfmeHostEY::bfmeRefreshEY()
{
	BfmeHostEY *owner = this;
	Rva006D6050 *render = reinterpret_cast<Rva006D6050 *>(
		reinterpret_cast<char *>(owner) + 0x18);
	BfmeThing930A *thing = reinterpret_cast<BfmeThing930A *>(
		reinterpret_cast<char *>(owner) + 0x18);
	owner->m_bfmeDirtyEY = 0;
	thing->bfmeGo930A();
	m_bfmeSxEY = 1.0f;
	m_bfmeSyEY = 1.0f;

	Rva0094CA90Map packed;
	unsigned int rowWidth[64];
	unsigned int rowCount = 1;
	rowWidth[0] = 0;

	Rva0094D370Map *images = reinterpret_cast<Rva0094D370Map *>(
		owner->m_bfmeMapEY);
	Rva0094D370Map::iterator image = images->begin();

	for (; image != images->end(); ++image)
	{
		BfmeHandleCX *handle = const_cast<BfmeHandleCX *>(
			reinterpret_cast<const BfmeHandleCX *>(&image->first));
		int width = reinterpret_cast<BfmeThingEF *>(handle)->bfmeAskEF();
		int height = reinterpret_cast<BfmeThingGN *>(handle)->bfmeAskGN();
		int cells = width * height;
		BfmePairDW pair = bfmeMakePair(&cells, handle);
		Rva0094CA90Value value;
		value.m_texture = reinterpret_cast<unsigned int>(
			pair.m_bfmeHandle.m_bfmeThing);

		TextureClass *texture = reinterpret_cast<TextureClass *>(
			pair.m_bfmeHandle.m_bfmeThing);
		if (texture != 0)
			texture->Add_Ref();

		packed.insert(Rva0094CA90Map::value_type(
			static_cast<unsigned int>(cells), value));

		if (texture != 0)
			texture->Release_Ref();
	}

	Rva0094CA90Map::iterator packedIt = packed.end();
	if (packedIt == packed.begin())
		return;
	--packedIt;

	for (;;)
	{
		BfmeHandleCX current;
		current.m_bfmeThing = reinterpret_cast<BfmeThingCX *>(
			packedIt->second.m_texture);
		if (current.m_bfmeThing != 0)
			++current.m_bfmeThing->m_bfmeRefs;

		int tileWidth = (reinterpret_cast<BfmeThingEF *>(
			&current)->bfmeAskEF() + 0x1f) >> 5;
		int tileHeight = (reinterpret_cast<BfmeThingGN *>(
			&current)->bfmeAskGN() + 0x1f) >> 5;
		unsigned int row = 0;
		unsigned int column = 0;
		unsigned int candidate = 0;

		if (tileHeight <= static_cast<int>(rowCount))
		{
			unsigned int lastRow = rowCount - tileHeight;
			for (;;)
			{
				unsigned int scan = 0;
				while (scan < static_cast<unsigned int>(tileHeight)
					&& rowWidth[candidate + scan] + tileWidth <= rowCount)
					++scan;
				if (scan == static_cast<unsigned int>(tileHeight))
				{
					row = candidate;
					column = rowWidth[candidate];
					break;
				}
				++candidate;
				if (candidate > lastRow)
					break;
			}
			if (candidate <= lastRow)
			{
				row = candidate;
				column = rowWidth[candidate];
			}
		}

		if (tileHeight > static_cast<int>(rowCount)
			|| candidate > rowCount - tileHeight)
		{
			if ((rowCount << 6) > *reinterpret_cast<unsigned int *>(this))
				return;

			unsigned int maximum = 0;
			unsigned int start = tileHeight <= static_cast<int>(rowCount)
				? candidate : 0;
			for (unsigned int index = 0;
				index < static_cast<unsigned int>(tileHeight); ++index)
			{
				if (rowWidth[start + index] > maximum)
					maximum = rowWidth[start + index];
			}

			column = maximum;
			for (unsigned int index = 0;
				index < static_cast<unsigned int>(tileHeight); ++index)
				rowWidth[start + index] = maximum + tileWidth;

			rowCount <<= 1;
			if (rowCount > 64)
				return;

			continue;
		}

		Rva0094D370Value &record = (*images)[
			*reinterpret_cast<RefCountPtr<TextureClass> *>(&current)];
		record.x = column << 5;
		record.y = row << 5;
		record.z = record.x + reinterpret_cast<BfmeThingEF *>(
			&current)->bfmeAskEF();
		record.w = record.y + reinterpret_cast<BfmeThingGN *>(
			&current)->bfmeAskGN();

		if (current.m_bfmeThing != 0)
		{
			reinterpret_cast<TextureClass *>(current.m_bfmeThing)->Release_Ref();
			current.m_bfmeThing = 0;
		}

		if (packedIt == packed.begin())
			break;
		--packedIt;
	}

	int atlas = static_cast<int>(rowCount) << 5;
	render->init(atlas, atlas,
		*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 4),
		0, 1, 0);

	TextureBaseClass *renderTexture = reinterpret_cast<TextureBaseClass *>(render);
	if (render->m_texture == 0)
		return;
	if (!reinterpret_cast<Rva006D6050Texture *>(render->m_texture)->slot28())
			return;

	m_bfmeSxEY = static_cast<float>(atlas) / g_bfmeDefaultBU;
	m_bfmeSyEY = m_bfmeSxEY;
	W3DRadarResetSurface destination =
		reinterpret_cast<W3DRadarResetTexture *>(render)->getSurfaceLevel();
	reinterpret_cast<Rva008FC830Surface *>(&destination)->clear(
		*(reinterpret_cast<unsigned char *>(this) + 0x1d));

	for (image = images->begin(); image != images->end(); ++image)
	{
		BfmeHandleCX *handle = const_cast<BfmeHandleCX *>(
			reinterpret_cast<const BfmeHandleCX *>(&image->first));
		TextureClass *texture = reinterpret_cast<TextureClass *>(
			handle->m_bfmeThing);
		if (texture != 0)
			texture->Add_Ref();

		Rva0094D450Rect rect;
		rect.left = image->second.x;
		rect.top = image->second.y;
		rect.right = image->second.z;
		rect.bottom = image->second.w;
		W3DRadarResetSurface source =
			reinterpret_cast<W3DRadarResetTexture *>(handle)->getSurfaceLevel();
		D3DXLoadSurfaceFromSurface(
			destination.peek(), 0, &rect, source.peek(), 0, 0, 1, 0);

		if (texture != 0)
			texture->Release_Ref();
	}

	D3DXFilterTexture(renderTexture->Peek_D3D_Base_Texture(), 0, 0xffffffff, 0xffffffff);
}
