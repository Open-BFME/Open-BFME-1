// ?appendInternalEventName@Rva002E9590Host@@QAEXPAVXmlNameSlotList@@@Z
// partial score=0.28 date=2026-09-21
// cl: /DNDEBUG /MD /O2 /Ob0
// Open-BFME5: retail 0x002E9590 (186B).
// Sibling of Rva002E2970ApplyNameFlags.cpp: same XmlNameSlotList accessor
// class (count/tagAt/nameAt/finish, pins from that landing) and the same
// "this" object (the vector field at +0x7c sits inside that class's own
// m_pad78 padding, 0x78-0xB8). Reached from the still-carved dispatcher at
// 0x002EA5D0 (stash reverse/attempts/0x002ea5d0.cpp) for the InternalEvent
// tag. For each attribute whose tag is "Name", converts the attribute value
// through BfmeThingVKT::bfmeBaseVKT (pinned, a local zero-init) and
// BfmeThingBLC::bfmeGoBLC (matched, BfmeConv484.cpp) and appends the
// resulting pointer to a BfmeVector28-shaped growable array (same
// double-checked push_back idiom as the landed BfmeVector28::push_back in
// BfmeConv826.cpp), falling back to the vector<Gen_t_002e8eb0_m4pod>-style
// overflow helper pinned at 0x002E7940 through its ILT thunk.
//
// PARTIAL: identity chain (accessors, memcmp("Name",5), the BfmeVector28
// push_back double-check idiom, the VKT/BLC conversion pair) all reproduce
// retail's instruction stream faithfully, but retail's prologue is a bare
// 3-register push frame (push ecx/ebx/ebp, no `sub esp`) that reuses the
// now-dead incoming "xml" stack argument slot as scratch for the two local
// "thing" temporaries and the insertHelper out-param, keeping `this` off
// any callee-saved register. Every shape tried (separate locals, a shared
// `scratch` local, a `self` alias for `this`, /Ob1, /O1) still made the
// compiler emit `sub esp, N` and route `this` through ebx, which shifts
// every later instruction. Best score with this identity: 52/186 matching
// non-reloc bytes (0.28), from this exact source.

#include <string.h>

class XmlNameSlotList
{
public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	void finish();
};

class BfmeThingVKT
{
public:
	void bfmeBaseVKT();
};

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
	void *m_bfmeGot;
};

// address-derived view of the same object Rva002E2970Host describes; only
// the growable-array field this body actually touches is modeled.
class Rva002E9590Host
{
	char m_pad7c[0x7c];
	void **m_start;
	void **m_cur;
	void **m_end;

	void insertHelper(void **pos, void * const *src, void *temp, int one1, int one2);

public:
	void appendInternalEventName(XmlNameSlotList *xml);
};

#pragma comment(linker, "/alternatename:?insertHelper@Rva002E9590Host@@AAEXPAPAXPBQAX0HH@Z=?j_00017c38@@YAXXZ")

void Rva002E9590Host::appendInternalEventName(XmlNameSlotList *xml)
{
	int i = 0;
	if (xml->count() > 0)
	{
		do
		{
			int diff = memcmp(xml->tagAt(i), "Name", 5);
			if (diff == 0)
			{
				const char *value = xml->nameAt(i);

				{
					BfmeThingVKT vkt;
					vkt.bfmeBaseVKT();
				}

				BfmeThingBLC blc;
				blc.bfmeGoBLC((void *)value);

				if (m_cur != m_end)
				{
					if (m_cur)
						*m_cur = blc.m_bfmeGot;
					m_cur++;
				}
				else
				{
					void *temp;
					insertHelper(m_cur, &blc.m_bfmeGot, &temp, 1, 1);
				}
			}
			++i;
		} while (i < xml->count());
	}
	xml->finish();
}
