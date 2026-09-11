// ?d_00494ec0@@YAXXZ
// partial score=0.94 date=2026-09-10
// 62/62 bytes. Every instruction, register, stack offset and relocation
// matches retail except one adjacent transposition at +0x27: retail emits
// `mov ecx,offset g_bfmeMapLB` and then `mov dword ptr [eax+8],0`, this body
// emits them the other way round.
//
// What made the size exact, replacing the earlier volatile-self-store bank:
// the key is a plain local initialised from the parameter and re-assigned
// before the erase, and MSVC 7.1 parks that local in the DEAD parameter home
// slot at [esp+8], which is where retail's `lea` and both `mov [esp+0ch],esi`
// stores point. No volatile is needed and the parameter is never reloaded.
//
// Ruled out for the remaining transposition, all leaving the identical
// 8-byte diff (probe experiment history has each one):
//   * all six source orders of the three block statements; the and/count pair
//     is canonicalised by the compiler, so only the key store moves;
//   * comma-operator and nested-block groupings of the count and key stores,
//     and both stores moved into the erase argument expression
//     (`&(key = p)`, `(key = p, &key)`);
//   * a __forceinline helper performing both stores as one call;
//   * the map as a pointer local, as a reference, and defined mid-block;
//     declaring erase before find; an early `return` instead of the if-block;
//   * field retyping of the +8 slot (int, void *, float) and volatile on
//     either field;
//   * `// cl:` sweeps: /G5 /G6 /G7 /GB /Os /Ot /O1 /Oxs /Od, all identical;
//   * `#pragma optimize` a/w/t/y on and g/s/y off; "s" on gives a different
//     59-byte shape, "g" off gives 90;
//   * _ReadWriteBarrier / _WriteBarrier / _ReadBarrier at each of the three
//     statement boundaries; every placement that moved anything moved it away
//     from retail.
//
// Also ruled out (2026-09-11, identical 8-byte diff both times):
//   * pre-materializing the erase argument into its own pointer local
//     (`void **pkey = &key;` taken before the count store, key=p written
//     after, `bfmeEraseLB(pkey)`) -- the this-load still lands after the
//     count store;
//   * spelling the count store as a raw pointer cast
//     (`*(int *)((char *)entry + 8) = 0;`) instead of the field access --
//     identical codegen.
//
// The measured rule behind all of it: MSVC 7.1 inserts the thiscall `mov ecx`
// immediately before the LAST pending statement of the block. With no pending
// statement (the find call site) it lands right after the argument push, which
// is why that call site matches. Retail's erase site has the ecx load ahead of
// BOTH the count store and the key spill, which no source order reproduces
// while the key store is a source statement. Dropping the key assignment does
// put the ecx load ahead of the count store, so the lever is a form in which
// the key spill is the compiler's own escape spill rather than a statement --
// but every such form measured here also drops esi and moves the slot.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class BfmeEntryLB
{
public:
	unsigned char m_bfmeHeadLB[8];
	int m_bfmeCountLB;
	unsigned char m_bfmeGapLB[0x14];
	unsigned char m_bfmeFlagsLB;
};

class BfmeMapLB
{
public:
	BfmeEntryLB **bfmeFindLB(void **key);
	void bfmeEraseLB(void **key);
};

extern BfmeMapLB g_bfmeMapLB;

void __cdecl Rva00494EC0(void *p)
{
	void *key = p;

	BfmeEntryLB *entry = *g_bfmeMapLB.bfmeFindLB(&key);

	if (entry != 0)
	{
		entry->m_bfmeFlagsLB &= 0xfc;
		entry->m_bfmeCountLB = 0;

		key = p;

		g_bfmeMapLB.bfmeEraseLB(&key);
	}
}
