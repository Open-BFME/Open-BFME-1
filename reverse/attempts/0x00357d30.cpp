// attempt stash for ?duplicate@Condition@@QBEPAV1@XZ at 0x00357D30
// partial score=0.55 date=2026-09-09
//
// Third attempt on this row (2 prior blocked entries exist). Both prior
// attempts wrongly concluded Parameter/Condition needed MORE fields than ZH;
// this attempt corrects that: the class layout is EXACTLY the ZH one, field
// for field, no extra members. What actually happens is Parameter's implicit
// (compiler-generated) operator= gets INLINED field-by-field into duplicate()
// rather than called, AND retail chooses to fully inline Condition's own
// constructor body at ONE of its two call sites but not the other -- both of
// those inlining choices were mistaken for "more fields" by earlier attempts.
//
// Ground truth for Parameter's layout came from two ALREADY-MATCHED sibling
// files, not from re-guessing:
//   - Code/GameEngine/Source/GameLogic/ScriptEngine/Condition_ctor.cpp
//     (83B, real ??0Condition@@QAE@W4ConditionType@0@@Z @ 0x00357CC0)
//   - Code/GameEngine/Source/GameLogic/ScriptEngine/Condition_setConditionType_Thunk.cpp
//     (215B, real ?setConditionType@Condition@@... @ 0x00355D10)
// Condition: ConditionType m_conditionType; int m_hasWarnings;
// Parameter *m_parms[12]; int m_customData; int m_customFrame; int m_numParms;
// Condition *m_nextAndCondition; (vtable + these = 0x4C, matches the
// operator new(0x4C) at every Condition allocation site in this function).
// Parameter: ParameterType m_paramType; bool m_initialized (+3 pad); int
// m_int; float m_real; AsciiString m_string; Coord3D m_coord; a 2-dword
// status mask. Total 0x28, matching every byte offset (0..0x24) this body's
// raw copy touches. The string-copy call resolves to 0x00887C90, which is an
// ICF fold shared by EVERY StringBase<T>::set() (Ascii or Unicode) -- it does
// NOT by itself prove BFME widened m_string, contra the 2nd prior attempt's
// conclusion. Confirmed via ?set@AsciiString@@QAEXABV1@@Z and
// ?set@UnicodeString@@QAEXABV1@@Z both already pinned at the SAME address in
// reverse/symbols.csv.
//
// This version below compiles clean and reaches 448 of the target 514 bytes.
// explain_mismatch's first diff is just a register-naming difference (esi
// used where retail keeps a value in a different register) that cascades
// through the whole first Parameter-copy loop without changing its shape --
// every subsequent load/store in that loop matches instruction-for-
// instruction once you look past the renamed register, including the
// Coord3D sub-object copy shape (this needed a `struct Coord3D { float x,y,z; }`
// member rather than a raw `float[3]`, or the compiler linearizes it
// differently -- confirmed, this alone moved the diff into alignment through
// offset 0x24).
//
// What is NOT closed: the AND-linked-list `while (pLink)` loop. Retail's
// SECOND `new Condition(...)` (inside the loop, one per linked condition)
// compiles with the whole Condition constructor body INLINED at that call
// site (12-dword m_parms zero loop visible directly in duplicate()'s bytes,
// then a real call out to setConditionType); the FIRST `new Condition(...)`
// (the primary duplicate) instead compiles to a genuine call to the already-
// matched real ctor at 0x00357CC0. This is retail's own per-call-site /O2
// inlining choice on the exact same constructor body appearing twice in
// source -- not something the source structure below controls on its own.
// Declaring the ctor only (no body visible in this TU, as below) makes BOTH
// call sites real calls (short by ~66B, this file's state). Tried: giving
// the compiler the ctor's actual body (copied verbatim from Condition_ctor.cpp,
// including a from-scratch setConditionType DECLARATION -- do NOT give
// setConditionType a body too, that makes the compiler resolve the ctor's
// internal call to a freshly-compiled LOCAL copy instead of the pinned
// external 0x00355D10 body, which is wrong) got the primary call routed
// correctly through 0x00357CC0 directly (matching structurally) but grew to
// 458B with the loop's inlined copy now indexed differently (register
// scheme changed, and one inlined-ctor immediate at the vtable-store site
// came out wrong -- 0x8418b24 instead of retail's 0x10e84dc, suggesting the
// vtable-store bytes were misaligned by the surrounding register shuffle,
// not a wrong vtable address per se). That version is NOT this stash (it
// regressed the otherwise-clean first loop); worth revisiting with fresh
// eyes on register allocation once the ctor-visibility trick is kept.
//
// Next lever to try: keep the ctor's body visible (as in the 458B attempt)
// but rebuild the *outer* duplicate() loop structure to match retail's
// register choices from scratch line-by-line (the loop-body register
// scheme visibly changed once the ctor became inlineable, so this needs a
// fresh iteration pass, not a reuse of the declared-only version's shape).
// t=90min model=sonnet-5.1

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=( const AsciiString &other ) { set( other ); return *this; }
	void set( const AsciiString &other );

private:
	void *m_data;
};

struct Coord3D
{
	float x, y, z;
};

class Parameter
{
public:
	// implicit memberwise operator= -- matches retail's inlined copy exactly

private:
	int m_paramType;
	Bool m_initialized;
	int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	unsigned int m_status0;
	unsigned int m_status1;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};

	Condition( ConditionType type );
	virtual ~Condition();
	void setConditionType( ConditionType type );
	Condition *duplicate() const;

private:
	ConditionType m_conditionType;
	int m_hasWarnings;
	Parameter *m_parms[ 12 ];
	int m_customData;
	int m_customFrame;
	int m_numParms;
	Condition *m_nextAndCondition;
};

// ?duplicate@Condition@@QBEPAV1@XZ
Condition *Condition::duplicate() const
{
	Condition *pNew = new Condition( m_conditionType );
	Int i;
	for( i = 0; i < m_numParms && i < pNew->m_numParms; ++i )
	{
		*pNew->m_parms[ i ] = *m_parms[ i ];
	}

	Condition *pLink = m_nextAndCondition;
	Condition *pCur = pNew;
	while( pLink )
	{
		pCur->m_nextAndCondition = new Condition( pLink->m_conditionType );
		pCur = pCur->m_nextAndCondition;
		for( i = 0; i < pLink->m_numParms; ++i )
		{
			*pCur->m_parms[ i ] = *pLink->m_parms[ i ];
		}
		pLink = pLink->m_nextAndCondition;
	}

	return pNew;
}
