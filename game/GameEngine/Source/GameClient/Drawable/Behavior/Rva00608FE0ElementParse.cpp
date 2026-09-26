// ?parse@Rva00608FE0Element@@QAEXPAVINI@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
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
	Rva006087E0Mask m_mask000;
	Rva006087E0Mask m_mask018;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vector030;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vector03c;
	unsigned char m_tail048[0x1c8];
};

#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@XZ=?j_0002a48c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@ABU0@@Z=?j_00042339@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00608FE0Element@@QAE@XZ=?j_00034158@@YAXXZ")

void Rva00608FE0Element::parse(INI *ini)
{
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *firstVector = &m_vector030;
	firstVector->erase(firstVector->begin(), firstVector->end());
	m_mask000.clear();
	m_vector03c.erase(m_vector03c.begin(), m_vector03c.end());
	m_mask018.clear();

	for (const char *token = ini->getNextTokenOrNull(0); token != 0;
		token = ini->getNextTokenOrNull(0))
	{
		AsciiString value(token);
		firstVector->push_back(value);
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
