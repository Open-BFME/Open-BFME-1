// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BfmeSpecialPowerAllowanceStore::_bfme_allows, retail 0x0039BE50,
// 61 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// A negative answer from the index lookup allows the power outright. Otherwise
// the count the state keeps at +0x04 has to reach the requirement at +0x20 of
// the template -- or of whatever the template's override chain ends at, walked
// one level inline the way the rest of this family does.
//
// When the template has no override the requirement is read from the template
// itself, which is why the walk leaves its result in the same register the
// template arrived in rather than defaulting to null.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride(void);		// ILT 0x00048C61

	char m_bfmeHeadA[0x04];
	Overridable *m_bfmeNextOverride;			// +0x04
	char m_bfmeHeadB[0x20 - 0x08];
	Int m_bfmeRequired;					// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
};

class BfmePlayerSpecialPowerState
{
public:
	char m_bfmeHead[0x04];
	Int m_bfmeCount;					// +0x04
};

class BfmeSpecialPowerAllowanceStore
{
public:
	unsigned char _bfme_allows(BfmePlayerSpecialPowerState *state,
			const SpecialPowerTemplate *tmpl);

private:
	Int bfmeIndexOf(const SpecialPowerTemplate *tmpl);	// ILT 0x0003E0B3
};

// ?_bfme_allows@BfmeSpecialPowerAllowanceStore@@QAEEPAVBfmePlayerSpecialPowerState@@PBVSpecialPowerTemplate@@@Z
unsigned char BfmeSpecialPowerAllowanceStore::_bfme_allows(
		BfmePlayerSpecialPowerState *state, const SpecialPowerTemplate *tmpl)
{
	if (bfmeIndexOf(tmpl) < 0)
		return 1;

	Int count = state->m_bfmeCount;

	// The walk writes back over the argument rather than into a second
	// variable: with two names the compiler keeps two registers and copies
	// the template into the one the requirement is read through.
	Overridable *next = tmpl->m_bfmeNextOverride;

	if (next)
	{
		if (next->m_bfmeNextOverride)
			next = next->m_bfmeNextOverride->friend_getFinalOverride();

		tmpl = (const SpecialPowerTemplate *)next;
	}

	return count >= tmpl->m_bfmeRequired;
}
