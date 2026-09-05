// ?method@BfmeRva7626F0@@QAEXXZ
// partial score=0.25 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived body, retail 0x007626F0, 363 bytes. Neighbours
// (0x00762500 W3DModelDraw::updateSubObjectsFromShroud, 0x00762640 setHidden,
// 0x007628C0 setFullyObscuredByShroud) and the sibling body at 0x00764290
// (esi+0x28 == RenderObjClass* m_renderObject there) place this in the same
// W3DDevice GameClient Drawable family; m_renderObject sits at +0x34 in THIS
// body's own "this", 0xC further in than the +0x28 seen at 0x00764290 -- an
// adjustor-thunk-reached interface method of the same owning object. Identity
// of the owning class/method could not be proven within budget; landed under
// an address-derived name per IDENTITY POLICY. Callees: ?ask@BfmeSubBIA@@QAEHXZ
// (pinned, still a dump), ?j_0002dca4@@YAXXZ (gen-thunk, thunks_021.cpp),
// ?bfmeForward@Gen_0043A570Target@@QAEXPAX@Z (pinned, still a dump).

class BfmeSubBIA
{
public:
	void *m_vtable;
	BfmeSubBIA *m_nextOverride;
	int ask();
};

class BfmeRva7626F0Target
{
public:
	void bfmeForward(void *a);
};

#define TEN_SLOTS(P) \
	virtual void *P##0(); virtual void *P##1(); virtual void *P##2(); \
	virtual void *P##3(); virtual void *P##4(); virtual void *P##5(); \
	virtual void *P##6(); virtual void *P##7(); virtual void *P##8(); \
	virtual void *P##9()

class BfmeRva7626F0RenderObj
{
public:
	TEN_SLOTS(a); TEN_SLOTS(b); TEN_SLOTS(c); TEN_SLOTS(d);
	TEN_SLOTS(e); TEN_SLOTS(f); TEN_SLOTS(g); TEN_SLOTS(h);
	TEN_SLOTS(i);
	virtual void *s90(); virtual void *s91(); virtual void *s92();
	virtual void *s93(); virtual void *s94(); virtual void *s95();
	virtual void *s96(); virtual void *s97(); virtual void *s98();
	virtual int slot99();
};

#undef TEN_SLOTS

class BfmeRva7626F0Cache
{
public:
	char m_pad0[4];
	unsigned char m_f4;
	unsigned char m_f5;
	char m_pad1[0x30 - 6];
	unsigned char m_f30;
};

class BfmeRva7626F0Info
{
public:
	char m_pad0[0x4c];
	int m_f4c;
	char m_pad1[0x3c8 - 0x50];
	int m_f3c8;
	int m_f3cc;
	int m_f3d0;
	int m_f3d4;
	char m_pad2[0x3e0 - 0x3d8];
	int m_f3e0;
	int m_f3e4;
	char m_pad3[0x482 - 0x3e8];
	unsigned short m_f482;
	char m_pad4[0x48d - 0x484];
	unsigned char m_f48d;
	unsigned char m_f48e;
	unsigned char m_f48f;
};

extern const char g_bfmeEmptyAscii[];

class BfmeRva7626F0
{
public:
	void method();

	char m_pad0[8];
	BfmeSubBIA *m_head;                 // +0x08
	char m_pad1[0x24 - 0xc];
	void *m_arg24;                      // +0x24
	char m_pad2[0x2d - 0x28];
	unsigned char m_flag2d;             // +0x2d
	unsigned char m_flag2e;             // +0x2e
	char m_pad3[0x34 - 0x2f];
	BfmeRva7626F0RenderObj *m_renderObject; // +0x34
	char m_pad4[0x3c - 0x38];
	BfmeRva7626F0Cache *m_cache;        // +0x3c
};

extern "C" char *__cdecl strcpy(char *dest, const char *src);

class BfmeGlobQE7626F0
{
public:
	void *build(void *localBuf, void *renderObj);
};
typedef void *(BfmeGlobQE7626F0::*BfmeRva7626F0BuildFn)(void *, void *);
extern void j_0002dca4(void);
extern BfmeGlobQE7626F0 *g_bfmeGlobQE;

// ?d_007626f0@@YAXXZ
void BfmeRva7626F0::method()
{
	BfmeSubBIA *nodeA = m_head->m_nextOverride;
	BfmeSubBIA *result;
	if (nodeA)
	{
		BfmeSubBIA *nodeB = nodeA->m_nextOverride;
		if (nodeB)
			result = (BfmeSubBIA *)(void *)(unsigned int)nodeB->ask();
		else
			result = nodeA;
	}
	else
	{
		result = 0;
	}
	BfmeRva7626F0Info *info = (BfmeRva7626F0Info *)result;

	if (m_cache != 0)
		return;
	if (m_renderObject == 0)
		return;
	if (g_bfmeGlobQE == 0)
		return;
	if (info->m_f482 == 0)
		return;

	char localBuf[0x98];
	const char *name = info->m_f4c ? (const char *)((char *)(unsigned int)info->m_f4c + 8) : g_bfmeEmptyAscii;
	strcpy(localBuf, name);

	union { void *asVoid; BfmeRva7626F0BuildFn asMember; } build;
	build.asVoid = (void *)j_0002dca4;
	void *cache = (g_bfmeGlobQE->*build.asMember)(localBuf, m_renderObject);
	m_cache = (BfmeRva7626F0Cache *)cache;
	if (!cache)
		return;

	m_cache->m_f30 = info->m_f48f;
	if (info->m_f48e)
	{
		((BfmeRva7626F0Target *)m_cache)->bfmeForward(m_arg24);
	}
	m_cache->m_f5 = m_flag2d;

	int r = m_renderObject->slot99();
	if (r != 0 || !m_flag2e)
		m_cache->m_f4 = 0;
}
