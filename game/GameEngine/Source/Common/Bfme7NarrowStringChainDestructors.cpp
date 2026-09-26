// Six non-polymorphic destructors of the same shape: a narrow-string base and
// two narrow-string members, nothing else.
//
// Sibling of Bfme5PlainChainDestructors.cpp; the same three-call chain, but
// here all three callees are the ONE narrow destructor at 0x00887940
// (StringBase<char>'s, private, which is why the ledger spells it AAE).  A
// wide member would call 0x008881D0 instead, and none of these six does --
// that call target is the whole reason these are not the LANPlayer destructor
// they were once landed as: LANPlayer holds three UnicodeStrings and its body
// is the one at 0x00685830 that calls 0x008881D0 three times.
//
// The unwind state word counts what is still to be destroyed: 1, then 0
// (written as a byte, only the low one changes), then -1 once both members are
// gone and only the base is left.
//
// IDENTITY IS NOT RECOVERED.  Six retail classes share this layout and nothing
// in the bytes separates them, so each is named for its own address.

class BfmeDtorMemberC
{
public:
	~BfmeDtorMemberC(void);					// retail 0x00887940

private:
	int m_bfmeValue;
};

class Gen_001D6700 : public BfmeDtorMemberC
{
public:
	~Gen_001D6700(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

class Gen_004F10B0 : public BfmeDtorMemberC
{
public:
	~Gen_004F10B0(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

class Gen_00581FB0 : public BfmeDtorMemberC
{
public:
	~Gen_00581FB0(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

class Gen_0060AA70 : public BfmeDtorMemberC
{
public:
	~Gen_0060AA70(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

class Gen_00762250 : public BfmeDtorMemberC
{
public:
	~Gen_00762250(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

class Gen_00762E10 : public BfmeDtorMemberC
{
public:
	~Gen_00762E10(void);

private:
	BfmeDtorMemberC m_bfmeFirst;				// +0x04
	BfmeDtorMemberC m_bfmeSecond;				// +0x08
};

// ??1Gen_001D6700@@QAE@XZ
Gen_001D6700::~Gen_001D6700(void)
{
}

// ??1Gen_004F10B0@@QAE@XZ
Gen_004F10B0::~Gen_004F10B0(void)
{
}

// ??1Gen_00581FB0@@QAE@XZ
Gen_00581FB0::~Gen_00581FB0(void)
{
}

// ??1Gen_0060AA70@@QAE@XZ
Gen_0060AA70::~Gen_0060AA70(void)
{
}

// ??1Gen_00762250@@QAE@XZ
Gen_00762250::~Gen_00762250(void)
{
}

// ??1Gen_00762E10@@QAE@XZ
Gen_00762E10::~Gen_00762E10(void)
{
}
