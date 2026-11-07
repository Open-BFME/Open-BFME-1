// cl: /MD /DNDEBUG /DWIN32 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Open-BFME5: clean reconstruction of the cached two-axis scale update at
// retail RVA 0x00784480.  The owning type's original identity is not recovered;
// the address-derived wrapper records the observed layout without inventing it.

// Retail reads the constant 1.0f out of the compiler's own float literal pool
// at image VA 0x01075334, whose neighbours 0x01075338 (3.0f) and 0x0107533C
// (0.5f, dir32 name __real@3f000000) hold the rest of the run.  It is a code
// literal, not a game datum, so it is defined here rather than left
// unresolved: the previous `extern float g_bfmeDefaultBU` was one of thirteen
// invented placeholder spellings that address carried, none of them defined.
static const float bfmeOneFloat = 1.0f;

extern float g_bfmeUint32Scale; // retail 0x01075358 (2^32 conversion fixup)

class BfmeThingIH
{
public:
	int bfmeGetIH(void);
	void *m_bfmeItem;
};

class BfmeThingIJ
{
public:
	int bfmeGetIJ(void);
};

class Gen_00784480
{
public:
	void update(BfmeThingIH &thing);

private:
	unsigned char m_pad[0x15];
	unsigned char m_initialized;
	unsigned char m_gap[2];
	void *m_sub;
	float m_first0;
	float m_second0;
	float m_first1;
	float m_second1;
	float m_first2;
	float m_second2;
};

void Gen_00784480::update(BfmeThingIH &thing)
{
	if (m_initialized)
		return;
	if (thing.m_bfmeItem == 0)
		return;

	unsigned int first = (unsigned int)thing.bfmeGetIH();
	float first_scale = bfmeOneFloat / (float)first;
	unsigned int second = (unsigned int)((BfmeThingIJ *)&thing)->bfmeGetIJ();
	float second_scale = bfmeOneFloat / (float)second;

	m_initialized = 1;
	m_first0 *= first_scale;
	m_first1 *= first_scale;
	m_first2 *= first_scale;
	m_second0 *= second_scale;
	m_second1 *= second_scale;
	m_second2 *= second_scale;
}

#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../../../Libraries/Source/WWVegas/WW3D2/texturefilter.h"
#include <hash_map>

#include "string_base.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
#include "ascii_string.h"
typedef AsciiString BFMERetailAsciiString;

class File
{
public:
	virtual ~File();
	virtual void slot04();
	virtual void close();
	virtual int slot0c(void *buffer, int bytes);
	virtual int slot10(const void *buffer, int bytes);
	virtual int slot14(int bytes, int mode);
	virtual void nextLine(char *buffer, int bufferSize);
	virtual bool slot1c();
	virtual bool slot20(int &value);
	virtual bool slot24(float &value);
	virtual bool slot28(AsciiString &value);
	virtual bool slot2c(const char *format, ...);
	virtual int slot30();
	virtual int slot34();
	virtual char *slot38();
	virtual File *slot3c();

	bool eof();
};

class FileSystem
{
public:
	File *openFile(const char *name, int access);
};

extern FileSystem *TheFileSystem;

// This helper is static in Open2Conv007.cpp.  MSVC's private-register ABI is
// encoded by the declaration's internal linkage; the exact decorated name is
// already carried by that matched body, so this TU-local declaration can use
// it without inventing a second semantic owner.
static File *Open2OpenPastSeparators(const AsciiString &name) throw()
{
	const char *text = name.str();
	File *file = TheFileSystem->openFile(text, 1);
	while (file == 0)
	{
		text = ::strchr(text, '\\');
		if (text == 0)
			return 0;
		++text;
		file = TheFileSystem->openFile(text, 1);
	}
	return file;
}

#include "texture.h"
#include "dx8wrapper.h"
#include "ww3d.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva00788460GlobalDataView
{
 char m_pad[0xe55];
 unsigned char m_resolutionFlag;
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

class ShroudFilter
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();

	TextureClass *m_texture;
};

class Rva0090E250
{
public:
	void set(int value);

	void *m_inner;
};

// The body at 0x00787D80 is the matched 4-byte hash_map subscript that the
// 0x00027E30 thunk reaches.  The value is used here only as an ABI surrogate:
// this address-derived owner is not being claimed to be Player or to own a
// relationship map.
enum Relationship
{
	BfmeLookupValue0 = 0,
	BfmeLookupValue1,
	BfmeLookupValue2
};

