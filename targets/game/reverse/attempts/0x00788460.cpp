// ?bfmeStep2@Gen_007892D0@@AAEXXZ
// partial score=0.9933774834437086 date=2026-09-28
// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib
// ?bfmeStep2@Gen_007892D0@@AAEXXZ
// partial score=0.24 date=2026-09-09
// stlport
// Retry of the preferred bank. Corrected against retail:
// map key is first (not the filename's second index); the retained entry owns
// texture.m_texture, not the filtering view; preserve seven getFilter calls.
// Open2 helper independently probes exact over all 81 bytes at 0x00785270.
// Its throw contract removes a state absent from the retail caller.
// Remaining mismatch: five frame displacements (unusedWindowed and first).
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

extern FileSystem *TheOpen2FileSystem;

// This helper is static in Open2Conv007.cpp.  MSVC's private-register ABI is
// encoded by the declaration's internal linkage; the exact decorated name is
// already carried by that matched body, so this TU-local declaration can use
// it without inventing a second semantic owner.
static File *Open2OpenPastSeparators(const AsciiString &name) throw()
{
	const char *text = name.str();
	File *file = TheOpen2FileSystem->openFile(text, 1);
	while (file == 0)
	{
		text = ::strchr(text, '\\');
		if (text == 0)
			return 0;
		++text;
		file = TheOpen2FileSystem->openFile(text, 1);
	}
	return file;
}

class DX8Wrapper
{
public:
	static void Get_Device_Resolution(int &width, int &height, int &refresh,
		bool &windowed);
};

struct GlobalData
{
	char m_pad[0xe55];
	unsigned char m_resolutionFlag;
};

extern GlobalData *TheWritableGlobalData;

class TextureClass
{
public:
	void Release_Ref();
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

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudFilter : public Gen_00920a60
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

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> >
	BfmeLookupMap;

struct BfmeTextureEntry
{
 BfmeTextureEntry(const BFMEWaterTrackTextureHandle &texture) {
  m_vftable=(void*)0x01126ab8;
  m_filter=(ShroudFilter*)texture.m_texture;
  if (texture.m_texture) ++*(unsigned short*)((char*)texture.m_texture+4);
 }
	void *m_vftable;
	ShroudFilter *m_filter;
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

// ?bfmeStep2@Gen_007892D0@@AAEXXZ
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
	struct { int width,height,refresh; } resolution;
	bool unusedWindowed;
	DX8Wrapper::Get_Device_Resolution(resolution.width, resolution.height, resolution.refresh, unusedWindowed);
	unsigned char windowed = TheWritableGlobalData->m_resolutionFlag;
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
				surface->getFilter()->m(one);
			}
			else
			{
				surface->getFilter()->m_04 = 3;
				surface->getFilter()->m_00 = 3;
				surface->getFilter()->m(3);
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

