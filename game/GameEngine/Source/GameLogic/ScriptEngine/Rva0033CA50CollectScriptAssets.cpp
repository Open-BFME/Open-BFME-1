// cl: /DNDEBUG /MD /EHsc
// Retail 0x0033CA50 (200 bytes), a __thiscall with two pass-through arguments,
// called once from GameLogic::startNewGame.  It hands every script to the
// matched asset collector at 0x00351040: first the pooled script lists of each
// side in g_bfmeTableERJ (the side table BfmeConv1954.cpp reads), then the
// chains hanging off the receiver's pointer vector at +0x0C.  The receiver and
// the method are not proven, so both keep the address.

typedef int Int;

class Rva00351040Script
{
public:
	void collectAssets(void *assets, void *context);

private:
	char m_beforeActions[0x20];
	void *m_action;
	void *m_actionFalse;
};

// A pooled script's node value; the script sits after its leading word.
class Rva0033CA50PooledScript
{
public:
	Rva00351040Script *getScript() { return &m_script; }

private:
	void *m_head;
	Rva00351040Script m_script;
};

struct Rva0033CA50PoolNode
{
	Int m_next;
	unsigned char m_pad04[0x10 - 0x04];
	Rva0033CA50PooledScript *m_script;
};

struct Rva0033CA50ScriptPool
{
	unsigned char m_pad00[0x38];
	Rva0033CA50PoolNode *m_nodes;
	unsigned char m_pad3c[0x48 - 0x3c];
	Int m_head;
};

struct BfmeEntryERJ
{
	unsigned char m_bfmeHeadERJ[8];
	Rva0033CA50ScriptPool *m_bfmeValueERJ;
	unsigned char m_bfmeTailERJ[12];
};

class BfmeTableERJ
{
public:
	BfmeEntryERJ *bfmeAtERJ(int index)
	{
		if (index >= 0 && index < m_bfmeCountERJ)
			return m_bfmeEntriesERJ + index;
		return 0;
	}

	unsigned char m_bfmeHeadERJ[0x28];
	int m_bfmeCountERJ;
	BfmeEntryERJ m_bfmeEntriesERJ[1];
};

extern BfmeTableERJ *g_bfmeTableERJ;

struct Rva0033CA50Chain
{
	unsigned char m_pad00[0x14];
	Rva00351040Script *m_script;
	unsigned char m_pad18[0x28 - 0x18];
	Rva0033CA50Chain *m_next;
};

class Rva0033CA50Owner
{
public:
	void rva0033CA50(void *assets, void *context);

private:
	unsigned char m_pad00[0x0c];
	Rva0033CA50Chain **m_chainsBegin;
	Rva0033CA50Chain **m_chainsEnd;
};

// ?rva0033CA50@Rva0033CA50Owner@@QAEXPAX0@Z
void Rva0033CA50Owner::rva0033CA50(void *assets, void *context)
{
	for (Int i = 0; i < g_bfmeTableERJ->m_bfmeCountERJ; ++i)
	{
		Rva0033CA50ScriptPool *pool = g_bfmeTableERJ->bfmeAtERJ(i)->m_bfmeValueERJ;
		if (pool == 0)
			continue;

		for (Int index = pool->m_head; index != -1; index = pool->m_nodes[index].m_next)
		{
			Rva00351040Script *script = pool->m_nodes[index].m_script->getScript();
			if (script != 0)
				script->collectAssets(assets, context);
		}
	}

	for (Rva0033CA50Chain **it = m_chainsBegin; it != m_chainsEnd; ++it)
	{
		for (Rva0033CA50Chain *chain = *it; chain != 0; chain = chain->m_next)
		{
			if (chain->m_script != 0)
				chain->m_script->collectAssets(assets, context);
		}
	}
}
