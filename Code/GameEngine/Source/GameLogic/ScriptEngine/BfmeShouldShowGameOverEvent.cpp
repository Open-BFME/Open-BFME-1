// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x002ED8F0, 70 bytes, no frame: three globals and no locals.
//
// Two of the globals are known -- 0x012F076C is TheScriptEngine and
// 0x012F0898 is TheGameLogic. The two predicate calls in front of them are
// only known by their ILTs, and reverse/symbols.csv already carries names
// minted for exactly these two sites (bfmeIsSet on BfmeGameOverGateA at ILT
// 0x000330DC and on BfmeGameOverGateB at 0x0000CFC7), so the globals are
// declared with those types to reach them. The addresses themselves ride
// DIR32 relocations copied from retail, so only the two REL32 calls have to
// resolve.
//
// Layout that falls out of the tail: the mode word sits at +0x10C of
// GameLogic and is meaningful at 1 and 5, and the word tested for zero is at
// +0x290. An if with || rather than a switch, or the two calls would compile
// to dec/sub instead of two cmps.
//
// The return type is an eight-bit one, not bool: reverse/reloc_names.csv
// guesses _N, but bool makes the compiler materialise a full 32-bit 0/1
// (xor eax,eax before the sete) where retail sets al alone and leaves the
// mode value's high bits sitting in eax. Both other exits agree -- mov al,1
// and xor al,al. So the row goes in as @@YAEXZ.

typedef bool Bool;
typedef unsigned char BfmeByteBool;			// see the note above
typedef int Int;

class BfmeGameOverGateA
{
public:
	Bool bfmeIsSet(void);					// ILT 0x000330DC
};

class BfmeGameOverGateB
{
public:
	Bool bfmeIsSet(void);					// ILT 0x0000CFC7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_bfmeHead[0x10C];
	Int m_bfmeMode;						// +0x10C
	char m_bfmeTail[0x290 - 0x110];
	void *m_bfme0290;					// +0x290
};

extern BfmeGameOverGateA *TheBfmeGameOverGateA;			// 0x012ED748
extern BfmeGameOverGateB *TheScriptEngine;			// 0x012F076C
extern GameLogic *TheGameLogic;					// 0x012F0898

// ?BfmeShouldShowGameOverEvent@@YA_NXZ
BfmeByteBool BfmeShouldShowGameOverEvent(void)
{
	if (TheBfmeGameOverGateA->bfmeIsSet() || TheScriptEngine->bfmeIsSet())
		return 1;

	GameLogic *logic = TheGameLogic;

	if (logic->m_bfmeMode == 1 || logic->m_bfmeMode == 5)
		return !logic->m_bfme0290;

	return 0;
}
