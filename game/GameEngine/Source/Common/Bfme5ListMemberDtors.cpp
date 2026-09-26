// Two destructors whose only member is a list.
//
// Each is empty in source. The list member's destructor is inline: it calls
// the out-of-line clear and then frees the twelve-byte sentinel it keeps,
// guarded because an empty-constructed list has none. Then the base destructor
// runs on this with the state word back at -1.
//
// One of the two stores a vftable first and reaches its base through a virtual
// destructor; the other has no vptr at all, and those six bytes are the whole
// difference between them.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeListNode
{
	BfmeListNode *m_bfmeNext;				// +0x00
	BfmeListNode *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeListA
{
public:
	~BfmeListA(void)
	{
		bfmeClear();

		if (m_bfmeNode)
			bfmeDeallocate(m_bfmeNode, sizeof(BfmeListNode));
	}

	void bfmeClear(void);					// retail 0x00021CD3

private:
	BfmeListNode *m_bfmeNode;				// +0x00
};

class BfmeListB
{
public:
	~BfmeListB(void)
	{
		bfmeClear();

		if (m_bfmeNode)
			bfmeDeallocate(m_bfmeNode, sizeof(BfmeListNode));
	}

	void bfmeClear(void);					// retail 0x0001900B

private:
	BfmeListNode *m_bfmeNode;				// +0x00
};

class BfmeDtorBaseW
{
public:
	virtual ~BfmeDtorBaseW(void);				// retail 0x0003F25B

private:
	char m_bfmePad[0x10];					// +0x04
};

class BfmeDtorBaseV
{
public:
	~BfmeDtorBaseV(void);					// retail 0x00887940

private:
	int m_bfmeField;					// +0x00
};

class Gen_0009F7A0 : public BfmeDtorBaseW
{
public:
	virtual ~Gen_0009F7A0(void);

private:
	BfmeListA m_bfmeList;					// +0x14
};

class Gen_00080950 : public BfmeDtorBaseV
{
public:
	~Gen_00080950(void);

private:
	BfmeListB m_bfmeList;					// +0x04
};

// ??1Gen_0009F7A0@@UAE@XZ
Gen_0009F7A0::~Gen_0009F7A0(void)
{
}

// ??1Gen_00080950@@QAE@XZ
Gen_00080950::~Gen_00080950(void)
{
}
