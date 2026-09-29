// ?update006059F0@Node004092A0@@QAEXXZ
// partial score=0.7857 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006059F0, 903 bytes (ret at +0x386; the generated ledger row claims
// 896 and stops 7 bytes short of the epilogue). Sole caller:
// SpatialList004092A0::update (retail 0x0040936B through ILT 0x0003765F), which
// walks its owner list and calls this on each node. The node is the
// AnimationSoundClientBehavior owner: out of listener range (or with drawable
// flag +0x143 clear) it hands itself to the registry's U4Notify::noteOwner; in
// range it walks the drawable's draw modules and, for every named sound range,
// queries the module-data sound set (tree body 0x00605550) and fires an audio
// event per matching entry.
//
// MEASURED STATE (tools/probe.py --size 903, 2026-09-28):
//   907/903 bytes emitted, 172 non-relocation byte differences,
//   shape 0.956, 12 structural differences, frame `sub esp,0x11c` == retail.
//   Previous bank was 902 B / 308 diffs; the single change below is worth -136.
//
// THE LEVER THAT MATTERS MOST (new this session, -136 diffs):
//   the draw-module walk needs a *guarded pointer* plus a *separate copy* of
//   that pointer as the loop induction variable:
//
//       void **first = draw->getDrawModules();
//       if (first && *first)
//       {
//           void **modules = first;
//           do { ...body... } while (*++modules);
//       }
//
//   Only this spelling makes MSVC 7.1 emit retail's rotated module loop:
//   test eax,eax / je ; cmp dword [eax],0 / je ; mov edi,eax / mov [esp+..],edi ;
//   jmp +0x100 over a 7-byte `lea esp,[esp]` npad, with the body at +0x100 and
//   the bottom block at +0x35b doing
//       mov edi,[esp+..] / mov eax,[edi+4] / add edi,4 / test eax,eax /
//       mov [esp+..],edi / jne body
//   -- the load-before-increment of `*m` that only a do-while produces.
//
//   Why the earlier 23 spellings missed it: with ONE pointer variable, MSVC
//   folds the guard and the induction variable into a single value, schedules
//   `mov edi,eax` BEFORE the two tests, and never rotates.  Giving the
//   induction variable its own definition AFTER the guard leaves eax holding
//   the raw return value across both tests, which is what retail's `cmp [eax],0`
//   reads.  Measured on the same body: single-variable `for` 308 diffs;
//   `if (m && *m) do{}while(*++m)` 599; this form 172.  The block split matters,
//   not the loop keyword: a `goto`-split guard, a post-increment `*modules++`
//   and a copy-after-guard form all land in the same 172-178 band, and
//   declaring the copy at the top of the loop body instead is worse (192).
//
// STILL OPEN, blocker=stack-slot-permutation (the only large residue left):
//   Every instruction shape now matches except the local frame slots.  Retail:
//     range-ptr 0x10 / name 0x14 / draw 0x18 / k 0x1c / i 0x20 / sounds 0x24 /
//     modules 0x28 / maxWeight 0x2c / listener 0x30,0x34,0x38 / end 0x3c /
//     count 0x40 / source 0x44 / ranges 0x48 / key 0x58
//   Ours:
//     range-ptr 0x10 / name 0x14 / k 0x18 / i 0x1c / modules 0x20 / draw 0x24 /
//     listener 0x28,0x2c,0x30 / minWeight 0x34 (shared with end) /
//     maxWeight 0x38 / sounds 0x3c / count 0x40 / source 0x44
//   i.e. `draw` is three slots too high and `sounds` three too low, and the
//   k/i pair is exchanged.  CORRECTION to three earlier sessions: this is NOT
//   declaration order (swapping declarations changes nothing) and NOT the
//   first-materialisation order proved by build/ord/ord.cpp (that experiment
//   used `volatile int`, which forces a home for every store and does not
//   describe address-taken or spilled objects).  It is neither forward nor
//   reverse source order either: moving the `sounds` definition to the top of
//   the function reproduces retail's slot SET exactly -- range/name/draw/
//   k/i/sounds/modules/max/listener/end/count/source all in retail's order --
//   but swaps draw(0x18) and sounds(0x24) and costs a 6-byte prologue, because
//   `mov reg,[esi+4] / add reg,8` then has to be emitted before the drawable
//   null check instead of at +0xcf.  That is the sharpest remaining lead: the
//   slot order wants `sounds` materialised in the entry block, the code wants
//   it sunk to the module-loop preheader, and nothing tried reconciles them.
//     - `sounds` assigned at the top / after the null check: correct slot SET,
//       draw and sounds exchanged, +6 bytes, 642-663 diffs
//     - `sounds` assigned in the module-loop body: code lands at +0xe7 (LICM
//       does not hoist it), 192 diffs
//     - `sounds` assigned after the range check (this stash): right code,
//       wrong slots, 172 diffs
//
//   Secondary residues, all smaller:
//     * `i` lives in ebx here and in esi in retail, so retail re-materialises
//       `i` from the stack after the k loop (mov esi,[esp+0x20] at +0x303)
//       while we reload it at the k-loop bottom (mov ebx,[esp+0x1c], +4 bytes).
//       The cause is that esi is already holding `sounds` for the whole i loop.
//     * the min/max copy local adds `mov ecx,eax` + `mov [esp+0x34],eax` around
//       the key ctor; retail pushes the min straight from the selected pointer.
//       Dropping the copy (`key(name, bfmeMin(...))`) makes the argument
//       sequence byte-identical to retail but costs 394-527 diffs, so the copy
//       stays load-bearing.
//     * retail loads the entry weight as `fld dword [ebx+0x18]` (node-relative)
//       where we use `fld dword ptr [edi+8]` (value-relative).
//     * distance square: retail `fld st(1) / fmul st(2)`, ours `fld st(0) /
//       fmul st(1)`; source-order independent (four orderings are identical).
//
// DISPROVED this session (all on this body, all worse or no-ops):
//   const on sounds/draw/count/end/pos: byte-identical no-ops.  `const` on the
//   tree pointer does not even compile (it selects const_iterator).
//   countdown or post-decrement k loop: no-op or 495 and frame 0x124.
//   i-loop as `do{}while(++i<count)`, min computed before max (420), maxWeight
//   as an array (186), plain `Real minWeight` (194, frame 0x124), minWeight
//   element 0 instead of 1 (no-op), no `const Rva00605800Value &value` binding
//   (410), listener as a reference instead of a copy (693), no `sounds` local
//   at all (741), name/end hoisted, block scoping.
//   tools/eh_levers.py (6 choices) and tools/shape_family_levers.py
//   (sib,register,bool,test,copy,store,loop,branch,constant,frame; 5 choices)
//   each ran 5 trials through shape_search on this body: no improvement.
//
// KEY SEMANTICS PROVED FROM RETAIL (do not re-derive):
//   * key weight is min(m_start,m_end): the `fcomp` at +0x1a7 selects the max
//     POINTER into [esp+0x2c] (compared against the entry weight at +0x262,
//     skipping when the weight is greater), and the value pushed to the key
//     ctor comes from &m_start unless the pair is unordered.
//   * the module-data sound tree sits at node+4 -> +8 (`mov esi,[esi+4];
//     add esi,8` at +0xcf); the entry is the node at ebx, the value at
//     ebx+0x10, weight at +0x18, gated byte at +0x6c, range pointers +0x1c
//     and +0x44.
//   * drawable flag at +0x143, gated test object at +0x250, range square at
//     this+0x10, listener position through vtable +0x10c, addAudioEvent through
//     vtable +0x44.
//
// LINK TODO before landing: the key ctor/dtor (0x00605690 via ILT 0x00040C28,
// 0x00605080 via ILT 0x000014D8) and the audio event ctor/dtor (0x000B45E0 via
// ILT 0x0000AFBF, 0x00026F35) need pins under the TU-local names used here.
// Scratch for this session: build/s6/ (harness.py, gen.py, t1..t16.py, prof.py,
// slots.py, v/*.cpp), build/shape_search/59151656.../ and 4de5b6a2.../.
//
// EARLIER SESSIONS (kept for the record; several conclusions are superseded by
// the loop-rotation finding above):
//   * bfmeMin must be copied into a named local before the key ctor, or pass it
//     inline: one scratch-rotation step, worth -209 diffs (527 -> 320).
//   * the frame is 0x11c, not 0x124; the extra four bytes come from the min
//     copy object, absorbed by declaring it `Real minWeight[2]` and writing one
//     element (documented in docs/shape_levers.md).
//   * MSVC normalises the up-count k loop into retail's countdown-plus-pointer
//     advance for free, so the k-loop source form is not a lever (confirmed
//     again this session: byte-identical either way).
//   * hoisting `sounds` above `draw` was measured at 673 diffs on the OLD body;
//     on this body the same hoist is 663 with a much better slot set, so the
//     number alone is misleading -- read the slot map, not the count.
//   * SUPERSEDED: "the retail module loop is not reachable by any spelling".
//     It is reachable; see the top of this header.

