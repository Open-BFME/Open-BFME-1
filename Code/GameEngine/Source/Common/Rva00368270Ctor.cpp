// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: near-twin of the Gen0014AE40 owning-record constructor
// (Rva0014AE40OwnerDestructor.cpp / retail 0x0014ADC0) at retail 0x00368270,
// 102 bytes. Same GameSpyGroupRoom-copy-ctor + releaseBuffer shape, but this
// sibling is non-virtual (no vtable install) and takes one extra leading
// 4-byte value parameter stored directly at offset 0.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

class Bfme00368270String : private AsciiString
{
public:
	Bfme00368270String(const AsciiString &other) : AsciiString(other) {}
	~Bfme00368270String() {}
};

class Rva00368270
{
public:
	Rva00368270(void *p, AsciiString name);
	~Rva00368270();

private:
	void *m_00;
	Bfme00368270String m_bfmeMember;
	void *m_bfmeOwned;
	void *m_bfmeOther;
};

Rva00368270::Rva00368270(void *p, AsciiString name) :
	m_00(p),
	m_bfmeMember(name),
	m_bfmeOwned(0),
	m_bfmeOther(0)
{
}
