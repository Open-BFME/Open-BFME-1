// ??0GiantBirdAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9402 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc

// BANKED CANDIDATE for retail 0x002C2430 (418 B), GiantBirdAIUpdate's public
// module constructor.  393 of 418 bytes match and every relocation site lands
// on a retail operand; the only residue is the scratch-rotation phase of the
// five-global mask chain, 25 bytes from +0xEB to +0x134.
//
//   tools/probe.py <this file> "??0GiantBirdAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z" 0x002C2430
//     size ours=418 retail=418  relocs=13  diffs 25 non-reloc, first at +236
//
// Retail keeps the shared mask in EAX and uses ECX as the accumulator of all
// three |= chains, with the [0x12F02D4] store sunk between the [0x12F02DC]
// load and its ORs, and the [0x12F02E4] load hoisted between the [0x12F02E0]
// chain's first OR and its immediate OR.  This build keeps the mask in EAX but
// gives the first accumulator EDX, so all three chains shift one place along.
//
// MEASURED, do not repeat:
//  * store order 1-2-4-3-5 or 1-2-3-4-5 (30 / 39 diffs) - the scheduler keeps
//    source order, so no permutation reproduces retail's mid-chain store.
//  * re-reading g_Rva012F02D4 in the three chains (429 B): MSVC 7.1 does not
//    CSE a load across the intervening stores, so the shared value MUST be a
//    local.  Confirmed twice, with `|=` and with `=`.
//  * struct spelling (g_rec->m_00) , a comma operator , a shared `acc`
//    variable , a folded copy local , and identity-inline rot() on the mask:
//    all normalise to the identical shape (25 diffs, probe shape 75efa622).
//  * shape_family_levers (register,store,copy,constant) only offers adjacent
//    store swaps, which break the store order that already matches.
//  * rotation_sweep.py declines the file ("special members and templates").
//    Hand-running its H2 toggle (copy vs direct push) on the base-ctor
//    arguments changes nothing, because both are already register parameters.
//
// THE PHASE IS SET BY THE BASE CALL, and that is the useful lead.  Reduced
// repros in build/gbchain*.cpp (kept untracked): with the two-argument
// AIUpdateInterface(thing, moduleData) call the chain's first accumulator is
// always EDX; delete the second argument (one push) and it becomes ECX, which
// is retail.  It is not the vtable stores (a non-virtual base still gives
// EDX) and not any of the three subobject constructors (dropping BfmeThingIC,
// the list root or DeployStyleAIUpdateMember one at a time still gives EDX).
// So the lever is a spelling of that two-argument call that emits the same
// `mov eax,[esp+0x18] / mov ecx,[esp+0x1c] / push eax / push ecx` but
// consumes ONE FEWER scratch temporary.  rot(), const-qualified parameters,
// void* parameters and a templated base constructor were all tried and all
// keep EDX; void* changes the mangled name and is not available anyway.
//
// Open-BFME5: GiantBirdAIUpdate module ctor.
//
// The base chain is AIUpdateInterface (ILT 0x000292A3 -> the matched 0x0027F4B0
// body), whose four secondary interface bases carry the vtbls retail stores at
// +0xc/+0x10/+0x20/+0x24 beside the class vtbl at +0; the chain ends at +0x340.
//
// Three subobjects have constructors, so the ctor carries an SEH frame with the
// three states retail's unwind map has (tools/eh_info.py 0x002C2430): state 0
// destroys the base through ??1AIUpdateInterface@@UAE@XZ (0x0027EF60), state 1
// the DeployStyleAIUpdateMember object at +0x34c (ctor ILT 0x0001A9B0, dtor
// 0x0027AF40), state 2 the list root at +0x3ec (ctor allocates 12 bytes from
// STLport's node pool, dtor 0x000E6010).  The BfmeThingIC member at +0x400
// (ctor ILT 0x00012300) is the last initialiser, so it adds no state.
//
// The zero stores that follow are in retail's order, which is neither
// declaration nor address order, and the five-global bit chain at 0x012F02D4
// sits between two of them, so both are written as body statements.

class Thing;
class ModuleData;
class Object;

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

