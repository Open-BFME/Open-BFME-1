// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Q2FlagOwner::query, retail 0x00416FC0, 19 bytes. The body carried
// only a machine byte-dump row; the symbols.csv pin names it as the predicate
// every row of the 34-byte queried-index assignment family calls, and
// Q2QueriedIndexAssignments.cpp is where those rows live.
//
// It calls the same sound lookup that ThingTemplate::getSound at 0x00416FA0 --
// the body immediately before it, already ledgered -- calls, through the same
// ILT at 0x0000286A, and asks only whether anything came back. So the class the
// assignment family calls Q2FlagOwner is the class the reloc name calls
// ThingTemplate, and this predicate is the has-a-sound question next to
// getSound's give-me-the-sound-or-the-empty-one.
//
// The pointer becomes a Bool through neg/sbb/neg, this compiler's spelling of
// != 0, which is what makes the callers' test al,al a byte-wide truth value.

typedef int Int;
typedef bool Bool;

class AudioEventRTS;
class Q2FlagOwner;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
private:
	const AudioEventRTS *bfmeLookupSound(Int index) const;	// ILT 0x0000286A

	friend class Q2FlagOwner;
};

class Q2FlagOwner
{
public:
	Bool query(Int index);
};

// ?query@Q2FlagOwner@@QAE_NH@Z
Bool Q2FlagOwner::query(Int index)
{
	return ((const ThingTemplate *)this)->bfmeLookupSound(index) != 0;
}
