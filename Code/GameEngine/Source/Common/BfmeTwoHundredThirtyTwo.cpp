// A record written into the ring behind the last one, unless the ring is
// already full; the record keeps what the other one points at, what the caller
// brought, the other one itself, and the note taken after it has been told.

class BfmeOtherLP
{
public:
	virtual void bfmeDoLP(void) = 0;

	unsigned char m_bfmeGap[0x4c];		// 0x04
	void **m_bfmeSub;			// 0x50
};

struct BfmeRecLP
{
	int m_bfmeKind;				// 0x00
	int m_bfmeNote;				// 0x04
	void *m_bfmeFirst;			// 0x08
	void *m_bfmeSecond;			// 0x0c
	BfmeOtherLP *m_bfmeThird;		// 0x10
};

class BfmeThingLP
{
public:
	void bfmePushLP(void *what, BfmeOtherLP *other, int note);

private:
	BfmeRecLP *m_bfmeRing;			// 0x0000
	BfmeRecLP *m_bfmeHead;			// 0x0004
	BfmeRecLP *m_bfmeTail;			// 0x0008
	unsigned char m_bfmeGap[0x12a4];	// 0x000c
	int m_bfmeRoom;				// 0x12b0
};

void BfmeThingLP::bfmePushLP(void *what, BfmeOtherLP *other, int note)
{
	BfmeRecLP *next = m_bfmeTail + 1;

	if (next == m_bfmeRing + m_bfmeRoom)
		next = m_bfmeRing;

	if (next == m_bfmeHead)
		return;

	m_bfmeTail->m_bfmeKind = 0;

	m_bfmeTail->m_bfmeFirst = other->m_bfmeSub[10];

	m_bfmeTail->m_bfmeSecond = what;

	m_bfmeTail->m_bfmeThird = other;

	other->bfmeDoLP();

	m_bfmeTail->m_bfmeNote = note;

	m_bfmeTail = next;
}