#include <set>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

extern const char g_bfmeEmptyAscii[];

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	~AsciiString(void)
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}
	int compareNoCase(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : g_bfmeEmptyAscii;
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : g_bfmeEmptyAscii;
		int result = _memicmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

struct Coord3D
{
	Real x, y, z;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

// Sound entry of the animation-sound set: the tree at 0x00605550 orders it
// by name (case-insensitive) then weight; 0x00605690 constructs it and
// 0x00605080 destroys it (the tree's node destructor 0x00605820 reaches the
// same body through ILT 0x000014D8).
struct Rva00605800Value
{
	Rva00605800Value(const AsciiString &key, Real weight);
	~Rva00605800Value();

	AsciiString m_key;
	AsciiString m_eventName;
	Real m_weight;
	Int m_rangeA[10];
	Int m_rangeB[10];
	Bool m_gated;
};

struct Rva00605800Less
{
	bool operator()(const Rva00605800Value &left, const Rva00605800Value &right) const
	{
		int c = left.m_key.compareNoCase(right.m_key);
		if (c < 0)
			return true;
		if (c > 0)
			return false;
		return left.m_weight < right.m_weight;
	}
};

typedef _STL::_Rb_tree<Rva00605800Value, Rva00605800Value, _STL::_Identity<Rva00605800Value>,
	Rva00605800Less, _STL::allocator<Rva00605800Value> > Rva00605800Tree;

struct ModuleData006059F0
{
	UnsignedByte m_unmodelled00[8];
	Rva00605800Tree m_sounds;
};

class Gen0003C2E5
{
public:
	Bool test(void *a, void *b);
};

class Drawable
{
public:
	const Coord3D *getPosition(void) const;
	void **getDrawModules(void) const;
	DrawableID getID(void) const;

	UnsignedByte m_unmodelled000[0x143];
	Bool m_143;
	UnsignedByte m_unmodelled144[0x250 - 0x144];
	Gen0003C2E5 m_250;
};

// Address-derived 0x70-byte view of the audio event built per sound entry.
class AudioEvent006059F0
{
public:
	AudioEvent006059F0(const AsciiString &eventName, DrawableID drawableID);
	~AudioEvent006059F0();

private:
	unsigned __int64 m_storage[14];
};

template <class T> inline const T &bfmeMax(const T &a, const T &b) { return a > b ? a : b; }
template <class T> inline const T &bfmeMin(const T &a, const T &b) { return a < b ? a : b; }

struct Range006059F0
{
	Real m_start;
	Real m_end;
};

class SoundSource006059F0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual Int getCount006059F0();
	virtual AsciiString getName006059F0(Int index);
	virtual void slot0B(); virtual void slot0C();
	virtual void getRanges006059F0(Int index, Range006059F0 *first, Range006059F0 *second);
};

class DrawModule006059F0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual SoundSource006059F0 *getSoundSource006059F0();
};

