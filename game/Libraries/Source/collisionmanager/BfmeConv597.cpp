// The node and sub-object types below are address-derived: retail ties no
// string, vtable slot or BFME helper to them, so every field keeps an offset
// token. Only the two list links (node +0x2C back slot, node +0x30 next) carry
// a role name, and those are the intrusive-hash-chain idiom already landed in
// game/GameEngine/Source/Common/System/Rva009A3770HashChainInsert.cpp and
// game/GameEngine/Source/Common/SmallGaps/Rva009A2BE0HashIterNext.cpp.
struct Rva009A2FE0Node;

struct Rva009A2FE0Sub
{
	unsigned char m_pad0[4];
	unsigned m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
};

struct Rva009A2FE0Node
{
	Rva009A2FE0Sub *m_bfme00;
	Rva009A2FE0Sub *m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
	unsigned char m_pad14[0x18];
	Rva009A2FE0Node **m_backSlot;
	Rva009A2FE0Node *m_next;
};

class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0xae10 - 4];
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

// Walk the 0x493-slot table at this+0xAE10 from the cursor at this+0xC064 and
// move every node whose two sub-objects are both flagged at sub+0x04 out of its
// bucket chain and onto the second list at this+0xC05C. Identity is proven by
// the matched caller bfmeGoCGD (0x009A4A30, call at +0x0F); see
// targets/game/reverse/identity_evidence/009a2fe0-bfmeOneCGD.md.
void BfmeThingCGD::bfmeOneCGD()
{
	Rva009A2FE0Node *nil = 0;
	Rva009A2FE0Node **curp = &m_cur;

	m_index = 0;
	m_cur = m_buckets[0];
	for (;;)
	{
		while (m_cur == nil)
		{
			int i = m_index + 1;

			if (i == 0x493)
				return;
			m_index = i;
			m_cur = m_buckets[i];
		}

		Rva009A2FE0Node *n = m_cur;

		m_cur = m_cur->m_next;
		if (n == nil)
			return;

		if (n->m_bfme00->m_bfme10 == 0 && n->m_bfme04->m_bfme10 == 0)
			continue;

		if (n->m_bfme00->m_bfme04 == 0 || n->m_bfme04->m_bfme04 == 0)
		{
			if (*curp == n)
				*curp = (*curp)->m_next;
			if (n->m_next != nil)
				n->m_next->m_backSlot = n->m_backSlot;
			*n->m_backSlot = n->m_next;
			n->m_backSlot = (Rva009A2FE0Node **)nil;
			n->m_next = m_active;
			m_active = n;
		}
		else
		{
			n->m_bfme10 = 0;
		}
	}
}

void BfmeThingCGD::bfmeGoCGD()
{
	if (m_bfmeFirst != 0)
	{
		m_bfmeBusy = true;
		bfmeOneCGD();
		bfmeGlobalCGD();
		bfmeTwoCGD();
		m_bfmeBusy = false;
	}
}
