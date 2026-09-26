// Address-derived identity: the callers establish a string-to-key lookup followed
// by a map search, but do not establish the retail owner or value type.
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

extern char g_bfmeEmptyERA[];

struct BfmeStrDataERA
{
	int m_bfmeRefERA;
	int m_bfmeLenERA;
	char m_bfmeTextERA[1];
};

class BfmeStrERA
{
public:
	const char *bfmeTextERA() const
	{
		return m_bfmeDataERA ? m_bfmeDataERA->m_bfmeTextERA : g_bfmeEmptyERA;
	}

	BfmeStrDataERA *m_bfmeDataERA;
};

class BfmeKeyGenERA
{
public:
	int bfmeNameToKeyERA(const char *name);
};

extern BfmeKeyGenERA *g_bfmeKeyGenERA;

class BfmeNodeERA
{
public:
	unsigned char m_bfmeHeadERA[0x14];
	void *m_bfmeValueERA;
};

class BfmeMapERA
{
public:
	void bfmeFindERA(BfmeNodeERA **out, int *key);

	BfmeNodeERA *m_bfmeEndERA;
};

class BfmeOwnerERA
{
public:
	unsigned char m_bfmeHeadERA[8];
	BfmeMapERA m_bfmeMapERA;
};

extern BfmeOwnerERA *g_bfmeOwnerERA;

void * __stdcall Rva001B70E0Lookup(BfmeStrERA *name)
{
	int key = g_bfmeKeyGenERA->bfmeNameToKeyERA(name->bfmeTextERA());

	if (key == 0)
	{
		// Preserve retail's inline zero-return block; the later zero return
		// cross-jumps back to it without emitting an instruction here.
		_WriteBarrier();
		return 0;
	}

	BfmeMapERA *map = &g_bfmeOwnerERA->m_bfmeMapERA;
	BfmeNodeERA *node;
	map->bfmeFindERA(&node, &key);

	if (node == map->m_bfmeEndERA)
		return 0;

	return node->m_bfmeValueERA;
}
