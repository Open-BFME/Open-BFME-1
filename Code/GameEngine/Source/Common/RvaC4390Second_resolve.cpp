// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RvaC4390Second::resolve, retail 0x001CB0C0, 119 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it as the
// relation resolver.
//
// Three answers in order. The template at +0x04 is walked to its final override
// -- the same one-level inline Rva2225E0Filter::accepts uses, and with the same
// blind spot: a null template is not tested again before the flags at +0xD4 are
// read. If bit 0x1000 is set there, this is its own answer.
//
// Otherwise the thing at +0x214, if there is one and it is of kind 0x6C, is the
// answer. Failing that the Int argument -- tested as a byte, so it is really a
// flag -- allows one more try: the object the id at +0x78 names, looked up in
// TheGameLogic and put through the same kind test.
//
// Both kind tests share one return, so the second jumps back into the first.
//
// The argument is spelled Int by the mangled name but only its low byte is
// tested, so the source narrows it: reading the whole word gives a test on eax
// where retail tests al.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct RvaC4390First;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);		// ILT 0x000022BB

	char m_bfmeHeadA[0x04];
	BfmeOverridable *m_bfmeNextOverride;			// +0x04
	char m_bfmeHeadB[0xD4 - 0x08];
	UnsignedInt m_bfmeFlags;				// +0xD4
};

enum KindOfType { BFME_KINDOF_6C = 0x6C };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;			// ILT 0x0003251F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);				// ILT 0x0001F253
};

extern GameLogic *TheGameLogic;					// 0x012F0898

class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int allowLookup);

private:
	char m_bfmeHeadA[0x04];
	BfmeOverridable *m_bfmeTemplate;			// +0x04
	char m_bfmeHeadB[0x78 - 0x08];
	Int m_bfmeObjectID;					// +0x78
	char m_bfmeHeadC[0x214 - 0x7C];
	Thing *m_bfmeThing;					// +0x214
};

// ?resolve@RvaC4390Second@@QAEPAURvaC4390First@@H@Z
RvaC4390First *RvaC4390Second::resolve(Int allowLookup)
{
	BfmeOverridable *final = m_bfmeTemplate;

	if (final && final->m_bfmeNextOverride)
		final = final->m_bfmeNextOverride->friend_getFinalOverride();

	if (final->m_bfmeFlags & 0x1000)
		return (RvaC4390First *)this;

	Thing *thing = m_bfmeThing;

	if (thing && thing->isKindOf(BFME_KINDOF_6C))
		return (RvaC4390First *)thing;

	if ((char)allowLookup)
	{
		thing = TheGameLogic->findObjectByID(m_bfmeObjectID);

		if (thing && thing->isKindOf(BFME_KINDOF_6C))
			return (RvaC4390First *)thing;
	}

	return 0;
}
