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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
enum NameKeyType { };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *g_bfmeKeyGenERA;

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
	// The map shim keys on int; the value is the same 32-bit NameKeyType.
	int key = (int)g_bfmeKeyGenERA->nameToKey(name->bfmeTextERA());

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
