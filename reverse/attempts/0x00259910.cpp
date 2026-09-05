// ?scan@Rva00259910Owner@@QAEXXZ
// partial score=0.1 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: address-derived attempt for the BFME PartitionFilter scan at
// retail 0x00259910 (440 B). This body stack-builds three PartitionFilter-
// shaped objects (vtables 0x01085DD0/0x010B243C/0x01083B80/0x0109688C are
// all shared with many other retail sites per tools/vtable_lookup.py, so
// they are the generic 3-slot PartitionFilter interface, not evidence of a
// specific subclass here), links them, and asks ThePartitionManager
// (0x012ED5B8) for a wide forward search via bfmeForwardWideC. No Zero Hour
// twin identified for the specific combination of filters. This is only a
// scaffold: the SEH frame, the exact filter field layouts, and the STL
// node-allocator cleanup tail (0x0082E5F0 / 0x00881EB0) are not faithfully
// reproduced -- see ledger notes for open questions.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
class Object;

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);		// ILT 0x009F2AE0
};

struct BfmeWideResult
{
	Int a, b, c, d, e;
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);	// 0x009F2960
};

extern BfmeWideForwardC *g_ThePartitionManager;		// ?ThePartitionManager@@3PAVPartitionManager@@A 0x012ED5B8

class BfmeHold1004
{
public:
	void *bfmeFind1004(void);				// ILT 0x0000D3B9
};

class AICommandInterface
{
public:
	void aiBfmeCommand45(Object *obj, Int commandSource);	// ILT 0x00019628
};

class BfmeK1094
{
public:
	void *bfmeCur1094(void);				// ILT 0x00020824
};

class Rva00259910Owner : public BfmeK1094, public BfmeHold1004
{
public:
	void scan(void);

	unsigned char m_bfmeGap[0x210];
	void *m_bfmeAiInterface;				// +0x204 style field used via a sub-object
};

void Rva00259910Owner::scan(void)
{
	bfmeCur1094();

	PartitionFilter filterA;
	PartitionFilter filterB;
	PartitionFilter filterC;

	filterA.link(&filterB);
	filterB.link(&filterC);

	g_ThePartitionManager->bfmeForwardWideC(0, 0, 0, 0, 2);

	void *found = bfmeFind1004();
	if (found)
	{
		AICommandInterface *ai = (AICommandInterface *)m_bfmeAiInterface;
		ai->aiBfmeCommand45((Object *)found, 2);
	}
}