// Base chain; the names are the ones the matched GiantBirdAIUpdate destructor
// already uses, so the five vftable symbols resolve to the recorded addresses.
class GiantBirdRoot
{
public:
	virtual ~GiantBirdRoot();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class GiantBirdIface1
{
public:
	virtual void giantBirdIface1();
};

class GiantBirdIface2
{
public:
	virtual void giantBirdIface2();
};

class GiantBirdIface3
{
public:
	virtual void giantBirdIface3();
};

class GiantBirdIface4
{
public:
	virtual void giantBirdIface4();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class GiantBirdUpdateBase : public GiantBirdRoot,
	public GiantBirdIface1,
	public GiantBirdIface2
{
public:
	unsigned char m_state14[0x0c];				///< retail this+0x14 .. +0x20
};

// The base the ctor calls: the ledger owns its constructor (0x0027F4B0) and its
// virtual destructor (0x0027EF60, retail's state 0 cleanup).
class AIUpdateInterface : public GiantBirdUpdateBase,
	public GiantBirdIface3,
	public GiantBirdIface4
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual ~AIUpdateInterface();
};

// The +0x34c object; its constructor is the matched 0x0027AE50 body.
class DeployStyleAIUpdateMember
{
public:
	DeployStyleAIUpdateMember();				///< ILT 0x0001A9B0
	~DeployStyleAIUpdateMember();

	unsigned char m_unreconstructed_00[0xA0];	///< retail this+0x34c .. +0x3EC
};

// The node retail allocates for +0x3ec: two self-linked links and a word it
// never touches here.
class Rva002C2476ListNode
{
public:
	Rva002C2476ListNode *m_next;
	Rva002C2476ListNode *m_prev;
	unsigned int m_unreconstructed_08;
};

// Owns the allocated list root; its constructor is inlined into the ctor below.
class Rva002C2476ListRoot
{
public:
	Rva002C2476ListRoot()
	{
		m_root = 0;
		Rva002C2476ListNode *root =
			(Rva002C2476ListNode *)_STL::__new_alloc::allocate(0x0C);
		root->m_next = root;
		root->m_prev = root;
		m_root = root;
	}
	~Rva002C2476ListRoot();

	Rva002C2476ListNode *m_root;				///< retail this+0x3EC
};

// The +0x400 member; its constructor is the matched 0x003A3370 body.
class BfmeThingIC
{
public:
	BfmeThingIC();								///< ILT 0x00012300
	~BfmeThingIC();

	void *m_bfmeVftIC;
	unsigned char m_unreconstructed_04[0x5C];	///< retail this+0x404 .. +0x460
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	unsigned int m_340;
	unsigned int m_344;
	unsigned int m_348;
	DeployStyleAIUpdateMember m_34c;			///< retail this+0x34c
	Rva002C2476ListRoot m_3ec;					///< retail this+0x3ec
	unsigned int m_3f0;
	unsigned int m_3f4;
	unsigned int m_3f8;
	unsigned int m_3fc;
	BfmeThingIC m_400;							///< retail this+0x400
	unsigned int m_460;
	unsigned int m_464;
	unsigned int m_468;
	bool m_46c;
	unsigned int m_470;
	unsigned int m_474;
	unsigned int m_478;
	unsigned int m_47c;
	unsigned int m_480;
	unsigned int m_484;
	bool m_488;
	unsigned int m_48c;
	bool m_490;
	unsigned int m_494;
	unsigned int m_498;
	unsigned int m_49c;
	unsigned int m_4a0;
	unsigned int m_4a4;
	unsigned int m_4a8;
	unsigned int m_4ac;
	bool m_4b0;
};

// Six dwords at 0x012F02D4; retail mutates five of them here and folds the
// first into the next three, so the OR result stays in a register across the
// chain.  One view of the record is what lets the compiler keep it there.
#define g_mask(index) (*(unsigned int *)(0x012F02D4 + 4 * (index)))
#define g_Rva012F02D4 g_mask(0)
#define g_Rva012F02D8 g_mask(1)
#define g_Rva012F02DC g_mask(2)
#define g_Rva012F02E0 g_mask(3)
#define g_Rva012F02E4 g_mask(4)

struct Rva012F02D4Mask
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
};

#define g_rec ((Rva012F02D4Mask *)0x012F02D4)

// ??0GiantBirdAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
GiantBirdAIUpdate::GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData), m_3fc(0)
{
	m_3f0 = 0;
	m_460 = 0;
	m_464 = 0;
	m_468 = 0;
	m_3f4 = 0;
	m_46c = false;
	m_470 = 0;
	m_474 = 0;
	m_478 = 0;
	m_47c = 0;
	m_480 = 0;
	m_484 = 0;
	m_488 = false;

	unsigned int bits = g_Rva012F02D4 | 0x28;
	g_Rva012F02D8 |= bits | 0x04;
	g_Rva012F02D4 = bits;
	g_Rva012F02DC |= bits | 0x02;
	g_Rva012F02E0 |= bits | 0x06;
	g_Rva012F02E4 |= 0x88;

	m_48c = 0;
	m_490 = false;
	m_494 = 2;
	m_340 = 0;
	m_344 = 0;
	m_348 = 0;
	m_3f8 = 0;
	m_498 = 0;
	m_49c = 0;
	m_4a0 = 0;
	m_4a4 = 0;
	m_4a8 = 0;
	m_4ac = 0;
	m_4b0 = false;
}
