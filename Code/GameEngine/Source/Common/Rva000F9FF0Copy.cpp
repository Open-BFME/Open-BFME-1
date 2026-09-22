// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// Retail000F9FF0/181B; opaque copy-constructor identity, not a guessed pair.
// The old bank inferred pair<const Key,Value> from a generated tgrid caller;
// no independent evidence establishes a pair. The physical body witnesses
// AsciiString+0, four words+4..10, a24-byte POD subobject+14, fields+2C..40,
// and the already-matched Gen_000F9C60 copy at+44 via ILT0003ED92.
// A native implicit POD copy preserves the six-word ECX/EDX transfer;
// an explicit memberwise constructor flattens it and changes the bytes.
// The owner is intentionally address-derived; no generated caller identity is
// carried into this class.

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

// Opaque, address-qualified six-word subobject at +0x14.  Its copy contract
// is the six scalar loads/stores visible between the two lea instructions in
// the retail body; its ownership/name remain unknown.
struct Rva000F9FF0Block14
{
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
	int m_f28;

};

class Rva000F9FF0
{
public:
	Rva000F9FF0(const Rva000F9FF0 &other);

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

Rva000F9FF0::Rva000F9FF0(const Rva000F9FF0 &other)
		: m_name(other.m_name),
		  m_f04(other.m_f04),
		  m_f08(other.m_f08),
		  m_f0c(other.m_f0c),
		  m_f10(other.m_f10),
		  m_block14(other.m_block14),
		  m_f2c(other.m_f2c),
		  m_f30(other.m_f30),
		  m_f34(other.m_f34),
		  m_f38(other.m_f38),
		  m_f3c(other.m_f3c),
		  m_f40(other.m_f40),
		  m_gen44(other.m_gen44)
	{
	}
