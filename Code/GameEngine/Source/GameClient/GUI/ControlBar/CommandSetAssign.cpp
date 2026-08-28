// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CommandSet::operator=, retail 0x0049CDA0, 64 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it from
// ControlBar::newCommandSetOverride, which copies the original over a fresh
// override through it.
//
// Memberwise all the way down: the base assignment first, then the name at
// +0x0C through AsciiString's own assignment, then twenty command pointers at
// +0x10, then one more word at +0x60, and this comes back in eax.
//
// The twenty are copied by a loop the compiler strength-reduces: it holds the
// distance between the two objects in a register and indexes the destination
// with it, so there is one address to step rather than two.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);	// retail 0x00887C90

private:
	char *m_bfmeData;
};

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other); // ILT 0x00048725

private:
	char m_bfmeHead[0x0C];
};

class CommandSetCommand;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet : public ScienceInfoBase
{
public:
	CommandSet &operator=(const CommandSet &other);

private:
	AsciiString m_bfmeName;					// +0x0C
	CommandSetCommand *m_bfmeCommands[20];			// +0x10
	Int m_bfmeTail;						// +0x60
};

// ??4CommandSet@@QAEAAV0@ABV0@@Z
CommandSet &CommandSet::operator=(const CommandSet &other)
{
	ScienceInfoBase::operator=(other);

	m_bfmeName = other.m_bfmeName;

	for (Int i = 0; i < 20; ++i)
		m_bfmeCommands[i] = other.m_bfmeCommands[i];

	m_bfmeTail = other.m_bfmeTail;

	return *this;
}
