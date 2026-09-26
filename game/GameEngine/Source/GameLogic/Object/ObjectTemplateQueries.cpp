// cl: /DNDEBUG /MD /EHsc
// stlport

// The three Object queries that answer out of the ThingTemplate's final override:
//
//   getRadarPriority            0x001CA4D0  m_radarPriority, then two kind-of fallbacks
//   isNonFactionStructure       0x001C8130  one kind-of bit, minus five faction kinds
//   bfmeResetSafeOcclusionFrame 0x001C3020  m_occlusionDelay, stamped onto the object
//
// All three start from m_template at Object+0x04 and walk the override chain
// before reading anything, and each file described that walk and that template
// from scratch. Between them they name three ThingTemplate fields where each knew
// one:
//
//   +0x0C8  m_kindOf[3]      getRadarPriority names it; isNonFactionStructure
//                            reached the same address as a raw byte
//   +0x428  m_occlusionDelay bfmeResetSafeOcclusionFrame
//   +0x490  m_radarPriority  getRadarPriority
//
// and the two kind-of readers turn out to be reading one array from opposite
// ends: bit 7 of word 0 for the structure test, bit 0x20000 of word 1 -- bit 49 --
// for the radar fallback.
//
// Overridable had three accounts too, all agreeing that m_nextOverride is at
// +0x04 and disagreeing on how getFinalOverride is spelled: declared-only in two
// files, inline and recursive in the third. Both spellings are load-bearing and
// both are here, the way ObjectCommandButtons.cpp already carries them --
// getFinalOverride out of line, because that is the call retail makes, plus an
// inline bfmeFinalOverride for the body that carries the guarded walk expanded.
// Defining getFinalOverride inline instead would inline it into the other two and
// change their bytes.
//
// isNonFactionStructure keeps a byte-sized read of m_kindOf[0]: retail tests it
// with `test byte`, and going through the UnsignedInt would widen that.

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum RadarPriorityType
{
	RADAR_PRIORITY_INVALID,
	RADAR_PRIORITY_NOT_ON_RADAR,
	RADAR_PRIORITY_STRUCTURE,
	RADAR_PRIORITY_UNIT,
	RADAR_PRIORITY_LOCAL_UNIT_ONLY,
	RADAR_PRIORITY_NUM_PRIORITIES
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// Retail's own call; the two bodies that reach the end of the chain make it.
	const Overridable *getFinalOverride() const;

	// The guarded one-step form, expanded inline in isNonFactionStructure.
	const Overridable *bfmeFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;			// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	UnsignedInt getOcclusionDelay() const { return m_occlusionDelay; }

	unsigned char m_unmodelled_008[0xc8 - 0x08];
	UnsignedInt m_kindOf[3];			// +0x0C8
	unsigned char m_unmodelled_0d4[0x428 - 0xd4];
	UnsignedInt m_occlusionDelay;			// +0x428
	unsigned char m_unmodelled_42c[0x490 - 0x42c];
	signed char m_radarPriority;			// +0x490
};

// KINDOF bits, numbered from m_kindOf[0] bit 0.
enum { KINDOF_STRUCTURE_BIT = 7, KINDOF_RADAR_STRUCTURE_BIT = 49 };

// The contain module, seen here only for its garrisonable query.
class BfmeRadarContain
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual bool isGarrisonable();
};

// The five faction kinds isNonFactionStructure excludes, built on the stack as a
// six-dword mask.
class BfmeKindOfMask
{
public:
	__forceinline BfmeKindOfMask(Int idx1, Int idx2, Int idx3, Int idx4, Int idx5)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
		m_bits.set(idx4);
		m_bits.set(idx5);
	}

private:
	std::bitset<192> m_bits;
};

// Object under the spelling the kind-of test is pinned as.
class BfmeKindOfTester
{
public:
	Bool isAnyKindOf(const BfmeKindOfMask &mask) const;
};

