// Six stop-and-reset bodies.
//
// Each drops a target it owns and then pokes something reached two hops away.
// The host is loaded before the guard, not after it -- that is what pins the
// argument at [esp+0x0C] and costs the extra register; loading it after the
// if-block is two bytes shorter and does not match.
//
// The target is finished through slot +0x14, then deleted: the null test, the
// vptr load and the call to slot 0 with a 1 are what delete on a class with a
// virtual destructor expands to, and the member is re-read for it because the
// finish call could have changed it in memory. The member is nulled inside the
// guard.
//
// The last statement rewrites the argument slot to zero in place and jumps, so
// the reset is a tail call. Five of the six keep the target at +0x40 and one at
// +0x2C, which is the only difference between them.

class BfmeStopOther
{
public:
	void bfmeReset(void *value);				// retail 0x0002A88D
};

class BfmeStopHost
{
public:
	char m_bfmePad[0x23C];					// +0x00
	BfmeStopOther *m_bfmeOther;				// +0x23C
};

class BfmeStopOwner
{
public:
	char m_bfmePad[0x10];					// +0x00
	BfmeStopHost *m_bfmeHost;				// +0x10
};

class BfmeStopTarget
{
public:
	virtual ~BfmeStopTarget(void);				// slot +0x00
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeFinish(void *value);			// slot +0x14
};

class Gen_0015BA80
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0x20];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x40
};

class Gen_0015BD10
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0x20];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x40
};

class Gen_0015E9E0
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0x20];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x40
};

class Gen_00189D60
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0xC];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x2C
};

class Gen_002BBE30
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0x20];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x40
};

class Gen_002BC0B0
{
public:
	void bfmeStop(void *value);

private:
	char m_bfmePadA[0x1C];					// +0x00
	BfmeStopOwner *m_bfmeOwner;				// +0x1C
	char m_bfmePadB[0x20];					// +0x20
	BfmeStopTarget *m_bfmeTarget;				// +0x40
};

// ?bfmeStop@Gen_0015BA80@@QAEXPAX@Z
void Gen_0015BA80::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}

// ?bfmeStop@Gen_0015BD10@@QAEXPAX@Z
void Gen_0015BD10::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}

// ?bfmeStop@Gen_0015E9E0@@QAEXPAX@Z
void Gen_0015E9E0::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}

// ?bfmeStop@Gen_00189D60@@QAEXPAX@Z
void Gen_00189D60::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}

// ?bfmeStop@Gen_002BBE30@@QAEXPAX@Z
void Gen_002BBE30::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}

// ?bfmeStop@Gen_002BC0B0@@QAEXPAX@Z
void Gen_002BC0B0::bfmeStop(void *value)
{
	BfmeStopHost *host = m_bfmeOwner->m_bfmeHost;

	if (m_bfmeTarget)
	{
		m_bfmeTarget->bfmeFinish(value);
		delete m_bfmeTarget;
		m_bfmeTarget = 0;
	}

	if (host->m_bfmeOther)
		host->m_bfmeOther->bfmeReset(0);
}
