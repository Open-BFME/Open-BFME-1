// cl: /DNDEBUG /MD /EHsc
// partial score=0.87 date=2026-09-06
// Open-BFME7: Rva0045EF90Object's copy constructor (0x0045E830, 163 B). The
// class and its vtables (base 0x010F6F58, derived 0x010F6F80) are the same
// family already landed for the destructor in
// Rva0045EF90Destructor.cpp -- reused here with the same member layout so
// the two bodies agree. GameSpyGroupRoom below stands in for the real
// AsciiString-sized member: its copy constructor is the address-aliased
// ??0GameSpyGroupRoom@@QAE@ABV0@@Z row already matched at 0x00887B60
// (a StringBase<char> copy ctor under a GameSpyGroupRoom alias), called
// three times at +8, +0xC and +0x28.

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &source);
	~GameSpyGroupRoom();

private:
	unsigned m_value;
};

class Rva0045EF90Base
{
public:
	Rva0045EF90Base(const Rva0045EF90Base &source) : m_value(source.m_value) {}
	virtual ~Rva0045EF90Base();

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object(const Rva0045EF90Object &source);
	virtual ~Rva0045EF90Object();

private:
	GameSpyGroupRoom m_first;
	GameSpyGroupRoom m_second;
	unsigned m_handle;
	unsigned m_value14;
	unsigned m_value18;
	unsigned m_value1c;
	unsigned m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[3];
	GameSpyGroupRoom m_last;
};

Rva0045EF90Object::Rva0045EF90Object(const Rva0045EF90Object &source)
	: Rva0045EF90Base(source)
	, m_first(source.m_first)
	, m_second(source.m_second)
	, m_handle(source.m_handle)
	, m_value14(source.m_value14)
	, m_value18(source.m_value18)
	, m_value1c(source.m_value1c)
	, m_value20(source.m_value20)
	, m_value24(source.m_value24)
	, m_last(source.m_last)
{
}
