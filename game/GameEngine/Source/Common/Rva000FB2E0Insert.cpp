// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 000FB2E0/212B: native insertion into the96B record vector.
// Caller002A30D0 +182 passes its Object* (ESI) after getControllingPlayer,
// with receiver Player+684. Constructor000FA1B0 dereferences that Object.
// The inherited unsigned-int spelling was an untyped address; use Object*.
// The owner and method remain address-derived from the bank.

#include "ascii_string.h"
#include <vector>
class Object;

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

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

// The +0x44 subobject is copied by the proven 0x000F9FF0 body but is
// destroyed through the AudioEventRTS ILT at 0x0002671F.  Keep its copy
// identity opaque; the independently audited pin names the witnessed destructor.

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

// Genuine 96-byte record layout from the independently landed F9FF0 copy
// body.  The vector spelling is the already-proven FB210 instantiation, not a
// guessed pair identity; its copy constructor is routed to the retail F9FF0
// body through the witnessed 0x0004845F ILT.
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
	Rva000FB210Element(Object *param1);
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

struct Rva000FB2E0Owner
{
	void *m_unknown00;
	std::vector<Rva000FB210Element> m_vec;

	int Gen000FB2E0Method(Object *param1, bool param2);
};

int Rva000FB2E0Owner::Gen000FB2E0Method(Object *param1, bool param2)
{
	Rva000FB210Element temp(param1);

	if (param2)
		temp.m_f2c = 0;

	// Keep the vector as the native STLport object.  The reference alias makes
	// MSVC rebase esi to this+4 before its capacity test; native size() then
	// emits the retail start/finish order and the 96-byte divide-by-magic.
	std::vector<Rva000FB210Element> &vec = m_vec;
	vec.push_back(temp);
	return (int)vec.size() - 1;
}

