// cl: /EHs-c-
// Eight more bodies in two shapes.
//
// 0x00783A50, 0x008925F0, 0x00892CA0 and 0x00893990 test a pointer member,
// run it past a __cdecl check, and only when that check answers zero hand the
// same member to a second __cdecl call. The member is RE-READ for the second
// call rather than kept in a register, which is what a plain member expression
// gives once a call sits between the two uses.
//
// 0x008AB8E0, 0x008BD820, 0x008BD880 and 0x008BD8E0 are destructors of classes
// that own one child at +0x10. The vptr store lands between the test and the
// branch. The child is released with an explicit destructor call followed by a
// two-argument free carrying the size, which is the class-level
// operator delete(void *, size_t) form -- the size sixteen is sizeof of the
// child, not a constant the body computes.

int bfmeCheckA(void *p);					// retail 0x00894D90
__declspec(noinline) void bfmeDropA(void *p);		// retail 0x00895320
int bfmeCheckB(void *p);					// retail 0x00894DB0
__declspec(noinline) void bfmeDropB(void *p);		// retail 0x008961C0

extern void (*TheBfmeFree)(void *p, unsigned int bytes);	// 0x01337830

class BfmeChildA
{
public:
	~BfmeChildA(void);					// retail 0x008976E0

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

class BfmeChildB
{
public:
	~BfmeChildB(void);					// retail 0x0089CC70

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeDropObjectB
{
public:
	~BfmeDropObjectB(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x10];
};


class Gen_00783A50
{
public:
	void bfmeCleanup(void);

private:
	void *m_bfmeItem;
};

class Gen_008925F0
{
public:
	void bfmeCleanup(void);

private:
	void *m_bfmeItem;
};

class Gen_00892CA0
{
public:
	void bfmeCleanup(void);

private:
	void *m_bfmeItem;
};

class Gen_00893990
{
public:
	void bfmeCleanup(void);

private:
	void *m_bfmeItem;
};

class Gen_008AB8E0
{
public:
	~Gen_008AB8E0(void);

	virtual void bfmeSlot0(void);

private:
	char m_bfmeHead[0x10 - 4];
	BfmeChildA *m_bfmeChild;				// +0x10
};

class Gen_008BD820
{
public:
	~Gen_008BD820(void);

	virtual void bfmeSlot0(void);

private:
	char m_bfmeHead[0x10 - 4];
	BfmeChildB *m_bfmeChild;				// +0x10
};

class Gen_008BD880
{
public:
	~Gen_008BD880(void);

	virtual void bfmeSlot0(void);

private:
	char m_bfmeHead[0x10 - 4];
	BfmeChildB *m_bfmeChild;				// +0x10
};

class Gen_008BD8E0
{
public:
	~Gen_008BD8E0(void);

	virtual void bfmeSlot0(void);

private:
	char m_bfmeHead[0x10 - 4];
	BfmeChildB *m_bfmeChild;				// +0x10
};

// ?bfmeDropA@@YAXPAX@Z
__declspec(noinline) void bfmeDropA(void *p)
{
	delete (BfmeDropObjectA *)p;
}

// ?bfmeDropB@@YAXPAX@Z
__declspec(noinline) void bfmeDropB(void *p)
{
	delete (BfmeDropObjectB *)p;
}

// ?bfmeCleanup@Gen_00783A50@@QAEXXZ
void Gen_00783A50::bfmeCleanup(void)
{
	if (m_bfmeItem)
	{
		if (bfmeCheckA(m_bfmeItem) == 0)
			bfmeDropA(m_bfmeItem);
	}
}

// ?bfmeCleanup@Gen_008925F0@@QAEXXZ
void Gen_008925F0::bfmeCleanup(void)
{
	if (m_bfmeItem)
	{
		if (bfmeCheckB(m_bfmeItem) == 0)
			bfmeDropB(m_bfmeItem);
	}
}

// ?bfmeCleanup@Gen_00892CA0@@QAEXXZ
void Gen_00892CA0::bfmeCleanup(void)
{
	if (m_bfmeItem)
	{
		if (bfmeCheckB(m_bfmeItem) == 0)
			bfmeDropB(m_bfmeItem);
	}
}

// ?bfmeCleanup@Gen_00893990@@QAEXXZ
void Gen_00893990::bfmeCleanup(void)
{
	if (m_bfmeItem)
	{
		if (bfmeCheckB(m_bfmeItem) == 0)
			bfmeDropB(m_bfmeItem);
	}
}

// ??1Gen_008AB8E0@@QAE@XZ
Gen_008AB8E0::~Gen_008AB8E0(void)
{
	delete m_bfmeChild;
}

// ??1Gen_008BD820@@QAE@XZ
Gen_008BD820::~Gen_008BD820(void)
{
	delete m_bfmeChild;
}

// ??1Gen_008BD880@@QAE@XZ
Gen_008BD880::~Gen_008BD880(void)
{
	delete m_bfmeChild;
}

// ??1Gen_008BD8E0@@QAE@XZ
Gen_008BD8E0::~Gen_008BD8E0(void)
{
	delete m_bfmeChild;
}
