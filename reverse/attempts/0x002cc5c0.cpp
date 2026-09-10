// ?onEnterReached@DockUpdate@@UAEXPAVObject@@@Z
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include ...
// stlport
//
// Identity CONFIRMED by vtable-slot geometry: DockUpdateInterface's slot 9 is
// onEnterReached (0-indexed: isClearToApproach=0 ... onApproachReached=8,
// onEnterReached=9, onDockReached=10, onExitReached=11). symbols.csv already
// pins slot 10 (onDockReached@DockUpdate, 0x002CC750) and slot 11
// (onExitReached@DockUpdate, 0x002CC7F0) from the SAME vtable; 0x002CC5C0
// (318B) sits exactly one slot before them with tight, function-sized gaps
// (0x2CC5C0+0x13E=0x2CC6FE .. pad .. 0x2CC750; 0x2CC750+0x7A=0x2CC7CA ..
// pad .. 0x2CC7F0). The body itself is also a near-exact structural match
// for ZH's DockUpdate::onEnterReached: two clearAndSetModelConditionFlags
// calls (retail's REL32 callee 0x000095ED appears exactly x2 in the dump,
// matching the pinned clearAndSetModelConditionFlags@Object callee count)
// followed by a linear scan of m_approachPositionOwners clearing the
// docker's slot -- see reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp:327.
//
// LEDGER CONFLICT, NOT YET RESOLVED: reverse/functions.csv ALREADY claims
// the mangled name ?onEnterReached@DockUpdate@@UAEXPAVObject@@@Z at a
// DIFFERENT address, 0x002CDDF0 (216B, Code/GameEngine/Source/GameLogic/
// Object/Update/DockUpdate/DockUpdateOnEnterReached.cpp), landed on weaker
// evidence ("identity is plausible from onApproachReached offsets and caller
// cluster"). Since one mangled name cannot own two different-sized bodies,
// and the vtable-slot proof above is much stronger, that earlier landing at
// 0x002CDDF0 is very likely a MISIDENTIFICATION of some other function that
// merely happens to byte-match there. Landing 0x002CC5C0 under the real
// name requires `add_match.py --replace-existing` on that row FIRST -- read
// it as "retract a real claim in its own commit" (add_match.py's own
// docstring), i.e. rename the 0x002CDDF0 row to an honest address-derived
// placeholder in its own commit, THEN claim the real name here. Out of
// scope for this attempt; flagging for whoever picks this up next.
//
// SHAPE GAP (this attempt, NOT byte-exact): ours compiles to 377B against
// retail's 318B (122 non-reloc bytes differ in a probe.py diff). The
// PROLOGUE, FRAME SIZE (sub esp,0x50) and BIT CONSTANTS all match exactly,
// which confirms: BFME's ModelConditionFlags is BitFlags<320> (10 dwords,
// see Code/GameEngine/Source/Common/BfmeConv2097.cpp), not ZH's much larger
// MODELCONDITION_COUNT header value, and retail's clearAndSetModelCondition-
// Flags calls resolve through an ILT thunk to bfmeSetVKP@BfmeThingVKP
// (Code/GameEngine/Source/Common/BfmeConv1407.cpp, already matched at
// 0x001C7720), which takes the two flag-block addresses as plain ints.
// Bit indices read directly off retail's immediates: `or eax,0x30000` (bits
// 16|17) and `or eax,0x80000` (bit 19) give DOCKING=16, DOCKING_BEGINNING=17,
// DOCKING_ACTIVE=18, DOCKING_ENDING=19 (word 0 of the 10-word block).
//
// What's still wrong: retail INTERLEAVES the zero-initialization of the two
// 40-byte temporaries word-by-word (store into temp A's word0, temp B's
// word0, temp A's word1, temp B's word1, ...), where ours constructs each
// temporary fully before starting the next -- tried both named locals in a
// nested block AND an inline __forceinline bfmeFlagsAddr() helper called
// directly in the argument list (mirroring ZH's inline-temporary call
// style); both produced BYTE-IDENTICAL output, so the interleaving is not
// coming from source-level temp/statement structure. The +59B overshoot
// (377 vs 318, i.e. two calls' worth of construction where retail seems to
// pack tighter) suggests either a different underlying representation for
// the 320-bit block (try a flat `unsigned int[10]` with explicit index/or
// instead of _STL::bitset<320>::_Unchecked_set -- untried) or that retail
// shares/reorders the two per-call temporary pairs across the whole
// function rather than per-call. NEXT: try the flat-array representation
// first; if that doesn't change the interleaving either, the lever is
// probably in bfmeApplyVKP's own parameter-passing shape rather than in
// this caller at all.

