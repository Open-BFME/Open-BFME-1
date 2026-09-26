// ?bfmeAddERB@BfmeVecERB@@QAEXPAVBfmeOwnerERB@@@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 119/119 EXACT SIZE, ONE swapped instruction pair. Vector push_back of a
// freshly allocated 12-byte node keyed by nameToKey("(NULL)").
//   retail: mov eax,[ebx+4] / mov [esi],eax / add esp,4 / mov [esi+4],ebx
//   MSVC:   mov eax,[ebx+4] / add esp,4 / mov [esi],eax / mov [esi+4],ebx
// The add esp,4 is the cdecl cleanup for operator new; MSVC always drops it
// after the second instruction of the group. Swapping the two field
// assignments moves the pair but not the cleanup (store[esi+4] / load /
// add esp,4 / store[esi]). Flags do nothing: /G7 /GB /G6 /G5 /Ot /Ob1 all
// give the identical 119-byte body.
//
// Three things were needed to get here and are worth reusing:
//  * the node must be a POD assigned field-by-field -- a real constructor
//    makes MSVC null-check the allocation (148 bytes);
//  * the grow call's out-parameters must be locals declared INSIDE the else,
//    not &node/&owner -- taking the address of the long-lived pointers makes
//    MSVC spill and reload everything (128-148 bytes);
//  * the third out-parameter is an UNINITIALISED local: retail has no store
//    for it because it lands in the dead parameter home slot. Copying owner
//    into it costs exactly the 4 bytes of the difference (123 bytes).
//  * the value local must be declared before the nameToKey call so its spill
//    is scheduled into the call setup, as retail does.
class BfmeKeyGenERB
{
public:
	int bfmeNameToKeyERB(const char *name);
};

extern BfmeKeyGenERB *g_bfmeKeyGenERB;

class BfmeOwnerERB
{
public:
	unsigned char m_bfmeHeadERB[4];
	void *m_bfmeSourceERB;
	unsigned char m_bfmeMidERB[0x274];
	void *m_bfmeSlotERB;
};

class BfmeNodeERB
{
public:
	void *m_bfmeSourceERB;
	BfmeOwnerERB *m_bfmeOwnerERB;
	int m_bfmeKeyERB;
};

class BfmeVecERB
{
public:
	void bfmeAddERB(BfmeOwnerERB *owner);
	void bfmeGrowERB(BfmeNodeERB **where, BfmeNodeERB **value,
		BfmeOwnerERB **spare, int one, int two);

	BfmeNodeERB **m_bfmeFirstERB;
	BfmeNodeERB **m_bfmeLastERB;
	BfmeNodeERB **m_bfmeEndERB;
};

void BfmeVecERB::bfmeAddERB(BfmeOwnerERB *owner)
{
	BfmeNodeERB *node = new BfmeNodeERB;

	node->m_bfmeSourceERB = owner->m_bfmeSourceERB;
	node->m_bfmeOwnerERB = owner;

	BfmeNodeERB *value = node;

	node->m_bfmeKeyERB = g_bfmeKeyGenERB->bfmeNameToKeyERB("(NULL)");

	if (m_bfmeLastERB != m_bfmeEndERB)
	{
		if (m_bfmeLastERB != 0)
			*m_bfmeLastERB = node;

		m_bfmeLastERB = m_bfmeLastERB + 1;
	}
	else
	{
		BfmeOwnerERB *spare;

		bfmeGrowERB(m_bfmeLastERB, &value, &spare, 1, 1);
	}

	owner->m_bfmeSlotERB = node;
}
