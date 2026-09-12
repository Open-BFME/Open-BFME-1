// cl: /DNDEBUG /MD /EHsc

// Open-BFME: CaveContain::onRemoving, retail 0x00219FA0, 170 bytes.
//
// The CaveContain constructor at 0x00219B90 installs vtable 0x010AAD80 at
// complete-object +0x20.  Its +0x48 slot reaches this body without a this
// adjustment, so the retail receiver is the ContainModuleInterface secondary
// subobject.  The genuine multiple-inheritance declaration below lets MSVC
// select that receiver while `this` keeps its C++ meaning as the complete
// CaveContain object.  The same constructor puts the owning Object pointer at
// complete +0x08 (secondary -0x18), while changeTeamOnAllConnectedCaves at
// 0x00219E80 independently reads m_caveIndex at complete +0xDC.
//
// OpenContain's constructor at 0x002277A0 installs its corresponding secondary
// vtable 0x010AC038 at +0x20; slot +0x48 is ILT 0x00032E61 to body 0x00227DC0.
// This independently identifies the qualified OpenContain::onRemoving call
// and proves that it receives the same secondary pointer.  The primary
// OpenContain vtable calls doUnloadSound through slot +0x54 after the compiler
// adjusts back to the complete object.  Object vtable 0x0109EE58 proves
// getDrawable at +0x28.  The two still-unidentified direct helpers retain
// owner- and RVA-derived member names, preserving their proven receivers and
// ABI without inventing semantics.
//
// campaign=luna36h-20260907;lane=expand03;model=gpt-5.6-sol-ultra

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum DisabledType
{
	DISABLED_HELD = 3
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team;
class Drawable;

class Thing
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;

	void setPosition(const Coord3D *position);

	const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}

private:
	unsigned char m_thingData04[0x34];
	Coord3D m_cachedPos;
};

class Object : public Thing
{
public:
	virtual Drawable *getDrawable() const = 0;

	Bool clearDisabled(DisabledType type);
	void rva001CA2E0();
	void notifyModelConditionChanged();

	Team *getTeam() const
	{
		return m_team;
	}

	void clearGarrisonedModelCondition()
	{
		UnsignedInt value = m_modelConditionBits;
		if ((value & 0x400) != 0)
		{
			m_modelConditionBits = value & ~0x400;
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_objectData44[0x110 - 0x44];
	UnsignedInt m_modelConditionBits;
	unsigned char m_objectData114[0x23C - 0x114];
	Team *m_team;
};

typedef char ObjectLayoutMustReach240[(sizeof(Object) == 0x240) ? 1 : -1];

class Drawable
{
public:
	void rva00411DD0(Bool hidden);
};

class OpenContainPrimaryBase
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;

protected:
	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_moduleData;
	Object *m_object;
};

class OpenContainBehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class OpenContainUpdateInterface
{
public:
	virtual void updateAnchor() = 0;

private:
	UnsignedInt m_nextCallFrameAndPhase;
	int m_indexInLogic;
	UnsignedInt m_unreconstructed1C;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void onContaining(Object *obj, Bool wasSelected) = 0;
	virtual void onRemoving(Object *obj) = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
};

template <int Offset>
class OpenContainAuxiliaryInterface
{
public:
	virtual void auxiliaryAnchor() = 0;
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainBehaviorInterface,
	  public OpenContainUpdateInterface,
	  public ContainModuleInterface,
	  public OpenContainAuxiliaryInterface<0x24>,
	  public OpenContainAuxiliaryInterface<0x28>,
	  public OpenContainAuxiliaryInterface<0x2C>,
	  public OpenContainAuxiliaryInterface<0x30>,
	  public OpenContainAuxiliaryInterface<0x34>
{
public:
	virtual void doUnloadSound();
	virtual void onRemoving(Object *obj);
	virtual UnsignedInt getContainCount(Bool countRiders) const;

protected:
	using OpenContainPrimaryBase::getObject;

private:
	unsigned char m_openContainData[0x9C];
};

typedef char OpenContainSizeMustBeD4[(sizeof(OpenContain) == 0xD4) ? 1 : -1];

class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class __declspec(novtable) CaveContain : public OpenContain, public CaveInterface
{
public:
	virtual void onRemoving(Object *obj);
	virtual UnsignedInt getContainCount(Bool countRiders) const;

	void changeTeamOnAllConnectedCaves(Team *newTeam, Bool setOriginalTeams);

private:
	Bool m_needToRunOnBuildComplete;
	unsigned char m_fieldAlignment[3];
	int m_caveIndex;
	Team *m_originalTeam;
};

typedef char CaveContainSizeMustBeE4[(sizeof(CaveContain) == 0xE4) ? 1 : -1];

// ?onRemoving@CaveContain@@UAEXPAVObject@@@Z
void CaveContain::onRemoving(Object *obj)
{
	OpenContain::onRemoving(obj);
	obj->clearDisabled(DISABLED_HELD);
	obj->rva001CA2E0();
	obj->setPosition(getObject()->getPosition());

	if (obj->getDrawable() != 0)
		obj->getDrawable()->rva00411DD0(false);

	doUnloadSound();

	if (getContainCount(false) == 0)
	{
		if (obj->getTeam() != 0)
		{
			changeTeamOnAllConnectedCaves(m_originalTeam, false);
			m_originalTeam = 0;
		}

		obj->clearGarrisonedModelCondition();
	}
}
