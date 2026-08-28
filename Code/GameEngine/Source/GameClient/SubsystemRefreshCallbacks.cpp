// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: the two subsystem-refresh callbacks at retail 0x001072A0 and
// 0x001072F0, converted out of Code/gen_asm/d_000f93a0.asm. 58 bytes each,
// 0x50 apart, and the same body under two pairs of vtable slots.
//
// PlayerList::setLocalPlayer at 0x000DF3C0 hands their addresses to
// TheShroudManager and to the unnamed subsystem at 0x012ED5C0, one each, which
// is what says they are callbacks rather than ordinary functions.
//
// Each forwards its three arguments, unchanged and in order, to two singletons
// that may be null:
//
//   0x001072A0  TheDisplay slot +0x10C, then TheRadar slot +0x24
//   0x001072F0  TheDisplay slot +0x118, then TheRadar slot +0x2C
//
// Both globals were already named in reverse/symbols.csv. What the three
// arguments are is not settled by these bodies -- they only pass them along --
// so they are typed Int and named by position. The two functions keep their
// address-derived ledger names for the same reason.
//
// The register assignment differs between the two and is retail's, not a
// choice: 0x001072A0 caches a1/a3/a2 into ebx/esi/edi and 0x001072F0 caches
// a3/a2/a1, yet both push a1, a2, a3 in that order at both call sites.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c( Int a1, Int a2, Int a3 ) = 0;		///< +0x10C
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118( Int a1, Int a2, Int a3 ) = 0;		///< +0x118
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024( Int a1, Int a2, Int a3 ) = 0;		///< +0x024
	virtual void slot028() = 0;
	virtual void slot02c( Int a1, Int a2, Int a3 ) = 0;		///< +0x02C
};

extern Display *TheDisplay;
extern Radar *TheRadar;

// ?d_001072a0@@YAXHHH@Z
void d_001072a0( Int a1, Int a2, Int a3 )
{
	if (TheDisplay)
		TheDisplay->slot10c( a1, a2, a3 );

	if (TheRadar)
		TheRadar->slot024( a1, a2, a3 );
}

// 0x001072F0 is not landed. Its body is this one with two slot numbers changed
// and one thing that is not a source difference: retail caches a3/a2/a1 into
// ebx/esi/edi there where it caches a1/a3/a2 here, though both push a1, a2, a3
// in that order at both call sites. Identical C++ produces the ordering below
// for both, and swapping the two definitions in this TU does not move it.
// ?d_001072f0@@YAXHHH@Z present-unmatched
void d_001072f0( Int a1, Int a2, Int a3 )
{
	if (TheDisplay)
		TheDisplay->slot118( a1, a2, a3 );

	if (TheRadar)
		TheRadar->slot02c( a1, a2, a3 );
}
