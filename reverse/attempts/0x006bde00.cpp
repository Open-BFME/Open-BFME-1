// ?update@Rva006BDE00@@QAEXH@Z
// partial score=0.15 date=2026-09-05
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?d_006bde00@@YAXXZ (Code/gen_asm/d_0069c4f0.asm), size 378.
//
// RVA-derived reconstruction, identity NOT proven. Structural notes for the
// next worker:
//   this (esi) is a member of some per-index owner: +0x08 holds a pointer to
//   an Object-shaped subobject whose vtable slot +0x28 returns a Drawable*
//   (call target 0x00021472 is the pinned ?getDrawModules@Drawable@@...).
//   +0x7c + index*4 is an array of node pointers (one per index, the arg is
//   an index into it) -- a per-cell "ghost/shroud" linked-node cache.
//   +0xfc is a container the two still-dumped helpers (0x000180a7 ctor-style,
//   0x00044341 update-style) both take by reference along with a `1` flag and
//   the current DrawModule-derived value (edi), obtained through vtable slot
//   +0xb8 of each entry in the Drawable's draw-module array.
//   +0x1c is the destination of a BfmeCopyElementA::bfmeAssign() copy whose
//   source is (*(Object* at +0x08)) + 0xac -- likely copying a small element
//   struct out of the owning Object before the final 12-byte struct copy at
//   the end (dest +0x0c/+0x18, source [obj+0x38..0x44]).
//   TheGhostObjectManager (0x012ef4fc) field +4 is compared against the
//   index argument as an early bounds/generation check; g_bfmeGlobPB
//   (0x012f8058) is used mid-loop through vtable slot +8 with the current
//   node's +4 field as the argument -- looks like a per-node release/notify.
//
// Not byte-matched: this is a compiling skeleton only, banked as partial.
// See docs/shape_levers.md before attempting the vtable-slot / SEH shape.

class BfmeXCQE
{
public:
	char bfmeKindCQE();
};

class Drawable
{
public:
	void **getDrawModules();
};

class BfmeCopyElementA
{
public:
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *other);
};

struct GhostObjectManager
{
	int m_pad0;
	int m_generation;
};

extern GhostObjectManager *TheGhostObjectManager;

struct BfmeGlobPBRec
{
	void *m_vtable;
};

extern BfmeGlobPBRec *g_bfmeGlobPB;

extern void j_000180a7(void);
extern void j_00044341(void);

union Rva006BDE00CtorCall
{
	void (*free_function)(void);
	void *(BfmeXCQE::*member_function)(void *value, void *container, int flag);
};

typedef void *(__stdcall *Rva006BDE00VFnGet)(void *);
typedef void (__stdcall *Rva006BDE00VFnArg)(void *, void *);

class Rva006BDE00
{
public:
	void update(int index);
};

void Rva006BDE00::update(int index)
{
	char *self = (char *)this;

	if (index != TheGhostObjectManager->m_generation)
		return;

	void *object = *(void **)(self + 0x08);
	void *objVtbl = *(void **)object;
	Drawable *drawable = (Drawable *)((Rva006BDE00VFnGet)(*(void **)((char *)objVtbl + 0x28)))(object);

	BfmeXCQE *kindOwner = (BfmeXCQE *)drawable;
	if (kindOwner->bfmeKindCQE())
		return;

	void *node = *(void **)(self + 0x7c + index * 4);
	void **dm = drawable->getDrawModules();
	void *previous = 0;

	if (dm != 0 && *dm != 0)
	{
		for (; *dm; ++dm)
		{
			void *module = *dm;
			void *modVtbl = *(void **)module;
			void *value = ((Rva006BDE00VFnGet)(*(void **)((char *)modVtbl + 0xb8)))(module);
			if (value == 0)
				continue;

			if (node == 0)
			{
				void *mem = ::operator new(0xc);
				void *result = 0;
				if (mem != 0)
				{
					Rva006BDE00CtorCall call;
					call.free_function = &j_000180a7;
					result = (((BfmeXCQE *)mem)->*call.member_function)(value, self + 0xfc, 1);
				}

				if (previous == 0)
					node = result;
				else
					*(void **)((char *)previous + 8) = result;
			}
			else
			{
				Rva006BDE00CtorCall call;
				call.free_function = &j_00044341;
				(((BfmeXCQE *)node)->*call.member_function)(value, self + 0xfc, 1);

				if (index == TheGhostObjectManager->m_generation)
				{
					void *nodeVtbl = *(void **)node;
					((Rva006BDE00VFnArg)(*(void **)((char *)nodeVtbl + 0x40)))(node, 0);

					objVtbl = *(void **)object;
					if (((Rva006BDE00VFnGet)(*(void **)((char *)objVtbl + 0x3c)))(object))
					{
						void *arg = *(void **)((char *)node + 4);
						((Rva006BDE00VFnArg)(*(void **)((char *)g_bfmeGlobPB->m_vtable + 8)))(g_bfmeGlobPB, arg);
					}
				}
			}

			previous = node;
			node = *(void **)((char *)node + 8);
		}
	}

	*(void **)(self + 0x7c + index * 4) = node;

	BfmeCopyElementA *dst = (BfmeCopyElementA *)(self + 0x1c);
	BfmeCopyElementA *src = (BfmeCopyElementA *)((char *)object + 0xac);
	dst->bfmeAssign(src);
}
