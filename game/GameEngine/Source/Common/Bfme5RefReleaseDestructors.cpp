// Six destructors that release a reference and then chain to their base.
//
// The member at +0x04 points at something whose count sits at +0x04 of itself.
// The decrement is an inline accessor that hands back the new count: the value
// is written to the member from one register and copied into another to be
// tested, which is that return value being materialised. Decrementing the
// member directly instead uses one register and is two bytes shorter.
//
// Only when the count has fallen to zero or below is the object deleted --
// through slot 0 with a 1, which is what delete on a class with a virtual
// destructor expands to. The store happens whether or not the delete follows.
//
// The base destructor then runs on this with the state word back at -1. The
// six are identical instruction for instruction and differ only in their
// relocations.

class BfmeRefCounted
{
public:
	virtual ~BfmeRefCounted(void);				// slot +0x00

	int bfmeRelease(void) { return --m_bfmeCount; }

	int m_bfmeCount;					// +0x04
};

class BfmeDtorMemberC
{
public:
	~BfmeDtorMemberC(void);					// retail 0x00887940

private:
	int m_bfmeValue;					// +0x00
};

class Gen_0045F280 : public BfmeDtorMemberC
{
public:
	~Gen_0045F280(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

class Gen_00467770 : public BfmeDtorMemberC
{
public:
	~Gen_00467770(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

class Gen_004682A0 : public BfmeDtorMemberC
{
public:
	~Gen_004682A0(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

class Gen_00468340 : public BfmeDtorMemberC
{
public:
	~Gen_00468340(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

class Gen_004683C0 : public BfmeDtorMemberC
{
public:
	~Gen_004683C0(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

class Gen_004736D0 : public BfmeDtorMemberC
{
public:
	~Gen_004736D0(void);

private:
	BfmeRefCounted *m_bfmeRef;				// +0x04
};

// ??1Gen_0045F280@@QAE@XZ
Gen_0045F280::~Gen_0045F280(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}

// ??1Gen_00467770@@QAE@XZ
Gen_00467770::~Gen_00467770(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}

// ??1Gen_004682A0@@QAE@XZ
Gen_004682A0::~Gen_004682A0(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}

// ??1Gen_00468340@@QAE@XZ
Gen_00468340::~Gen_00468340(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}

// ??1Gen_004683C0@@QAE@XZ
Gen_004683C0::~Gen_004683C0(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}

// ??1Gen_004736D0@@QAE@XZ
Gen_004736D0::~Gen_004736D0(void)
{
	BfmeRefCounted *reference = m_bfmeRef;

	if (reference)
	{
		if (reference->bfmeRelease() <= 0)
			delete reference;
	}
}
