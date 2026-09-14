// cl: /EHs-c-
// Six derived-class destructors.
//
// Each stores its own vtable pointer, frees the pointer member at +0x08, and
// then stores a SECOND vtable pointer before returning. That second store is
// the base destructor inlined: MSVC re-points the vptr once per class as the
// hierarchy unwinds, so two stores mean one base with a destructor of its own,
// even though that base destructor does nothing else.
//
// Only the two vtable addresses differ between the six, and those are
// relocations, so the six bodies compile from one shape.

void bfmeFreeBlock(void *block);					// retail 0x00881EF0

class BfmeDtorBase
{
public:
	virtual void bfmeSlot0(void);

	~BfmeDtorBase(void) {}

private:
	int m_bfmeBaseField;						// +0x04
};


class Gen_00924090 : public BfmeDtorBase
{
public:
	Gen_00924090(void);
	virtual ~Gen_00924090(void);

private:
	void *m_bfmeBlock;						// +0x08
};

class Gen_00924110 : public BfmeDtorBase
{
public:
	~Gen_00924110(void);

private:
	void *m_bfmeBlock;						// +0x08
};

class Gen_00924150 : public BfmeDtorBase
{
public:
	~Gen_00924150(void);

private:
	void *m_bfmeBlock;						// +0x08
};

class Gen_00926630 : public BfmeDtorBase
{
public:
	~Gen_00926630(void);

private:
	void *m_bfmeBlock;						// +0x08
};

class Gen_00929E80 : public BfmeDtorBase
{
public:
	~Gen_00929E80(void);

private:
	void *m_bfmeBlock;						// +0x08
};

class Gen_0092B920 : public BfmeDtorBase
{
public:
	~Gen_0092B920(void);

private:
	void *m_bfmeBlock;						// +0x08
};

// Retail's complete-destructor body is retained under ??1Gen_00924090@@QAE@XZ;
// the virtual declaration emits its ABI-equivalent UAE object symbol so the
// scalar-deleting wrapper can call the same matched body.
__declspec(noinline) Gen_00924090::~Gen_00924090(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}

Gen_00924090::Gen_00924090(void) {}

// A live object makes MSVC emit Gen_00924090's virtual scalar-deleting
// destructor alongside the matched complete destructor above.
void force_Gen_00924090_scalar(void)
{
	Gen_00924090 value;
}

// ??1Gen_00924110@@QAE@XZ
Gen_00924110::~Gen_00924110(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}

// ??1Gen_00924150@@QAE@XZ
Gen_00924150::~Gen_00924150(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}

// ??1Gen_00926630@@QAE@XZ
Gen_00926630::~Gen_00926630(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}

// ??1Gen_00929E80@@QAE@XZ
Gen_00929E80::~Gen_00929E80(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}

// ??1Gen_0092B920@@QAE@XZ
Gen_0092B920::~Gen_0092B920(void)
{
	bfmeFreeBlock(m_bfmeBlock);
}
