// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the two-name resolve at retail 0x002DE300, 73 bytes.  The first
// name always goes to its registry by value; the second only when it is set,
// and that one goes by reference.

class StringBaseNarrowBN
{
protected:
	StringBaseNarrowBN(const StringBaseNarrowBN &other) throw();

	~StringBaseNarrowBN(void) throw();

	char *m_bfmeNarrowBN;
};

class AsciiStringBN : public StringBaseNarrowBN
{
public:
	AsciiStringBN(const AsciiStringBN &other) throw() : StringBaseNarrowBN(other)
	{
	}

	~AsciiStringBN(void) throw()
	{
	}

	bool bfmeEmptyBN(void) const
	{
		return (m_bfmeNarrowBN == 0) || (*(const unsigned short *)(m_bfmeNarrowBN + 4) == 0);
	}
};

class BfmeRegistryBN
{
public:
	void *bfmeFindBN(AsciiStringBN name) throw();
};

class BfmeOtherBN
{
public:
	void *bfmeLookupBN(const AsciiStringBN &name) throw();
};

// Retail global 0x012EF738 is EA's WeaponStore singleton, defined once in
// game/GameEngine/Source/GameLogic/Object/Weapon.cpp; this TU keeps its own
// BfmeRegistryBN view and applies it at the use. Only ever used as a pointee,
// so a forward declaration is enough (the definition lives in
// Common/System/game_engine_subsystems.h).
class WeaponStore;

extern WeaponStore *TheWeaponStore;		// retail 0x012EF738

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp; this TU keeps its own BfmeOtherBN view of it.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class BfmeResolverBN
{
public:
	void bfmeRefreshBN(void);

	void bfmeResolveBN(void);

	char m_bfmePadBN[0x58];
	void *m_bfmeFirstBN;
	void *m_bfmeSecondBN;
	AsciiStringBN m_bfmeNameBN;
	AsciiStringBN m_bfmeOtherNameBN;
};

void BfmeResolverBN::bfmeResolveBN(void)
{
	bfmeRefreshBN();

	m_bfmeFirstBN = ((BfmeRegistryBN *)TheWeaponStore)->bfmeFindBN(m_bfmeNameBN);

	if (!m_bfmeOtherNameBN.bfmeEmptyBN())
		m_bfmeSecondBN = ((BfmeOtherBN *)TheThingFactory)->bfmeLookupBN(m_bfmeOtherNameBN);
}
