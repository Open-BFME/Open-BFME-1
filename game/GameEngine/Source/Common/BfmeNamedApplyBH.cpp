// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the named apply at retail 0x002F83D0, 62 bytes.  The name is
// handed to the registry by value; nothing happens unless it resolves.

class StringBaseNarrowBH
{
protected:
	StringBaseNarrowBH(const StringBaseNarrowBH &other) throw();

	~StringBaseNarrowBH(void) throw();

	char *m_bfmeNarrowBH;
};

class AsciiStringBH : public StringBaseNarrowBH
{
public:
	AsciiStringBH(const AsciiStringBH &other) throw() : StringBaseNarrowBH(other)
	{
	}

	~AsciiStringBH(void) throw()
	{
	}
};

class BfmeRegistryBH
{
public:
	void *bfmeFindBH(AsciiStringBH name) throw();
};

// retail 0x012ED80C is the game's TheSpecialPowerStore, so the global must carry
// that name and its pointee type.  SpecialPowerStore itself is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h; only the address
// of the global is referenced here, so a forward declaration of the pointee is
// enough and the registry view below is still reached by cast (which emits
// nothing).
class SpecialPowerStore;

extern SpecialPowerStore *TheSpecialPowerStore;	// retail 0x012ED80C

class BfmeSubBH
{
public:
	char m_bfmePadSBH[4];
};

class BfmeTargetBH
{
public:
	char m_bfmePadTBH[0x38];
	BfmeSubBH m_bfmeSubBH;
};

class BfmeApplierBH
{
public:
	void bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();

	void bfmeAddBH(void *owner, const AsciiStringBH &name, BfmeTargetBH *target);
};

void BfmeApplierBH::bfmeAddBH(void *owner, const AsciiStringBH &name,
		BfmeTargetBH *target)
{
	void *found = ((BfmeRegistryBH *)TheSpecialPowerStore)->bfmeFindBH(name);

	if (found != 0)
		bfmeApplyBH(owner, found, &target->m_bfmeSubBH);
}
