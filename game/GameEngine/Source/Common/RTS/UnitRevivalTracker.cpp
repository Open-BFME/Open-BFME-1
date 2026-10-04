// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x000FA1B0/350: builds a 96-byte Rva000FB210Element from an Object*
// (caller 0x000FB2E0, copy constructor 0x000F9FF0). The inline accessors are
// load-bearing: they set VC7.1's scratch and EBX/EBP register assignment.

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

	~Gen_000F9C60(void);

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

class Rva000FB210Element;
class Object;
class ThingTemplate;

extern void j_00004345();
extern void j_0001c65c();
extern void j_00021aee();
extern void j_000347e3();
extern void j_0003add7();
extern void j_000022bb();
extern void j_0002ae23();

enum NameKeyType
{
	Rva000FA1B0InvalidNameKey = 0
};

class NameKeyGenerator
{
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const AsciiString Rva01336E50EmptyString;

// Retail ILT 0x0003ADD7 carries thiscall NameKeyGenerator::nameToKey.
static __forceinline NameKeyType rva0003ADD7(NameKeyGenerator *generator, const char *name)
{
	typedef NameKeyType (NameKeyGenerator::*Fn)(const char *);
	union { void (*fn)(); Fn call; } lookup = { j_0003add7 };
	return (generator->*lookup.call)(name);
}

class Overridable
{
};

// Retail ILT 0x00022BB carries the const thiscall Overridable::getFinalOverride.
static __forceinline const Overridable *rva00022BB(Overridable *overridable)
{
	typedef const Overridable *(Overridable::*Fn)();
	union { void (*fn)(); Fn call; } lookup = { j_000022bb };
	return (overridable->*lookup.call)();
}

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

	// Thiscall bodies reached through ILTs 0x00004345, 0x0001C65C and 0x00021AEE.
	int rva002A22E0()
	{
		union { void (*entry)(); int (Module::*member)(); } call;
		call.entry = j_00004345;
		return (this->*call.member)();
	}
	int rva002A23B0()
	{
		union { void (*entry)(); int (Module::*member)(); } call;
		call.entry = j_0001c65c;
		return (this->*call.member)();
	}
	ThingTemplate *rva002A1B20()
	{
		union { void (*entry)(); ThingTemplate *(Module::*member)(); } call;
		call.entry = j_00021aee;
		return (this->*call.member)();
	}
};

class Rva000F9FF0ExperienceTracker
{
public:
	// Thiscall body 0x001B2070 reached through ILT 0x000347E3.
	int rva001B2070() const
	{
		union { void (*entry)(); int (Rva000F9FF0ExperienceTracker::*member)() const; } call;
		call.entry = j_000347e3;
		return (this->*call.member)();
	}
	int getF0c() const { return m_f0c; }

	unsigned char m_pad000[0x0c];
	int m_f0c;
	unsigned char m_pad010[0x18];
	int m_f28;
};


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
	Rva000F9FF0ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	int getF370() const { return m_f370; }

	// The null path writes 0 into the result temporary before the join (xor eax, eax).
	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		const ThingTemplate *result;
		if (!thingTemplate)
			result = 0;
		else if (thingTemplate->m_override)
			result = reinterpret_cast<const ThingTemplate *>(rva00022BB(thingTemplate->m_override));
		else
			result = thingTemplate;
		return result;
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

// Retail ILT 0x0002AE23 carries the const thiscall Object::findModule.
static __forceinline Module *rva0002AE23(const Object *object, NameKeyType key)
{
	typedef Module *(Object::*Fn)(NameKeyType) const;
	union { void (*fn)(); Fn call; } lookup = { j_0002ae23 };
	return (object->*lookup.call)(key);
}

class Rva000FB210Element
{
public:
	Rva000FB210Element(Object *object);

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

Rva000FB210Element::Rva000FB210Element(Object *object)
	: m_name(),
	  m_f04(0),
	  m_f08(object->getExperienceTracker()->getF0c()),
	  m_f0c(object->getExperienceTracker()->m_f28),
	  m_f10(object->getExperienceTracker()->rva001B2070()),
	  m_block14(object->m_completedUpgrades),
	  m_f2c(0),
	  m_f30(-1),
	  m_f34(0),
	  m_f38(1),
	  m_f3c(0),
	  m_f40(object->getF370()),
	  m_gen44(object->m_gen374)
{
	const ThingTemplate *thingTemplate = object->getFinalTemplate();
	static NameKeyType respawnUpdateKey =
		rva0003ADD7(TheNameKeyGenerator, "RespawnUpdate");
	Module *module = rva0002AE23(object, respawnUpdateKey);
	if (module != 0)
	{
		m_f04 = module->rva00000030();
		m_f2c = module->rva002A22E0();
		m_f34 = module->rva002A23B0();
		thingTemplate = module->rva002A1B20();
	}
	m_name.set(thingTemplate != 0 ? thingTemplate->m_name : Rva01336E50EmptyString);
}