namespace _STL { template<> Relationship &hash_map<int, Relationship>::operator[](const int &); }

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> >
	BfmeLookupMap;

struct Rva00785140Target { int m_first; unsigned short m_refCount; unsigned short m_pad; };
struct Rva00785140Plain { Rva00785140Target *m_target; };
class Rva00785140Handle
{
public:
 virtual ~Rva00785140Handle();
 Rva00785140Target *m_target;
};
struct BfmeTextureEntry
{
 BfmeTextureEntry(const BFMEWaterTrackTextureHandle &texture)
 {
  m_holder.m_target=(Rva00785140Target *)texture.m_texture;
  if(texture.m_texture) ++*(unsigned short *)((char *)texture.m_texture+4);
 }
 Rva00785140Handle m_holder;
};

extern "C" __declspec(dllimport) int __cdecl sscanf(
	const char *text, const char *format, ...);

extern void *operator new(unsigned int bytes);

class Gen_007892D0
{
public:
	void bfmeRun(void);

private:
	BFMERetailAsciiString m_bfmeName;
	char m_bfmeGap04[4];
	BfmeLookupMap m_bfmeLookup;

	void bfmeStep1(void);					// ILT 0x000270FC
	void bfmeStep2(void);					// ILT 0x0003879E
	void bfmeStep3(void);					// ILT 0x0004264A
};

// ?bfmeStep2@Gen_007892D0@@AAEXXZ -- retail 0x00788460 (755 bytes).
// BFME 2 Rva000A9F48FileOpen.cpp supplies the two-field resolution object.
// A separate refresh/bits local preserves retail's bool/key stack allocation.
//
// The owner remains address-derived: the caller/ILT proves this method's
// identity, while the first member, the +8 lookup object, and the callees below
// are the only layout facts used here.  In particular, the four-byte map value
// is treated as an ABI slot for the matched subscript body, not named as a
// recovered game concept.
void Gen_007892D0::bfmeStep2(void)
{
	BFMERetailAsciiString dataName(m_bfmeName);
	dataName.StringBase<char>::concat(".dat", 4);

	File *file;
	{
		BFMERetailAsciiString openName(dataName.str());
		file = Open2OpenPastSeparators(
			*(const AsciiString *)&openName);
	}

	if (file == 0)
		return;

	char line[0x400];
	line[0x3ff] = 0;
	struct { int width, height; } resolution;
	int refresh;
	bool unusedWindowed;
	WW3D::Get_Device_Resolution(
		resolution.width, resolution.height, refresh, unusedWindowed);
	unsigned char windowed = ((const Rva00788460GlobalDataView *)TheWritableGlobalData)->m_resolutionFlag;
	if (resolution.width == 0x400)
		windowed = !windowed;
	int one = 1;

	while (!file->eof())
	{

		file->nextLine(line, 0x3ff);
		if (line[0] == ';')
			continue;

		BFMERetailAsciiString textureName;
		int first;
		int second;

		if (sscanf(line, "%d->%d", &first, &second) == 2)
			textureName.format(BFMERetailAsciiString("apt_%s_%d.tga"), m_bfmeName.str(), second);
		else if (sscanf(line, "%d", &first) == one)
			textureName.format(BFMERetailAsciiString("apt_%s_%d.tga"), m_bfmeName.str(), first);
		else continue;

		{
			BFMEWaterTrackTextureHandle texture =
				BFMEGetWaterTrackTexture((char *)textureName.str(), 1, 0);
			Rva0090E250 *settings = (Rva0090E250 *)&texture;
			settings->set(2);

			ShroudTexture *surface = (ShroudTexture *)&texture;
			if (windowed)
			{
				surface->getFilter()->m_04 = one;
				surface->getFilter()->m_00 = one;
				reinterpret_cast<TextureFilterClass *>(surface->getFilter())->Set_Mip_Mapping(static_cast<TextureFilterClass::FilterType>(one));
			}
			else
			{
				surface->getFilter()->m_04 = 3;
				surface->getFilter()->m_00 = 3;
				reinterpret_cast<TextureFilterClass *>(surface->getFilter())->Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_DEFAULT);
			}
			surface->getFilter()->m_0c = one;
			surface->getFilter()->m_10 = one;

			BfmeTextureEntry *entry = new BfmeTextureEntry(texture);

			Relationship &slot = m_bfmeLookup[first];
			*(void **)&slot = entry;
		}
	}
	file->close();
}

