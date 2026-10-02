// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the name resolve at retail 0x002DAE80, 42 bytes.  The stored
// name is copied into the by-value argument slot the registry lookup takes,
// so the callee owns it and no unwind frame is emitted.

class StringBaseNarrowAS
{
protected:
	StringBaseNarrowAS(const StringBaseNarrowAS &other);

	~StringBaseNarrowAS(void);

	char *m_bfmeNarrowAS;
};

class AsciiStringAS : public StringBaseNarrowAS
{
public:
	AsciiStringAS(const AsciiStringAS &other) : StringBaseNarrowAS(other)
	{
	}

	~AsciiStringAS(void)
	{
	}
};

class BfmeRegistryAS
{
public:
	void *bfmeFindAS(AsciiStringAS name);
};

// Retail global at 0x012EF738 is EA's WeaponStore singleton, defined once in
// game/GameEngine/Source/GameLogic/Object/Weapon.cpp; this TU keeps its own
// BfmeRegistryAS view and applies it at the use. Only ever used as a pointee,
// so a forward declaration is enough (the definition lives in
// Common/System/game_engine_subsystems.h).
class WeaponStore;

extern WeaponStore *TheWeaponStore;

class BfmeResolverAS
{
public:
	void bfmeRefreshAS(void);

	void bfmeResolveAS(void);

	char m_bfmePadAAS[0x58];
	void *m_bfmeResultAS;
	char m_bfmePadBAS[4];
	AsciiStringAS m_bfmeNameAS;
};

void BfmeResolverAS::bfmeResolveAS(void)
{
	bfmeRefreshAS();

	m_bfmeResultAS = ((BfmeRegistryAS *)TheWeaponStore)->bfmeFindAS(m_bfmeNameAS);
}
