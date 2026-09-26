// Eight allocate-and-ring constructors.
//
// The same opening as the allocate-and-initialise family -- a one-byte
// out-parameter and a literal zero handed to a member -- but the block that
// comes back is a list header, and the two stores that follow point it at
// itself. That self-link is what makes it a circular list with no elements,
// and it is written before the header is handed to the member, so the compiler
// still has the block in eax.
//
// As before the size chooses the allocator, and the four bytes the prologue
// reserves survive because the out-parameter's address escapes into the call.

typedef bool Bool;

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30

struct BfmeRing
{
	BfmeRing *m_bfmeNext;					// +0x00
	BfmeRing *m_bfmePrev;					// +0x04
};


class Gen_00072840
{
public:
	Gen_00072840(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0003FA0D

	BfmeRing *m_bfmeRing;
};

class Gen_00222BD0
{
public:
	Gen_00222BD0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x00031B6F

	BfmeRing *m_bfmeRing;
};

class Gen_0037E2B0
{
public:
	Gen_0037E2B0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0000D715

	BfmeRing *m_bfmeRing;
};

class Gen_004FA1D0
{
public:
	Gen_004FA1D0(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x00034446

	BfmeRing *m_bfmeRing;
};

class Gen_0056CC60
{
public:
	Gen_0056CC60(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x000208B0

	BfmeRing *m_bfmeRing;
};

class Gen_00627050
{
public:
	Gen_00627050(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0001F04B

	BfmeRing *m_bfmeRing;
};

class Gen_00631A90
{
public:
	Gen_00631A90(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0001EF06

	BfmeRing *m_bfmeRing;
};

class Gen_00764C70
{
public:
	Gen_00764C70(int flags);

private:
	void bfmeInit(Bool *out, int mode);			// ILT 0x0002F018

	BfmeRing *m_bfmeRing;
};

// ??0Gen_00072840@@QAE@H@Z
Gen_00072840::Gen_00072840(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x38);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_00222BD0@@QAE@H@Z
Gen_00222BD0::Gen_00222BD0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x24);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_0037E2B0@@QAE@H@Z
Gen_0037E2B0::Gen_0037E2B0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeNewAlloc(0xe0);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_004FA1D0@@QAE@H@Z
Gen_004FA1D0::Gen_004FA1D0(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeNewAlloc(0x338);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_0056CC60@@QAE@H@Z
Gen_0056CC60::Gen_0056CC60(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x44);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_00627050@@QAE@H@Z
Gen_00627050::Gen_00627050(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x24);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_00631A90@@QAE@H@Z
Gen_00631A90::Gen_00631A90(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x20);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}

// ??0Gen_00764C70@@QAE@H@Z
Gen_00764C70::Gen_00764C70(int flags)
{
	Bool ok;

	bfmeInit(&ok, 0);

	BfmeRing *ring = (BfmeRing *)bfmeAllocNode(0x1c);

	ring->m_bfmeNext = ring;
	ring->m_bfmePrev = ring;

	m_bfmeRing = ring;
}
