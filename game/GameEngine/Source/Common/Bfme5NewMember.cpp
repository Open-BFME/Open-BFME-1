// A constructor whose only job is to build the object it points at.
//
// The unwind frame belongs to the new expression: the raw block is kept in a
// stack slot so that it can be given back if the constructor throws, and the
// state word is set before the construction rather than after. The failure
// path is the allocator returning nothing, with the null propagated into the
// store.

extern void * (*WideAllocPtr)(unsigned int bytes);

class BfmeThingBE
{
public:
	void *operator new(unsigned int bytes)
	{
		return WideAllocPtr(bytes);
	}

	void operator delete(void *block);

	BfmeThingBE(void);					// retail 0x008BE3B0

	int m_bfmeField;					// +0x00
};

class Gen_008BE660
{
public:
	Gen_008BE660(void);

private:
	BfmeThingBE *m_bfmeThing;				// +0x00
};

// ??0Gen_008BE660@@QAE@XZ
Gen_008BE660::Gen_008BE660(void)
{
	m_bfmeThing = new BfmeThingBE();
}

extern char *g_bfmeArenaStart;					// retail 0x013378D0
extern char *g_bfmeArenaCursor;					// retail 0x013378D4
extern char *g_bfmeArenaEnd;					// retail 0x013378D8

void __cdecl bfmeArenaReady(void);				// retail 0x00897050

// ?bfmeArenaInit@@YAXI@Z
void __cdecl bfmeArenaInit(unsigned int size)
{
	char *block = (char *)WideAllocPtr(0x4000);

	g_bfmeArenaStart = block;
	g_bfmeArenaCursor = block;
	g_bfmeArenaEnd = block + size;

	bfmeArenaReady();
}