class BfmeThingVKP
{
public:
	void bfmeSetVKP(int a, int b);
};

template <size_t NUMBITS>
class BfmeDockFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BfmeDockFlags(BogusInitType, int idx1);
	BfmeDockFlags(BogusInitType, int idx1, int idx2);

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
BfmeDockFlags<NUMBITS>::BfmeDockFlags(BogusInitType, int idx1)
{
	m_bits._Unchecked_set(static_cast<size_t>(idx1));
}

template <size_t NUMBITS>
BfmeDockFlags<NUMBITS>::BfmeDockFlags(BogusInitType, int idx1, int idx2)
{
	m_bits._Unchecked_set(static_cast<size_t>(idx1));
	m_bits._Unchecked_set(static_cast<size_t>(idx2));
}

template <size_t NUMBITS>
static __forceinline int bfmeFlagsAddr(const BfmeDockFlags<NUMBITS> &f)
{
	return (int)&f;
}

enum
{
	BFME_MODELCONDITION_DOCKING = 16,
	BFME_MODELCONDITION_DOCKING_BEGINNING = 17,
	BFME_MODELCONDITION_DOCKING_ACTIVE = 18,
	BFME_MODELCONDITION_DOCKING_ENDING = 19
};

// Drop-in body for DockUpdate::onEnterReached inside DockUpdate.cpp (needs
// that TU's real-header DockUpdate/Object class hierarchy; this compiled
// and byte-diffed via `python3 tools/probe.py Code/.../DockUpdate.cpp
// "?onEnterReached@DockUpdate@@UAEXPAVObject@@@Z" 0x002CC5C0`).
void DockUpdate::onEnterReached( Object* docker )
{
	Object *me = getObject();
	reinterpret_cast<BfmeThingVKP*>(me)->bfmeSetVKP(
		bfmeFlagsAddr( BfmeDockFlags<320>( BfmeDockFlags<320>::kInit, BFME_MODELCONDITION_DOCKING_ENDING ) ),
		bfmeFlagsAddr( BfmeDockFlags<320>( BfmeDockFlags<320>::kInit, BFME_MODELCONDITION_DOCKING_BEGINNING, BFME_MODELCONDITION_DOCKING ) ) );
	reinterpret_cast<BfmeThingVKP*>(docker)->bfmeSetVKP(
		bfmeFlagsAddr( BfmeDockFlags<320>( BfmeDockFlags<320>::kInit, BFME_MODELCONDITION_DOCKING_ENDING ) ),
		bfmeFlagsAddr( BfmeDockFlags<320>( BfmeDockFlags<320>::kInit, BFME_MODELCONDITION_DOCKING_BEGINNING, BFME_MODELCONDITION_DOCKING ) ) );
	m_dockerInside = TRUE;

	ObjectID dockerID = docker->getID();
	for( Int positionIndex = 0; positionIndex < m_approachPositionOwners.size(); ++positionIndex )
	{
		if( m_approachPositionOwners[positionIndex] == dockerID )
		{
			m_approachPositionOwners[positionIndex] = INVALID_ID;
			m_approachPositionReached[positionIndex] = FALSE;
			return;
		}
	}
}
