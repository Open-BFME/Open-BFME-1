// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x000FB4E0/241B (ret, then INT3), the third sibling of the matched
// 000FB2E0/000FB3F0 appends over the same 96-byte record (copy body 000F9FF0
// through ILT 0004845F, reallocating insert 000FB080 through ILT 000266E3):
// copy the record vector TheLivingWorldLogic (0x012F1028) exposes through the four-byte
// `lea eax,[ecx+0x68]` getter at 0x003BCD70 (vector copy 000FAA30 through ILT
// 00026ED1), push_back every element onto the vector at this+4, then destroy
// the copy (000DD310 through ILT 0002A081).  Only caller is ILT 0002F87E; owner
// and method stay address derived, no semantic identity is claimed.

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

struct Rva000FAA30Elem
{
	char m_body[0x60];
};

namespace _STL
{
// Retail overflow 000FB080 is owned by RvaVectorInsertOverflowInlineCopy.cpp.
// This append body calls it out of line; do not emit a competing helper.
template <>
void vector<Rva000FB210Element>::_M_insert_overflow(Rva000FB210Element *,
	const Rva000FB210Element &, const __false_type &, size_t, bool);

template<>
inline void _Construct(Rva000FB210Element *p, const Rva000FB210Element &value)
{
	new (p) Rva000F9FF0(*(const Rva000F9FF0 *)&value);
}

// A named empty dispatch tag preserves the retail caller without value-
// initializing storage when the overflow definition lives in another TU.
template <>
__forceinline void vector<Rva000FB210Element>::push_back(
	const Rva000FB210Element &value)
{
	if (_M_finish != _M_end_of_storage._M_data) {
		_Construct(_M_finish, value);
		++_M_finish;
	} else {
		__false_type tag;
		_M_insert_overflow(_M_finish, value, tag, 1, true);
	}
}
// The copy is the 0x000FAA30 instantiation; its copy constructor and the
// 0x000DD310 destructor stay out of line as in retail.
template <>
vector<Rva000FAA30Elem>::vector(const vector<Rva000FAA30Elem> &other);
template <>
vector<Rva000FAA30Elem>::~vector();
}

// The 0x003BCD70 getter's ledger identity is TeamPrototype::getTemplateInfo;
// on TheLivingWorldLogic (0x012F1028, referenced under its recorded DIR32
// spelling) it yields the record vector at +0x68.
class TeamTemplateInfo;
class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo() const;
};
class Glo012F1028Type;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

struct Rva000FB4E0
{
	void *m_unknown00;
	std::vector<Rva000FB210Element> m_vec;

	void rva000FB4E0();
};

// ?rva000FB4E0@Rva000FB4E0@@QAEXXZ
void Rva000FB4E0::rva000FB4E0()
{
	std::vector<Rva000FAA30Elem> records( *reinterpret_cast<const std::vector<Rva000FAA30Elem> *>(
		reinterpret_cast<TeamPrototype *>( Glo012F1028 )->getTemplateInfo() ) );

	for ( unsigned int i = 0; i < records.size(); ++i )
		m_vec.push_back( reinterpret_cast<const Rva000FB210Element &>( records[ i ] ) );
}
