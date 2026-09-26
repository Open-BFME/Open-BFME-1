// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: CaveContain::recalcApparentControllingPlayer, retail 0x0021A100.
//
// The retail entry is the ContainModuleInterface secondary subobject.  The
// CaveContain constructor at 0x00219B90 installs vtable 0x010AAD80 at complete
// object +0x20; that table's +0x40 slot is the unadjusted ILT jump 0x00016D7E
// to this body.  The genuine multiple-inheritance declaration below lets MSVC
// select that secondary receiver for the override while `this` retains its C++
// meaning as the complete CaveContain object.  Thus direct m_originalTeam
// accesses become secondary +0xC0, inherited getObject() reaches complete
// +0x08 (secondary -0x18), and the nonvirtual changeTeamOnAllConnectedCaves
// call gets the compiler's complete-object adjustment of -0x20.  Its retail
// body at 0x00219E80 independently reads m_caveIndex at complete +0xDC.
//
// Object vtable 0x0109EE58 slot +0x28 reaches the matched getDrawable body.
// InGameUI::placeBuildAvailable at 0x0043AF60 independently uses GlobalData
// +0x218 and Player +0x1C4/+0x1C8 for the same day/night indicator-color flow.
// True-MI correction: model=gpt-5.6-sol-ultra;campaign=luna36h-20260907;lane=expand03.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef Int Color;

enum TimeOfDay
{
	TIME_OF_DAY_NIGHT = 4
};

class Team;
class Player;
class Drawable;
class Object;

typedef _STL::list<Object *> ContainedItemsList;

class Player
{
public:
	Color getPlayerColor() const
	{
		return m_playerColor;
	}

	Color getPlayerNightColor() const
	{
		return m_playerNightColor;
	}

	Team *getDefaultTeam() const
	{
		return m_defaultTeam;
	}

private:
	unsigned char m_pad0[0x1C4];
	Color m_playerColor;
	Color m_playerNightColor;
	unsigned char m_pad1[0x230 - 0x1CC];
	Team *m_defaultTeam;
};

class Object
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
	virtual Drawable *getDrawable() const = 0;

	Player *getControllingPlayer() const;

	Team *getTeam() const
	{
		return *reinterpret_cast<Team *const *>(reinterpret_cast<const char *>(this) + 0x23C);
	}
};

class Drawable
{
public:
	void setIndicatorColor(Color color);
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return m_localPlayer;
	}

private:
	unsigned char m_pad[0x0C];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class GlobalData
{
private:
	unsigned char m_pad[0x218];

public:
	TimeOfDay m_timeOfDay;
};

extern GlobalData *TheGlobalData;

// Retail CaveContain uses OpenContain's genuine multiple-inheritance layout.
// The primary module base contains the module-data and owning-Object pointers;
// the ContainModuleInterface base begins at complete-object +0x20.
class OpenContainPrimaryBase
{
public:
	virtual void primaryAnchor() = 0;

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
	Int m_indexInLogic;
	UnsignedInt m_unreconstructed1C;
};

class ContainModuleInterface
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0C() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1C() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void pad28() = 0;
	virtual void pad2C() = 0;
	virtual void pad30() = 0;
	virtual void pad34() = 0;
	virtual void pad38() = 0;
	virtual const Player *getApparentControllingPlayer(const Player *) const = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void pad44() = 0;
	virtual void pad48() = 0;
	virtual void pad4C() = 0;
	virtual void pad50() = 0;
	virtual void pad54() = 0;
	virtual void pad58() = 0;
	virtual void pad5C() = 0;
	virtual void pad60() = 0;
	virtual void pad64() = 0;
	virtual void pad68() = 0;
	virtual void pad6C() = 0;
	virtual void pad70() = 0;
	virtual void pad74() = 0;
	virtual void pad78() = 0;
	virtual void pad7C() = 0;
	virtual void pad80() = 0;
	virtual void pad84() = 0;
	virtual void pad88() = 0;
	virtual void pad8C() = 0;
	virtual void pad90() = 0;
	virtual void pad94() = 0;
	virtual void pad98() = 0;
	virtual void pad9C() = 0;
	virtual void padA0() = 0;
	virtual void padA4() = 0;
	virtual void padA8() = 0;
	virtual void padAC() = 0;
	virtual void padB0() = 0;
	virtual void padB4() = 0;
	virtual void padB8() = 0;
	virtual void padBC() = 0;
	virtual void padC0() = 0;
	virtual void padC4() = 0;
	virtual void padC8() = 0;
	virtual void padCC() = 0;
	virtual void padD0() = 0;
	virtual void padD4() = 0;
	virtual void padD8() = 0;
	virtual void padDC() = 0;
	virtual void padE0() = 0;
	virtual void padE4() = 0;
	virtual void padE8() = 0;
	virtual void padEC() = 0;
	virtual void padF0() = 0;
	virtual void padF4() = 0;
	virtual void padF8() = 0;
	virtual void padFC() = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
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
	virtual const Player *getApparentControllingPlayer(const Player *) const;
	virtual void recalcApparentControllingPlayer();
	virtual UnsignedInt getContainCount(Bool countRiders) const;
	virtual const ContainedItemsList *getContainedItemsList() const;

protected:
	using OpenContainPrimaryBase::getObject;

private:
	unsigned char m_openContainData[0x9C];
};

typedef char OpenContainSizeMustBeD4[(sizeof(OpenContain) == 0xD4) ? 1 : -1];

class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(Int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class __declspec(novtable) CaveContain : public OpenContain, public CaveInterface
{
public:
	virtual void recalcApparentControllingPlayer();
	virtual UnsignedInt getContainCount(Bool countRiders) const;
	virtual const ContainedItemsList *getContainedItemsList() const;

	void changeTeamOnAllConnectedCaves(Team *, Bool);

private:
	Bool m_needToRunOnBuildComplete;
	unsigned char m_fieldAlignment[3];
	Int m_caveIndex;
	Team *m_originalTeam;
};

typedef char CaveContainSizeMustBeE4[(sizeof(CaveContain) == 0xE4) ? 1 : -1];

// ?recalcApparentControllingPlayer@CaveContain@@UAEXXZ
void CaveContain::recalcApparentControllingPlayer()
{
	if (m_originalTeam == 0)
		m_originalTeam = getObject()->getTeam();

	if (getObject()->getTeam() == 0)
		m_originalTeam = 0;

	if (getContainCount(false) == 1)
	{
		ContainedItemsList::const_iterator it = getContainedItemsList()->begin();
		Object *rider = *it;
		if (rider->getControllingPlayer() != 0)
			changeTeamOnAllConnectedCaves(
				rider->getControllingPlayer()->getDefaultTeam(), true);
	}
	else if (getContainCount(false) == 0)
	{
		changeTeamOnAllConnectedCaves(m_originalTeam, false);
	}

	const Player *controller =
		getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
	if (controller != 0)
	{
		if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
		{
			Color indicatorColor = controller->getPlayerNightColor();
			getObject()->getDrawable()->setIndicatorColor(indicatorColor);
		}
		else
		{
			Color indicatorColor = controller->getPlayerColor();
			getObject()->getDrawable()->setIndicatorColor(indicatorColor);
		}
	}
}
