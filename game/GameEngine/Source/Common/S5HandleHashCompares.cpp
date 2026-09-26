// Open-BFME5: twelve more of the hash-compare shape S3HandleCompareAssign.cpp
// already lands four of -- six PAIRS, each pair sharing a helper and a
// sentinel.
//
// The body reads the dword at +0x04 of two objects, hands them to a __cdecl
// helper and tests the answer against a constant that is NOT zero, so the
// helper returns a hash rather than an ordering.  The result is materialised
// as xor ecx,ecx / setne cl / mov al,cl -- a byte, so Bool.
//
// SIX HELPERS, SIX SENTINELS, AND THEY PAIR UP ONE TO ONE.  Each helper is
// only ever tested against its own constant, which is what a per-type hash of
// the empty or default value looks like; the constants are not shared and
// neither are the helpers.
//
// THE LEVER IS READ ORDER, not argument order.  Retail loads the OTHER's
// member into eax first and this's into ecx second, then pushes eax and ecx
// so this's member is the first argument.  Passing the two members straight
// into the call gives a third register; naming both as locals with the
// OTHER's read FIRST reproduces retail exactly.  Same lever as the four
// already landed.
//
// IDENTITY IS NOT RECOVERED.  Twelve classes at twelve addresses, each with
// one four-byte head and the compared dword at +0x04.

unsigned int bfmeHash00007518(unsigned int left, unsigned int right);	// ILT 0x00007518
unsigned int bfmeHash0000DD28(unsigned int left, unsigned int right);	// ILT 0x0000DD28
unsigned int bfmeHash00010AFA(unsigned int left, unsigned int right);	// ILT 0x00010AFA
unsigned int bfmeHash00013412(unsigned int left, unsigned int right);	// ILT 0x00013412
unsigned int bfmeHash0002A473(unsigned int left, unsigned int right);	// ILT 0x0002A473
unsigned int bfmeHash0002BB70(unsigned int left, unsigned int right);	// ILT 0x0002BB70

enum { BFME_HASH_EQUAL_00007518 = 0x944ADA98 };
enum { BFME_HASH_EQUAL_0000DD28 = 0x462E416F };
enum { BFME_HASH_EQUAL_00010AFA = 0x993BA311 };
enum { BFME_HASH_EQUAL_00013412 = 0x342C2BE0 };
enum { BFME_HASH_EQUAL_0002A473 = 0x66DE9C79 };
enum { BFME_HASH_EQUAL_0002BB70 = 0xA69B3F6A };

class Gen_00528EC0
{
public:
	bool bfmeDiffers(const Gen_00528EC0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_00529270
{
public:
	bool bfmeDiffers(const Gen_00529270 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054EC50
{
public:
	bool bfmeDiffers(const Gen_0054EC50 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054EC80
{
public:
	bool bfmeDiffers(const Gen_0054EC80 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F1A0
{
public:
	bool bfmeDiffers(const Gen_0054F1A0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F1D0
{
public:
	bool bfmeDiffers(const Gen_0054F1D0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0056E190
{
public:
	bool bfmeDiffers(const Gen_0056E190 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0056E790
{
public:
	bool bfmeDiffers(const Gen_0056E790 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_005941B0
{
public:
	bool bfmeDiffers(const Gen_005941B0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_005958C0
{
public:
	bool bfmeDiffers(const Gen_005958C0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0061A5C0
{
public:
	bool bfmeDiffers(const Gen_0061A5C0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0061A8D0
{
public:
	bool bfmeDiffers(const Gen_0061A8D0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

// ?bfmeDiffers@Gen_00528EC0@@QBE_NABV1@@Z		35B
bool Gen_00528EC0::bfmeDiffers(const Gen_00528EC0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002A473(mine, theirs) != BFME_HASH_EQUAL_0002A473;
}

// ?bfmeDiffers@Gen_00529270@@QBE_NABV1@@Z		35B
bool Gen_00529270::bfmeDiffers(const Gen_00529270 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002A473(mine, theirs) != BFME_HASH_EQUAL_0002A473;
}

// ?bfmeDiffers@Gen_0054EC50@@QBE_NABV1@@Z		35B
bool Gen_0054EC50::bfmeDiffers(const Gen_0054EC50 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002BB70(mine, theirs) != BFME_HASH_EQUAL_0002BB70;
}

// ?bfmeDiffers@Gen_0054EC80@@QBE_NABV1@@Z		35B
bool Gen_0054EC80::bfmeDiffers(const Gen_0054EC80 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00013412(mine, theirs) != BFME_HASH_EQUAL_00013412;
}

// ?bfmeDiffers@Gen_0054F1A0@@QBE_NABV1@@Z		35B
bool Gen_0054F1A0::bfmeDiffers(const Gen_0054F1A0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002BB70(mine, theirs) != BFME_HASH_EQUAL_0002BB70;
}

// ?bfmeDiffers@Gen_0054F1D0@@QBE_NABV1@@Z		35B
bool Gen_0054F1D0::bfmeDiffers(const Gen_0054F1D0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00013412(mine, theirs) != BFME_HASH_EQUAL_00013412;
}

// ?bfmeDiffers@Gen_0056E190@@QBE_NABV1@@Z		35B
bool Gen_0056E190::bfmeDiffers(const Gen_0056E190 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00010AFA(mine, theirs) != BFME_HASH_EQUAL_00010AFA;
}

// ?bfmeDiffers@Gen_0056E790@@QBE_NABV1@@Z		35B
bool Gen_0056E790::bfmeDiffers(const Gen_0056E790 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00010AFA(mine, theirs) != BFME_HASH_EQUAL_00010AFA;
}

// ?bfmeDiffers@Gen_005941B0@@QBE_NABV1@@Z		35B
bool Gen_005941B0::bfmeDiffers(const Gen_005941B0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00007518(mine, theirs) != BFME_HASH_EQUAL_00007518;
}

// ?bfmeDiffers@Gen_005958C0@@QBE_NABV1@@Z		35B
bool Gen_005958C0::bfmeDiffers(const Gen_005958C0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00007518(mine, theirs) != BFME_HASH_EQUAL_00007518;
}

// ?bfmeDiffers@Gen_0061A5C0@@QBE_NABV1@@Z		35B
bool Gen_0061A5C0::bfmeDiffers(const Gen_0061A5C0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0000DD28(mine, theirs) != BFME_HASH_EQUAL_0000DD28;
}

// ?bfmeDiffers@Gen_0061A8D0@@QBE_NABV1@@Z		35B
bool Gen_0061A8D0::bfmeDiffers(const Gen_0061A8D0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0000DD28(mine, theirs) != BFME_HASH_EQUAL_0000DD28;
}
