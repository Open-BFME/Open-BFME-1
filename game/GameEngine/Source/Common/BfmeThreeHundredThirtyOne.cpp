struct BfmeNodeSC
{
	unsigned char m_bfmeHead[4];
	unsigned short m_bfmeTag;
};

struct BfmeKeySC
{
	BfmeNodeSC *m_bfmeNode;
};

struct BfmeSlotSC
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

class BfmeMapSC
{
public:
	BfmeSlotSC *m_bfmeFirst;
};

// The retail call at 0x00146290 targets the five-byte ILT thunk at 0x00040430,
// whose address-derived identity is ?j_00040430@@YAXXZ (functions.csv,
// game/gen_small/gthunks_071.cpp).  Naming it as itself is what lets this
// object link; the thiscall shape and the returned pointer are unchanged.
extern void j_00040430();

typedef BfmeSlotSC *(BfmeMapSC::*BfmeFindSC_t)(BfmeKeySC *);

class BfmeThingSC
{
public:
	void * bfmeLookSC(BfmeKeySC *key);
	unsigned char m_bfmeHead[0x334];
	BfmeMapSC m_bfmeMap;
};

void * BfmeThingSC::bfmeLookSC(BfmeKeySC *key)
{
	BfmeNodeSC *node = key->m_bfmeNode;
	if (node == 0)
		return 0;
	if (node->m_bfmeTag == 0)
		return 0;
	union { void (__cdecl *raw)(); BfmeFindSC_t member; } call;
	call.raw = j_00040430;
	BfmeSlotSC *at = (m_bfmeMap.*call.member)(key);
	if (at == m_bfmeMap.m_bfmeFirst)
		return 0;
	return at->m_bfmeWhat;
}
