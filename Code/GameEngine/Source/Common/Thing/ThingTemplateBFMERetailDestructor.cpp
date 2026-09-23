// ??1ThingTemplate@@MAE@XZ
// BFME ThingTemplate destructor, retail 0x00146BA0 (849 bytes).
// Identity: ThingFactory::newOverride allocates this 0x4D4-byte type and the
// constructor installs vtable 0x01094988. Unknown members keep RVA names.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <set>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

typedef char AsciiStringMustBeFourBytes[sizeof(AsciiString) == 4 ? 1 : -1];
typedef char UnicodeStringMustBeFourBytes[sizeof(UnicodeString) == 4 ? 1 : -1];

// The vptr plus these fields gives the witnessed 0x0C Rva00146BA0OverridableView base.
class Rva00146BA0OverridableView
{
public:
	virtual ~Rva00146BA0OverridableView()
	{
		if (m_nextOverride)
			m_nextOverride->deleteInstance();
		m_nextOverride = 0;
	}

	void deleteInstance()
	{
		delete this;
	}

private:
	Rva00146BA0OverridableView *m_nextOverride;
	bool m_isOverride;
};

struct Rva00142250Nugget
{
	AsciiString m_first;
	AsciiString m_second;
	unsigned char m_opaque_008[12];
};

struct Rva001439F0Element
{
	unsigned char m_body[0x24];
	~Rva001439F0Element();
};

struct Rva00141A00Element
{
	virtual ~Rva00141A00Element();
	unsigned char m_opaque_004[0x58];
};

struct Rva00146BA0Pod12 { unsigned char m_body[12]; };
struct Rva00146BA0Pod236 { unsigned char m_body[0xEC]; };
typedef unsigned int Rva00146BA0UnknownSetKey;
struct Rva00146BA0ArrayItem
{
	std::set<Rva00146BA0UnknownSetKey> m_tree;
	unsigned char m_opaque_00C[8];
};

class Rva00146BA0AudioItem
{
public:
	virtual ~Rva00146BA0AudioItem();
};

class Rva00146BA0AudioSlots
{
public:
	~Rva00146BA0AudioSlots()
	{
		for (int i = 0; i < 0x6D; ++i)
		{
			if (m_items[i])
			{
				delete m_items[i];
				m_items[i] = 0;
			}
		}
	}

private:
	Rva00146BA0AudioItem *m_items[0x6D];
};

class Rva000FFCA0GeometryInfo
{
public:
	virtual ~Rva000FFCA0GeometryInfo();

private:
	unsigned char m_opaque_004[0x58];
};

typedef char NuggetMustBe20Bytes[sizeof(Rva00142250Nugget) == 0x14 ? 1 : -1];
typedef char ArrayItemMustBe20Bytes[sizeof(Rva00146BA0ArrayItem) == 0x14 ? 1 : -1];
typedef char GeometryInfoMustBe92Bytes[sizeof(Rva000FFCA0GeometryInfo) == 0x5C ? 1 : -1];


// Each retail call is a distinct tree destructor; its payload layout is opaque here.
#define OPAQUE_TREE(NAME) struct NAME { unsigned char m_bytes[12]; ~NAME(); };
OPAQUE_TREE(Rva00140250Tree)
OPAQUE_TREE(Rva00140310Tree)
OPAQUE_TREE(Rva00129B20Tree)
OPAQUE_TREE(Rva00143C00Tree)
OPAQUE_TREE(Rva001403D0Tree)
OPAQUE_TREE(Rva001468A0Tree)
#undef OPAQUE_TREE

class ThingTemplate : public Rva00146BA0OverridableView
{
protected:
	virtual ~ThingTemplate();

private:
	UnicodeString m_wide_00C;
	UnicodeString m_wide_010;
	UnicodeString m_wide_014;
	UnicodeString m_wide_018;

	AsciiString m_ascii_01C;
	AsciiString m_ascii_020;
	AsciiString m_ascii_024;
	AsciiString m_ascii_028;
	AsciiString m_ascii_02C;
	AsciiString m_ascii_030;
	AsciiString m_ascii_034;
	AsciiString m_ascii_array_038[5];
	AsciiString m_ascii_04C;
	AsciiString m_ascii_050;
	AsciiString m_ascii_054;
	AsciiString m_ascii_058;
	AsciiString m_ascii_05C;

	Rva000FFCA0GeometryInfo m_geometry_060;
	std::vector<Rva00141A00Element> m_vector_0BC;
	unsigned char m_opaque_0C8[0x18];
	Rva00146BA0AudioSlots m_audio_slots_0E0;

	std::vector<Rva00142250Nugget> m_vector_294;
	std::vector<Rva00142250Nugget> m_vector_2A0;
	std::vector<Rva00142250Nugget> m_vector_2AC;
	std::vector<Rva00142250Nugget> m_vector_2B8;
	std::vector<Rva001439F0Element> m_vector_2C4;
	std::vector<AsciiString> m_vector_2D0;
	std::vector<AsciiString> m_vector_2DC;
	std::vector<AsciiString> m_vector_2E8;
	unsigned char m_opaque_2F4[4];
	std::vector<Rva00146BA0Pod236> m_vector_2F8;
	Rva00140250Tree m_map_304;
	std::vector<Rva00146BA0Pod12> m_vector_310;
	Rva00140310Tree m_map_31C;
	Rva00129B20Tree m_map_328;
	Rva00143C00Tree m_map_334;
	Rva001403D0Tree m_map_340;
	Rva001468A0Tree m_map_34C;
	std::vector<void *> m_vector_358;
	Rva00146BA0ArrayItem m_array_364[2];
	unsigned char m_opaque_38C[0x4D4 - 0x38C];
};

typedef char ThingTemplateMustBe0x4D4[sizeof(ThingTemplate) == 0x4D4 ? 1 : -1];

ThingTemplate::~ThingTemplate()
{
}
