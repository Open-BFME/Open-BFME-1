// Five self-linking head constructors.
//
// Each nulls its member, allocates a head block, links the block to itself
// through its two pointers, and stores it. The self-links go through the
// returned pointer rather than through the member, which is what keeps the
// member from being re-read between them -- storing the member first and then
// linking through it costs two reloads.
//
// The allocation size picks the allocator and whether its push takes an
// immediate byte, which is the three bytes separating the thirty-two byte
// bodies from the thirty-five byte ones.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

struct BfmeSelfHead
{
	BfmeSelfHead *m_bfmeNext;				// +0x00
	BfmeSelfHead *m_bfmePrev;				// +0x04
};

class Gen_0037E8F0
{
public:
	Gen_0037E8F0(void *owner);

private:
	BfmeSelfHead *m_bfmeHead;				// +0x00
};

class Gen_00443560
{
public:
	Gen_00443560(void);

private:
	int m_bfmePad;						// +0x00
	BfmeSelfHead *m_bfmeHead;				// +0x04
};

class Gen_004FD8A0
{
public:
	Gen_004FD8A0(void *owner);

private:
	BfmeSelfHead *m_bfmeHead;				// +0x00
};

class Gen_0056E0F0
{
public:
	Gen_0056E0F0(void *owner);

private:
	BfmeSelfHead *m_bfmeHead;				// +0x00
};

class Gen_0076F740
{
public:
	Gen_0076F740(void *owner);

private:
	BfmeSelfHead *m_bfmeHead;				// +0x00
};

// ??0Gen_0037E8F0@@QAE@PAX@Z
Gen_0037E8F0::Gen_0037E8F0(void *owner)
{
	m_bfmeHead = 0;

	BfmeSelfHead *head = (BfmeSelfHead *)bfmeNewAlloc(0xE0);

	head->m_bfmeNext = head;
	head->m_bfmePrev = head;

	m_bfmeHead = head;
}

// ??0Gen_00443560@@QAE@XZ
Gen_00443560::Gen_00443560(void)
{
	m_bfmeHead = 0;

	BfmeSelfHead *head = (BfmeSelfHead *)bfmeAllocNode(0xC);

	head->m_bfmeNext = head;
	head->m_bfmePrev = head;

	m_bfmeHead = head;
}

// ??0Gen_004FD8A0@@QAE@PAX@Z
Gen_004FD8A0::Gen_004FD8A0(void *owner)
{
	m_bfmeHead = 0;

	BfmeSelfHead *head = (BfmeSelfHead *)bfmeNewAlloc(0x338);

	head->m_bfmeNext = head;
	head->m_bfmePrev = head;

	m_bfmeHead = head;
}

// ??0Gen_0056E0F0@@QAE@PAX@Z
Gen_0056E0F0::Gen_0056E0F0(void *owner)
{
	m_bfmeHead = 0;

	BfmeSelfHead *head = (BfmeSelfHead *)bfmeAllocNode(0x44);

	head->m_bfmeNext = head;
	head->m_bfmePrev = head;

	m_bfmeHead = head;
}

// ??0Gen_0076F740@@QAE@PAX@Z
Gen_0076F740::Gen_0076F740(void *owner)
{
	m_bfmeHead = 0;

	BfmeSelfHead *head = (BfmeSelfHead *)bfmeAllocNode(0x1C);

	head->m_bfmeNext = head;
	head->m_bfmePrev = head;

	m_bfmeHead = head;
}
