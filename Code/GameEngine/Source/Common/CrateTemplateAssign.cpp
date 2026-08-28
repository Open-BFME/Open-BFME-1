// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CrateTemplate::operator=, retail 0x0037A1A0, 109 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it.
//
// Memberwise, and every member is readable from how it is copied. The base
// assignment first -- the same one CommandSet::operator= at 0x0049CDA0 calls.
// Then the name at +0x0C through AsciiString's own assignment, two words at
// +0x10 and +0x14 copied straight, twenty-four bytes at +0x18 copied six words
// at a time through a base pointer at each end, one more word at +0x30, the
// entry list at +0x34 through its out-of-line operator=, and a byte at +0x38.
//
// The twenty-four bytes are a nested struct rather than six members of this
// class: written as members the compiler folds the offsets onto this and drops
// the two leas.

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

struct crateCreationEntry;

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc = allocator<_Tp> > class list
{
public:
	list<_Tp, _Alloc> &operator=(const list<_Tp, _Alloc> &other); // retail 0x0037A0D0

private:
	void *m_bfmeNode;
};

}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
struct crateCreationEntry
{
	char m_bfmeBody[0x0C];
};

struct BfmeCrateChances
{
	int m_bfmeA, m_bfmeB, m_bfmeC, m_bfmeD, m_bfmeE, m_bfmeF;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate : public ScienceInfoBase
{
public:
	CrateTemplate &operator=(const CrateTemplate &other);

private:
	AsciiString m_bfmeName;					// +0x0C
	int m_bfme10;						// +0x10
	int m_bfme14;						// +0x14
	BfmeCrateChances m_bfmeChances;				// +0x18
	int m_bfme30;						// +0x30
	_STL::list<crateCreationEntry> m_bfmeEntries;		// +0x34
	bool m_bfme38;						// +0x38
};

// ??4CrateTemplate@@QAEAAV0@ABV0@@Z
CrateTemplate &CrateTemplate::operator=(const CrateTemplate &other)
{
	ScienceInfoBase::operator=(other);

	m_bfmeName = other.m_bfmeName;
	m_bfme10 = other.m_bfme10;
	m_bfme14 = other.m_bfme14;
	m_bfmeChances = other.m_bfmeChances;
	m_bfme30 = other.m_bfme30;
	m_bfmeEntries = other.m_bfmeEntries;
	m_bfme38 = other.m_bfme38;

	return *this;
}
