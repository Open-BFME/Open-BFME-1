// ?parse@Rva00608FE0Element@@QAEXPAVINI@@@Z
// partial score=0.9411764705882353 date=2026-09-22
// ?parse@Rva00608FE0Element@@QAEXPAVINI@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// scratch reconstruction of retail 0x006087E0; not a tracked source claim
// Retail callee evidence: erase=0x0065960 via ILT 0x00024C17, token=0x008509C0,
// overflow=0x0063700 via ILT 0x0003827B, releaseBuffer=0x00887940,
// StringBase<char> copy=0x00887B60 and cstr ctor=0x00888BC0,
// getVoiceFieldParse=0x0013CE10 via ILT 0x0002698B, add=0x00850920,
// initFromINIMulti=0x00851910, and buildMasks=0x00608090 via ILT 0x0000F187.
// The 0x210-byte record lifetime is matched by ctor/copy/dtor at
// 0x006086E0/0x006089C0/0x00608480 (ILT 0x0002A48C/0x00042339/0x00034158).

#include <new>
#include <bitset>
struct Rva006087E0Mask { _STL::bitset<192> bits; void clear() { bits.reset(); } };
#include <stl/_config.h>
#include <vector>
#include "ascii_string.h"

struct FieldParse;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		m_count = 0;
		for (int i = 0; i < 16; ++i)
		{
			m_offsets[i] = 0;
			m_fields[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fields[16];
	unsigned int m_offsets[16];
	unsigned int m_count;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators);
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

extern const FieldParse *getVoiceFieldParse();

class Rva006083A0SoundUpgrade
{
public:
	void buildMasks(unsigned int *first, unsigned int *second);
};

#pragma comment(linker, "/alternatename:?buildMasks@Rva006083A0SoundUpgrade@@QAEXPAI0@Z=?j_0000f187@@YAXXZ")

class Rva00608FE0Element
{
public:
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();

	void parse(INI *ini);

private:
	Rva006087E0Mask m_values0;
	Rva006087E0Mask m_values18;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_soundNames;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_otherNames;
	unsigned char m_tail[0x1c8];
};

#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@XZ=?j_0002a48c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@ABU0@@Z=?j_00042339@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00608FE0Element@@QAE@XZ=?j_00034158@@YAXXZ")

void Rva00608FE0Element::parse(INI *ini)
{
	m_soundNames.erase(m_soundNames.begin(), m_soundNames.end());
	m_values0.clear();
	m_otherNames.erase(m_otherNames.begin(), m_otherNames.end());
	m_values18.clear();

	for (const char *token = ini->getNextTokenOrNull(0); token != 0;
		token = ini->getNextTokenOrNull(0))
	{
		AsciiString value(token);
		m_soundNames.push_back(value);
	}

	MultiIniFieldParse fields;
	fields.add(reinterpret_cast<const FieldParse *>(0x011159E8));
	fields.add(getVoiceFieldParse(), 0x48);
	ini->initFromINIMulti(this, fields);

	if (*(void **)0x012EF188 != 0)
	{
		unsigned int localA[6];
		unsigned int localB[6];
		reinterpret_cast<Rva006083A0SoundUpgrade *>(this)->buildMasks(localA, localB);
	}
}
