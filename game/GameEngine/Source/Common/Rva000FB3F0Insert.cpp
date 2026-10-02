// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 000FB3F0/206B: the two-argument helper the matched Player post-load
// template walk (0x000D9680) calls on the Player subobject at +0x684 with
// (const ThingTemplate *, Player *).  Caller 002A30D0-independent: the matched
// caller 000D9680 passes ECX = Player+0x684 and pushes the Player, then the
// resolved template, which fixes both argument types and the receiver.
//
// The body is the sibling shape of 000FB2E0 (same 96-byte record, same copy
// body 000F9FF0 through ILT 0004845F, same 000FB080 reallocating insert through
// ILT 000266E3, same +44 subobject destructor through ILT 0002671F): build the
// record from the two arguments, read one int out of the template and store it
// in the record at +0x0C, then push_back.  Owner and method stay address
// derived from the bank; no semantic identity is claimed here.

#include "ascii_string.h"
#include <new>
#include <vector>

class ThingTemplate;
class Rva000D9680Player;

// The +0x44 subobject is copied by the proven 0x000F9FF0 body but destroyed
// through the AudioEventRTS ILT at 0x0002671F.  Keep its copy identity opaque;
// the independently audited pin names the witnessed destructor.

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
	~Gen_000F9C60();

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	bool m_bfmeFlag;
	BfmeWideWK m_bfmeText;
	BfmeStrWK m_bfmeName;
};

// Genuine 96-byte record layout from the independently landed F9FF0 copy body.
// The vector spelling is the already-proven FB210 instantiation, not a guessed
// pair identity; its copy constructor is routed to the retail F9FF0 body
// through the witnessed 0x0004845F ILT.
struct Rva000F9FF0Block14
{
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
	int m_f28;
};

struct Rva000FB210Element
{
public:
	Rva000FB210Element(const Rva000FB210Element &other);

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
	Gen_000F9C60 m_audioEvent;
};

// 0x000FA4A0 is defined as Rva000FA610's source constructor.  Keep the
// FB210Element vector specialization below, while using the defining class
// name for this same 96-byte temporary layout and constructor call.
struct Rva000FA610
{
	Rva000FA610(const unsigned char *source, int unused);

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
	Gen_000F9C60 m_audioEvent;
};

// The record's copy construction is retail body 0x000F9FF0, whose defining
// name is Rva000F9FF0's copy constructor.  Spell the copy through that class so
// the emitted reference is the resolved one; the 96-byte layout is unchanged.
class Rva000F9FF0
{
public:
	Rva000F9FF0(const Rva000F9FF0 &other);
};

namespace _STL
{
template<>
inline void _Construct(Rva000FB210Element *p, const Rva000FB210Element &value)
{
	new (p) Rva000F9FF0(*(const Rva000F9FF0 *)&value);
}
}

// Retail 0x0013FC80 scans the behaviour module vector at +0x294 and returns an
// int; the matched Player walk has established no semantic name for it, so the
// address-derived spelling is the identity here too.
class Rva0013FC80ThingTemplateView
{
public:
	int rva0013FC80GetModuleValue(void);
};

struct Rva000FB3F0
{
	void *m_unknown00;
	std::vector<Rva000FB210Element> m_vec;

	void rva000FB3F0(const ThingTemplate *param1, Rva000D9680Player *param2);
};

void Rva000FB3F0::rva000FB3F0(const ThingTemplate *param1, Rva000D9680Player *param2)
{
	Rva000FA610 temp(reinterpret_cast<const unsigned char *>(param1), (int)param2);
	Rva000FB210Element &element = *(Rva000FB210Element *)&temp;

	element.m_f0c = const_cast<Rva0013FC80ThingTemplateView *>(
		reinterpret_cast<const Rva0013FC80ThingTemplateView *>(param1))->rva0013FC80GetModuleValue();

	// Keep the vector as the native STLport object.  The reference alias makes
	// MSVC rebase esi to this+4 before its capacity test; native push_back then
	// emits the retail start/finish order and the 96-byte store.
	std::vector<Rva000FB210Element> &vec = m_vec;
	vec.push_back(element);
}
