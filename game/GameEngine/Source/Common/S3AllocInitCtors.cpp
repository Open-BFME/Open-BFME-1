// Seven allocate-and-initialise constructors.
//
// Each hands a one-byte out-parameter and a literal zero to a member, then
// stores a fresh block in its only field and returns this. The constructor's
// own argument is never read.
//
// The size decides which allocator is called: at or below 0x80 bytes the node
// allocator, above it the plain one -- the same split the allocate-and-copy
// family makes, but here the choice is baked in because the size is a literal.
//
// The out-parameter is a single byte whose address escapes into the call, so
// the four bytes the prologue reserves with push ecx survive; the byte itself
// sits at the top of that slot, [esp+0xB] once the arguments are pushed.

typedef bool Bool;

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30


class Gen_00072B10
{
public:
	Gen_00072B10(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0004636C

	void *m_bfmePtr;
};

class Gen_00126570
{
public:
	Gen_00126570(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0001015E

	void *m_bfmePtr;
};

class Gen_00586170
{
public:
	Gen_00586170(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x00014F79

	void *m_bfmePtr;
};

class Gen_006051A0
{
public:
	Gen_006051A0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0000D60C

	void *m_bfmePtr;
};

class Gen_00631BB0
{
public:
	Gen_00631BB0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x00047159

	void *m_bfmePtr;
};

class Gen_00652C60
{
public:
	Gen_00652C60(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0001548D

	void *m_bfmePtr;
};

class Gen_00764DA0
{
public:
	Gen_00764DA0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x00043306

	void *m_bfmePtr;
};

// ??0Gen_00072B10@@QAE@H@Z
Gen_00072B10::Gen_00072B10(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeNewAlloc(0x110);
}

// ??0Gen_00126570@@QAE@H@Z
Gen_00126570::Gen_00126570(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeNewAlloc(0x84);
}

// ??0Gen_00586170@@QAE@H@Z
Gen_00586170::Gen_00586170(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeAllocNode(0x50);
}

// ??0Gen_006051A0@@QAE@H@Z
Gen_006051A0::Gen_006051A0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeAllocNode(0x70);
}

// ??0Gen_00631BB0@@QAE@H@Z
Gen_00631BB0::Gen_00631BB0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeAllocNode(0x48);
}

// ??0Gen_00652C60@@QAE@H@Z
Gen_00652C60::Gen_00652C60(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeNewAlloc(0x1d8);
}

// ??0Gen_00764DA0@@QAE@H@Z
Gen_00764DA0::Gen_00764DA0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	m_bfmePtr = bfmeAllocNode(0x48);
}
