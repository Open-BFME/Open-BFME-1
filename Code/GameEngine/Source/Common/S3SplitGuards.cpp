// Four more bodies the ledger had split three ways, reunited. Each ends with
// an eight-byte return TRUE and a five-byte return FALSE that its own branches
// target, and both arms had been claimed as aliases elsewhere.
//
// 0x0061E5F0 and 0x0068D300 compare the same pair of fields -- an int at +0x30
// and a SHORT at +0x34, the word compare proving the width -- against a key
// whose two fields sit at +0x00/+0x04 in one case and +0x14/+0x18 in the
// other, and both gate on a kind word at +0x04 being 5. The second also
// rejects a null argument first.
//
// 0x00684B90 loads a pointer at +0x40E04 and asks it a question with the
// argument; the callee cleans one argument and runs with that pointer in ecx,
// so it is a member of whatever is stored there.
//
// 0x001EDA90 walks this to a sub-object at +0x20 -- the load and the add of
// the same 0x20 -- checks the pointer it holds and a 16-bit count at +0x04 of
// what that points at, and then compares. The comparison target's ILT is
// pinned as AsciiString::compare, and it must answer zero for a match.

class BfmeShortKey
{
public:
	int m_bfme0000;							// +0x00
	short m_bfme0004;						// +0x04
};

class Gen_0061e5f0
{
public:
	int bfmeMatches(const BfmeShortKey *key) const;

private:
	char m_bfmeHead[0x04];
	int m_bfmeKind;							// +0x04
	char m_bfmeMid[0x30 - 0x08];
	int m_bfme0030;							// +0x30
	short m_bfme0034;						// +0x34
};

class BfmeOwnerKey
{
public:
	char m_bfmeHead[0x14];
	int m_bfme0014;							// +0x14
	short m_bfme0018;						// +0x18
};

class Gen_0068d300
{
public:
	int bfmeMatches(const BfmeOwnerKey *owner) const;

private:
	char m_bfmeHead[0x04];
	int m_bfmeKind;							// +0x04
	char m_bfmeMid[0x30 - 0x08];
	int m_bfme0030;							// +0x30
	short m_bfme0034;						// +0x34
};

class Gen_00684b90Holder
{
public:
	int bfmeAccepts(void *argument);				// ILT 0x00004F6B
};

class Gen_00684b90
{
public:
	int bfmeCheck(void *argument);

private:
	char m_bfmeHead[0x40E04];
	Gen_00684b90Holder *m_bfmeHolder;				// +0x40E04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compare(const AsciiString &other) const;			// ILT 0x000220C5
};

class Gen_001eda90Sub
{
public:
	int compare(const AsciiString &other) const;			// same thunk

	AsciiString *m_bfmeText;					// +0x00
};

class BfmeCountedText
{
public:
	char m_bfmeHead[0x04];
	short m_bfmeCount;						// +0x04
};

class Gen_001eda90Arg
{
public:
	char m_bfmeHead[0x0C];
	AsciiString m_bfmeText;						// +0x0C
};

class Gen_001eda90
{
public:
	int bfmeCheck(Gen_001eda90Arg *argument);

private:
	char m_bfmeHead[0x20];
	Gen_001eda90Sub m_bfmeSub;					// +0x20
};

// ?bfmeMatches@Gen_0061e5f0@@QBEHPBVBfmeShortKey@@@Z
int Gen_0061e5f0::bfmeMatches(const BfmeShortKey *key) const
{
	if (m_bfmeKind == 5 && m_bfme0030 == key->m_bfme0000 && m_bfme0034 == key->m_bfme0004)
		return 1;

	return 0;
}

// ?bfmeMatches@Gen_0068d300@@QBEHPBVBfmeOwnerKey@@@Z
int Gen_0068d300::bfmeMatches(const BfmeOwnerKey *owner) const
{
	if (owner && m_bfmeKind == 5 && owner->m_bfme0014 == m_bfme0030 && owner->m_bfme0018 == m_bfme0034)
		return 1;

	return 0;
}

// ?bfmeCheck@Gen_00684b90@@QAEHPAX@Z
int Gen_00684b90::bfmeCheck(void *argument)
{
	Gen_00684b90Holder *holder = m_bfmeHolder;

	if (holder && holder->bfmeAccepts(argument))
		return 1;

	return 0;
}

// ?bfmeCheck@Gen_001eda90@@QAEHPAVGen_001eda90Arg@@@Z
int Gen_001eda90::bfmeCheck(Gen_001eda90Arg *argument)
{
	if (m_bfmeSub.m_bfmeText
		&& ((BfmeCountedText *)m_bfmeSub.m_bfmeText)->m_bfmeCount != 0
		&& m_bfmeSub.compare(argument->m_bfmeText) == 0)
		return 1;

	return 0;
}
