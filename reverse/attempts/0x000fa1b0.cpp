// ??0Rva000F9FF0@@QAE@PAVObject@@@Z
// partial score=0.63 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x000FA1B0/350: constructor for the address-derived 96-byte
// Rva000F9FF0 record.  The matching copy constructor at 0x000F9FF0 proves
// the member order, canonical AsciiString lifetime, the six-word block at
// +0x14, and the Gen_000F9C60 subobject at +0x44.  The parent at 0x000FB2E0
// passes its first argument unchanged; this body reads that argument as an
// Object* at +0x210, +0x224, and +0x374.

#include "ascii_string.h"

class UnicodeStringWK
{
public:
	UnicodeStringWK(const UnicodeStringWK &other);
	~UnicodeStringWK(void);

private:
	unsigned short *m_bfmeData;
};

class AsciiStringWK
{
public:
	AsciiStringWK(const AsciiStringWK &other);
	~AsciiStringWK(void);

private:
	char *m_bfmeData;
};

class BfmeWideWK : private UnicodeStringWK
{
public:
	BfmeWideWK(const UnicodeStringWK &other) : UnicodeStringWK(other) {}
	~BfmeWideWK(void) {}
};

class BfmeStrWK : private AsciiStringWK
{
public:
	BfmeStrWK(const AsciiStringWK &other) : AsciiStringWK(other) {}
	~BfmeStrWK(void) {}
};

class Gen_000F9C60
{
public:
	Gen_000F9C60(const Gen_000F9C60 &other);

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	bool m_bfmeFlag;
	BfmeWideWK m_bfmeText;
	BfmeStrWK m_bfmeName;
};

struct Rva000F9FF0Block14
{
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
	int m_f28;
};

class Rva000F9FF0;
class Object;
class ThingTemplate;

enum NameKeyType
{
	Rva000FA1B0InvalidNameKey = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class Module
{
public:
	virtual void rva00000000() = 0;
	virtual void rva00000004() = 0;
	virtual void rva00000008() = 0;
	virtual void rva0000000C() = 0;
	virtual void rva00000010() = 0;
	virtual void rva00000014() = 0;
	virtual void rva00000018() = 0;
	virtual void rva0000001C() = 0;
	virtual void rva00000020() = 0;
	virtual void rva00000024() = 0;
	virtual void rva00000028() = 0;
	virtual void rva0000002C() = 0;
	virtual int rva00000030() = 0;

	int rva002A22E0();
	int rva002A23B0();
	ThingTemplate *rva002A1B20();
};

#pragma comment(linker, "/alternatename:?rva002A22E0@Module@@QAEHXZ=?j_00004345@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002A23B0@Module@@QAEHXZ=?j_0001c65c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002A1B20@Module@@QAEPAVThingTemplate@@XZ=?j_00021aee@@YAXXZ")

class Rva000F9FF0ExperienceTracker
{
public:
	int rva001B2070() const;

	unsigned char m_pad000[0x0c];
	int m_f0c;
	unsigned char m_pad010[0x18];
	int m_f28;
};

#pragma comment(linker, "/alternatename:?rva001B2070@Rva000F9FF0ExperienceTracker@@QBEHXZ=?j_000347e3@@YAXXZ")

class ThingTemplate
{
public:
	unsigned char m_pad000[4];
	Overridable *m_override;
	unsigned char m_pad008[0x20 - 8];
	AsciiString m_name;
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;

	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_override)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(
				thingTemplate->m_override->getFinalOverride());
		return thingTemplate;
	}

	unsigned char m_vtable[4];
	ThingTemplate *m_template;
	unsigned char m_pad008[0x210 - 8];
	Rva000F9FF0ExperienceTracker *m_experienceTracker;
	unsigned char m_pad214[0x224 - 0x214];
	Rva000F9FF0Block14 m_completedUpgrades;
	unsigned char m_pad23c[0x370 - 0x23c];
	int m_f370;
	Gen_000F9C60 m_gen374;
};

#pragma comment(linker, "/alternatename:?findModule@Object@@QBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")

class Rva000F9FF0
{
public:
	Rva000F9FF0(Object *object);

	AsciiString m_name;
	int m_f04;
	int m_f08;
	int m_f0c;
	int m_f10;
	Rva000F9FF0Block14 m_block14;
	int m_f2c;
	int m_f30;
	int m_f34;
	unsigned char m_f38;
	int m_f3c;
	int m_f40;
	Gen_000F9C60 m_gen44;
};

// ??0Rva000F9FF0@@QAE@PAVObject@@@Z
Rva000F9FF0::Rva000F9FF0(Object *object)
	: m_name(),
	  m_f04(0),
	  m_f08(object->m_experienceTracker->m_f0c),
	  m_f0c(object->m_experienceTracker->m_f28),
	  m_f10(object->m_experienceTracker->rva001B2070()),
	  m_block14(object->m_completedUpgrades),
	  m_f2c(0),
	  m_f30(-1),
	  m_f34(0),
	  m_f38(1),
	  m_f3c(0),
	  m_f40(object->m_f370),
	  m_gen44(object->m_gen374)
{
	const ThingTemplate *thingTemplate = object->getFinalTemplate();
	static NameKeyType respawnUpdateKey =
		TheNameKeyGenerator->nameToKey("RespawnUpdate");
	Module *module = object->findModule(respawnUpdateKey);
	if (module != 0)
	{
		m_f04 = module->rva00000030();
		m_f2c = module->rva002A22E0();
		m_f34 = module->rva002A23B0();
		thingTemplate = module->rva002A1B20();
	}
	if (thingTemplate != 0)
		m_name.set(thingTemplate->m_name);
	else
		m_name.set(*reinterpret_cast<const AsciiString *>(0x01336E50));
}