struct Rva005A00B0AudioClient
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10();
	virtual void addAudioEvent006059F0(AudioEvent006059F0 *event);
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot1A(); virtual void slot1B(); virtual void slot1C(); virtual void slot1D();
	virtual void slot1E(); virtual void slot1F(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot2A(); virtual void slot2B(); virtual void slot2C(); virtual void slot2D();
	virtual void slot2E(); virtual void slot2F(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot3A(); virtual void slot3B(); virtual void slot3C(); virtual void slot3D();
	virtual void slot3E(); virtual void slot3F(); virtual void slot40(); virtual void slot41();
	virtual void slot42();
	virtual const Coord3D *getListenerPosition006059F0();
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class U4Owner00604C00;
class U4Notify
{
public:
	void noteOwner(U4Owner00604C00 *owner);
};

class BfmeResetSubsystem;
extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

struct Node004092A0
{
	void update006059F0();

	UnsignedByte m_unmodelled00[4];
	ModuleData006059F0 *m_moduleData;
	Drawable *m_drawable;
	UnsignedByte m_unmodelled0C[4];
	Real m_rangeSqr;
	Node004092A0 *m_next;
	Node004092A0 *m_prev;
};

void Node004092A0::update006059F0()
{
	Drawable *draw = m_drawable;
	if (!draw)
		return;

	Bool inRange = false;
	if (draw->m_143)
	{
		if (!TheAudioClientUpdate)
			return;
		Coord3D listener = *TheAudioClientUpdate->getListenerPosition006059F0();
		const Coord3D *pos = draw->getPosition();
		Real dx = listener.x - pos->x;
		Real dy = listener.y - pos->y;
		Real dz = listener.z - pos->z;
		inRange = !(dx * dx + dy * dy + dz * dz > m_rangeSqr);
	}
	if (!inRange)
	{
		if (g_animationSoundClientBehaviorGlobal)
			((U4Notify *)g_animationSoundClientBehaviorGlobal)->noteOwner((U4Owner00604C00 *)this);
		return;
	}
	Rva00605800Tree *sounds = &m_moduleData->m_sounds;

	void **first = draw->getDrawModules();
	if (first && *first)
	{
	void **modules = first;
	do
	{
		SoundSource006059F0 *source = ((DrawModule006059F0 *)*modules)->getSoundSource006059F0();
		if (!source)
			continue;
		Int count = source->getCount006059F0();
		for (Int i = 0; i < count; ++i)
		{
			AsciiString name = source->getName006059F0(i);
			Range006059F0 ranges[2];
			ranges[0].m_start = 0.0f;
			ranges[0].m_end = 0.0f;
			ranges[1].m_start = 0.0f;
			ranges[1].m_end = 0.0f;
			source->getRanges006059F0(i, &ranges[0], &ranges[1]);
			for (Int k = 0; k < 2; ++k)
			{
				Range006059F0 *range = &ranges[k];
				if (range->m_start == range->m_end)
					continue;
				Real maxWeight = bfmeMax(range->m_start, range->m_end);
				Real minWeight[2];
				minWeight[1] = bfmeMin(range->m_start, range->m_end);
				Rva00605800Value key(name, minWeight[1]);
				Rva00605800Tree::iterator it = sounds->lower_bound(key);
				Rva00605800Tree::iterator end = sounds->end();
				while (it != end)
				{
					const Rva00605800Value &value = *it;
					if (value.m_key.compareNoCase(name) != 0)
						break;
					if (!(value.m_weight <= maxWeight))
						break;
					++it;
					if (value.m_weight == range->m_start)
						continue;
					if (value.m_gated && !draw->m_250.test((void *)value.m_rangeA, (void *)value.m_rangeB))
						continue;
					AudioEvent006059F0 event(value.m_eventName, draw->getID());
					TheAudioClientUpdate->addAudioEvent006059F0(&event);
				}
			}
		}
	} while (*++modules);
	}
}