// m_template lives on Thing, and so does the accessor bfmeResetSafeOcclusionFrame
// carries inlined. The accessor stays on Thing rather than moving to Object
// because MSVC emits an out-of-line copy of it, and the ledger declares that copy
// under ?getTemplate@Thing@@QBEPBVThingTemplate@@XZ (0x00098E50, owned by
// Thing_isKindOf.cpp). Renaming it to Object::getTemplate produces a defined
// function with no row, which the commit hook refuses -- correctly. The rule this
// is an instance of: a merge may move a body between files but must not rename
// what the body emits alongside itself.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;

protected:
	virtual ~Thing();
	const ThingTemplate *m_template;		// +0x004
};

// The early null return is load-bearing: it is what makes MSVC duplicate
// bfmeResetSafeOcclusionFrame's tail -- the +0x428 load and the +0x334 store
// appear on both branches -- where a single combined test produces one copy and
// eleven fewer bytes.
inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *thingTemplate = m_template;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	RadarPriorityType getRadarPriority() const;
	Bool isNonFactionStructure(void) const;
	void bfmeResetSafeOcclusionFrame();

private:
	unsigned char m_unmodelled_008[0x1fc - 0x08];
	BfmeRadarContain *m_contain;			// +0x1FC
	unsigned char m_unmodelled_200[0x334 - 0x200];
	UnsignedInt m_safeOcclusionFrame;		// +0x334
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;				// +0x3C
};

extern GameLogic *TheGameLogic;

// ?getRadarPriority@Object@@QBE?AW4RadarPriorityType@@XZ
//
// Retail repeats the override walk for the kind-of fallback rather than keeping
// the first result, and the reconstruction repeats it too.
RadarPriorityType Object::getRadarPriority() const
{
	ThingTemplate *templateValue = (ThingTemplate *)m_template;
	if (templateValue != 0 && templateValue->m_nextOverride != 0)
		templateValue = (ThingTemplate *)templateValue->m_nextOverride->getFinalOverride();

	RadarPriorityType priority = (RadarPriorityType)templateValue->m_radarPriority;
	if (priority != RADAR_PRIORITY_INVALID)
		return priority;

	BfmeRadarContain *contain = m_contain;
	if (contain != 0 && contain->isGarrisonable())
		priority = RADAR_PRIORITY_STRUCTURE;

	templateValue = (ThingTemplate *)m_template;
	if (templateValue != 0 && templateValue->m_nextOverride != 0)
		templateValue = (ThingTemplate *)templateValue->m_nextOverride->getFinalOverride();
	return (templateValue->m_kindOf[1] & (1u << (KINDOF_RADAR_STRUCTURE_BIT - 32))) != 0
		? RADAR_PRIORITY_STRUCTURE : priority;
}

// ?isNonFactionStructure@Object@@QBE_NXZ
//
// The template flag check is inlined and the five-kind mask is built on the
// stack, which is why this TU needs STLport's bitset.
Bool Object::isNonFactionStructure(void) const
{
	const ThingTemplate *tmplate = m_template;
	if (tmplate && tmplate->m_nextOverride)
		tmplate = (const ThingTemplate *)tmplate->bfmeFinalOverride();
	return (*reinterpret_cast<const unsigned char *>(&tmplate->m_kindOf[0])
			& (1u << KINDOF_STRUCTURE_BIT)) != 0 &&
		!reinterpret_cast<const BfmeKindOfTester *>(this)->isAnyKindOf(
			BfmeKindOfMask(61, 62, 63, 64, 134));
}

// ?bfmeResetSafeOcclusionFrame@Object@@QAEXXZ
//
// Object.cpp preserves this assignment as frame + the template's occlusion delay.
void Object::bfmeResetSafeOcclusionFrame()
{
	GameLogic *gameLogic = TheGameLogic;
	if (gameLogic)
	{
		UnsignedInt frame = gameLogic->m_frame;
		const ThingTemplate *thingTemplate = getTemplate();
		m_safeOcclusionFrame = frame + thingTemplate->getOcclusionDelay();
	}
}
