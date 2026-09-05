// ?bfmeGetOrCreateDefault@Rva008A7270Owner@@QAEPAXHPAPAX@Z
// partial score=0.45 date=2026-09-05
// cl: /EHsc
// Open-BFME5 conversion from Code/gen_asm/d_008592e0.asm.
//
// Two lazily constructed per-type default singletons, gated on a fixed-size
// byte compare of a name buffer (offset 8 of *arg2) against two constant
// templates. Each singleton is a BfmeA1029-shaped object (BfmeConv1029.cpp)
// allocated through the shared indirect allocator at 0x01337828 and pushed
// onto g_bfmeHeadDX (bfmePush, Bfme5FiftyFour.cpp), built with the shared
// bfmeBase1029(int,int) helper and BfmeA1029's own vtable, then flagged
// registered and given a one-time notify through its own vtable slot 0
// (bfmeBump, Bfme5FiftyFour.cpp).
//
// IDENTITY IS NOT RECOVERED: the owning class, the real parameter types and
// the meaning of the two 12/15-byte name templates are unknown; only the
// byte shape is proven. Names are address-derived.

extern "C" void *(*WideAllocPtr)(unsigned int bytes);

class BfmeItemDX;
extern void __cdecl bfmePush(BfmeItemDX *item);

extern "C" void *bfmeVft1029A[];

class BfmeA1029
{
public:
	void bfmeBase1029(int n, int m);

	void *m_bfmeVfptr;
	char m_bfmePad[0x1c];
	int m_bfmeVal;
};

class Rva008991B0Flags
{
public:
	int m_bfmeHead;
	unsigned int m_bfmeBits;
};

class Rva008A7270VBase
{
public:
	virtual void bfmeNotify();
};

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
#pragma intrinsic(memcmp)

extern const char g_rva01136588[12];
extern const char g_rva01136560[15];

extern BfmeA1029 *g_rva01337a9c;
extern BfmeA1029 *g_rva01337aa0;

class Rva008A7270Owner
{
public:
	void *bfmeGetOrCreateDefault(int unused, void **arg2);
};

void *Rva008A7270Owner::bfmeGetOrCreateDefault(int unused, void **arg2)
{
	if (memcmp((const char *)*arg2 + 8, g_rva01136588, 12) == 0)
	{
		BfmeA1029 *obj = g_rva01337a9c;

		if (obj == 0)
		{
			obj = (BfmeA1029 *)((char *)WideAllocPtr(0x24 + 8) + 8);

			bfmePush((BfmeItemDX *)obj);

			if (obj != 0)
			{
				obj->bfmeBase1029(9, 8);
				obj->m_bfmeVfptr = bfmeVft1029A;
				obj->m_bfmeVal = 0xca5440;
			}

			g_rva01337a9c = obj;

			Rva008991B0Flags *flags = (Rva008991B0Flags *)obj;
			flags->m_bfmeBits = (flags->m_bfmeBits & 0xffffc07f) | 0x40;

			((Rva008A7270VBase *)obj)->bfmeNotify();

			obj = g_rva01337a9c;
		}

		return obj;
	}

	if (memcmp((const char *)*arg2 + 8, g_rva01136560, 15) == 0)
	{
		BfmeA1029 *obj = g_rva01337aa0;

		if (obj == 0)
		{
			obj = (BfmeA1029 *)((char *)WideAllocPtr(0x24 + 8) + 8);

			bfmePush((BfmeItemDX *)obj);

			if (obj != 0)
			{
				obj->bfmeBase1029(9, 8);
				obj->m_bfmeVfptr = bfmeVft1029A;
				obj->m_bfmeVal = 0xca5490;
			}

			g_rva01337aa0 = obj;

			Rva008991B0Flags *flags = (Rva008991B0Flags *)obj;
			flags->m_bfmeBits = (flags->m_bfmeBits & 0xffffc07f) | 0x40;

			((Rva008A7270VBase *)obj)->bfmeNotify();

			obj = g_rva01337aa0;
		}

		return obj;
	}

	return 0;
}
