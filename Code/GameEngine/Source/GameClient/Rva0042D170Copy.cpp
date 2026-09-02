// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Copy constructor at 0x0042D170. Vtable 0x010F3550 (three slots). +4 and
// +0x18 are 4-byte copy-destruct members (retail ILTs 0x00033EC4 / 0x0002D49D);
// +0xC is AsciiString (copy 0x00887B60).

#include "StringInline.h"

struct Rva0042D170Member04
{
	int a;
	Rva0042D170Member04();
	Rva0042D170Member04(const Rva0042D170Member04 &);
	~Rva0042D170Member04();
};

struct Rva0042D170Member18
{
	int a;
	Rva0042D170Member18();
	Rva0042D170Member18(const Rva0042D170Member18 &);
	~Rva0042D170Member18();
};

class Rva0042D170
{
public:
	Rva0042D170(const Rva0042D170 &other);
	virtual ~Rva0042D170();
	virtual void slot1();
	virtual void slot2();

private:
	Rva0042D170Member04 m_04;
	unsigned char m_08;
	unsigned char m_pad09[3];
	AsciiString m_0c;
	unsigned char m_10;
	unsigned char m_pad11[3];
	int m_14;
	Rva0042D170Member18 m_18;
	int m_1c;
	int m_20;
};

// ??0Rva0042D170@@QAE@ABV0@@Z
Rva0042D170::Rva0042D170(const Rva0042D170 &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1c(other.m_1c)
	, m_20(other.m_20)
{
}
