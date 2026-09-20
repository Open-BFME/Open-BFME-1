// ?scan@Rva001C7530@@QBE_NXZ
// partial score=0.25 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// Carved body at retail RVA 0x001C7530 (161 B), 8 callers via ILT thunk.
// Landed neighbours (Object::getCrusherLevel/getCrushableLevel/canCrushOrSquish)
// place this in Object's own TU. Walks an override chain at this+0x214 while
// its resolved final-override flags field (+0xd4) has bit 0x1000 set, then
// checks the AI update interface at +0x204 (same offset already proven in
// Rva000EDB30TeamIsIdle.cpp), resolves a second override chain at +4, and
// compares locomotor speed * that override's float field (+0x3ec) against
// the nonnegative preferred locomotor height.  getFinalOverride is the
// already-landed Overridable recursion (GameCommon.cpp / LocomotorGetMaxTurnRateObject.cpp,
// pinned ILT 0x22bb -> 0x87A80); the class is redeclared here (TU-local,
// same mangled name) with the two extra fields this body's two chains read.
// The other two proven callees are pinned through ILT thunks 0x47c8 and 0x3daa5.
// Identity of the owning class/method is not proven; every name is address-derived.

typedef float Real;

extern const float BfmeZeroRange;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (this == 0)
			return this;
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	unsigned char m_unmodelled000[4];
	const Overridable *m_nextOverride;
	unsigned char m_pad008[0xd4 - 8];
	unsigned int m_flagsAt0xD4;
	unsigned char m_pad0d8[0x3ec - 0xd8];
	Real m_heightFactorAt0x3ec;
};

class AIUpdateInterface
{
public:
	Real getCurLocomotorSpeed() const;
};

class Rva001C7530
{
public:
	bool scan() const;

	unsigned char m_unmodelled000[4];
	Overridable *m_weaponOverrideChain;				// +0x4
	unsigned char m_pad008[0x204 - 8];
	AIUpdateInterface *m_aiUpdateInterface;			// +0x204
	unsigned char m_pad208[0x214 - 0x208];
	Overridable *m_armorOverrideChain;				// +0x214
};

class Object
{
public:
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
};

// ?scan@Rva001C7530@@QBE_NXZ
bool Rva001C7530::scan() const
{
	const Rva001C7530 *current = this;

	for (;;)
	{
		Overridable *chain = current->m_armorOverrideChain;
		if (!chain)
			break;

		const Overridable *result;
		const Overridable *level1 = chain->m_nextOverride;
		if (!level1)
		{
			result = level1;
		}
		else
		{
			const Overridable *level2 = level1->m_nextOverride;
			result = level2 ? level2->getFinalOverride() : level1;
		}

		if (!(result->m_flagsAt0xD4 & 0x1000))
			break;

		current = (const Rva001C7530 *)chain;
	}

	AIUpdateInterface *ai = current->m_aiUpdateInterface;
	if (!ai)
		return false;

	const Overridable *final2;
	const Overridable *weapon1 = current->m_weaponOverrideChain;
	if (!weapon1)
	{
		final2 = weapon1;
	}
	else
	{
		const Overridable *weapon2 = weapon1->m_nextOverride;
		final2 = weapon2 ? weapon2->getFinalOverride() : weapon1;
	}

	if (final2->m_heightFactorAt0x3ec <= BfmeZeroRange)
		return true;

	Real preferredHeight = ((const Object *)current)->bfmeGetNonnegativePreferredLocomotorHeight();
	Real speed = ai->getCurLocomotorSpeed();
	Real product = speed * final2->m_heightFactorAt0x3ec;

	return !(product > preferredHeight);
}
