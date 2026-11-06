// Four iterator makers.
//
// Each returns an eight-byte record through a hidden pointer -- the first
// stack argument, which is why the answer is stored through [esp+4] and the
// body cleans four bytes. Three pair a member with a fixed address; the fourth
// pairs this with the dword at +0x00.
//
// The record has to be built by a constructor in the return expression: with a
// named local the compiler copies it into the return slot instead of writing
// through the slot directly.

struct BfmeIterator
{
	BfmeIterator(void *node, void *owner)
	{
		m_bfmeNode = node;
		m_bfmeOwner = owner;
	}

	void *m_bfmeNode;					// +0x00
	void *m_bfmeOwner;					// +0x04
};


// These iterator words are code addresses, not data owners. The ledger's
// ILTs at RVAs 0x00022A70, 0x0002FEE6 and 0x00008224 jump to the next-link
// getters at 0x000C8A30, 0x001604E0 and 0x001605D0 respectively. Keep the
// thunk addresses: substituting the getter body would change the stored word.
// The ledger records 0x00008224 as TeamInQueue::dlink_next_TeamReadyQueue.
void j_00022a70();

class Gen_000CBB80
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x274];
	void *m_bfmeNode;					// +0x274
};

class Gen_00161290
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x4];
	void *m_bfmeNode;					// +0x4
};

class TeamInQueue
{
public:
	TeamInQueue *dlink_next_TeamReadyQueue() const;
	TeamInQueue *dlink_next_TeamBuildQueue() const;
};

typedef TeamInQueue *(TeamInQueue::*BfmeNextGetter)() const;

class Gen_001612B0
{
public:
	BfmeIterator bfmeMake(void);

private:
	char m_bfmeHead[0x8];
	void *m_bfmeNode;					// +0x8
};

class Gen_004C14F0
{
public:
	BfmeIterator bfmeMake(void);

private:
	void *m_bfmeFirst;					// +0x00
};

// ?bfmeMake@Gen_000CBB80@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_000CBB80::bfmeMake(void)
{
	return BfmeIterator(m_bfmeNode, (void *)&j_00022a70);
}

// ?bfmeMake@Gen_00161290@@QAE?AUBfmeIterator@@XZ
// Retail stores the recorded body name's address (thunk VA 0x0042FEE6),
// the same member-pointer union spelling Gen_001612B0 uses.
BfmeIterator Gen_00161290::bfmeMake(void)
{
	union
	{
		BfmeNextGetter member;
		void *raw;
	} getter;
	getter.member = &TeamInQueue::dlink_next_TeamBuildQueue;
	return BfmeIterator(m_bfmeNode, getter.raw);
}

// ?bfmeMake@Gen_001612B0@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_001612B0::bfmeMake(void)
{
	union
	{
		BfmeNextGetter member;
		void *raw;
	} getter;
	getter.member = &TeamInQueue::dlink_next_TeamReadyQueue;
	return BfmeIterator(m_bfmeNode, getter.raw);
}

// ?bfmeMake@Gen_004C14F0@@QAE?AUBfmeIterator@@XZ
BfmeIterator Gen_004C14F0::bfmeMake(void)
{
	return BfmeIterator(this, m_bfmeFirst);
}
