// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// HordeSiegeEngineContainModuleData constructor, RVA0022CB80,148B.
// Matched factory00116360 allocates0x24C; SlaughterHordeContainModuleData
// ctor0022B160 calls this base; installs vtable010AD180.
// Attribute handle at+224 is one index: ctorILT3747A->003A0410 and
// dtorILT1A401->0039D550 match the landed handle bodies. +228 is a
// separate opaque word, as is+230 after the canonical4B string at+22C.
// Value initialization of the+23C aggregate reproduces the three stores.
// The string and+230 word initialize together to retain ECX-relative stores;
// retail writes+230 again after clear(). No new pins or guessed field names.

#include "ascii_string.h"

class HordeSiegeEngineContainModuleDataBase
{
public:
	HordeSiegeEngineContainModuleDataBase();
	virtual ~HordeSiegeEngineContainModuleDataBase();

private:
	unsigned char m_pad[0x220];
};

class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

public:
	unsigned int m_224;

};

struct Rva0022CB80Triple
{
	float m_23c;
	float m_240;
	float m_244;
};

struct Rva0022CB80NameAt22C
{
	AsciiString m_22c;
	unsigned int m_230;

	Rva0022CB80NameAt22C() : m_22c(), m_230(0) {}
};

class HordeSiegeEngineContainModuleData : public HordeSiegeEngineContainModuleDataBase
{
public:
	HordeSiegeEngineContainModuleData();
	virtual ~HordeSiegeEngineContainModuleData();

private:
	AttributeHandleStandIn m_224;
	unsigned int m_228;
	Rva0022CB80NameAt22C m_22c;
	float m_234;
	unsigned char m_238;
	Rva0022CB80Triple m_23c;
	unsigned char m_248;
};

HordeSiegeEngineContainModuleData::HordeSiegeEngineContainModuleData()
	: m_22c(), m_23c()
{
	m_228 = 0;
	m_234 = 1.0f;
	m_238 = 0;
	m_22c.m_22c.clear();
	m_22c.m_230 = 0;
	m_248 = 0;
}