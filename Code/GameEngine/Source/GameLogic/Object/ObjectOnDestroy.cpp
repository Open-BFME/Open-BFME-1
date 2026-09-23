// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Object::onDestroy, retail 0x001C6D00, 194 bytes.
// The Zero Hour twin (GameLogic/Object/Object.cpp Object::onDestroy) opens with
// the same containment farewell (m_containedBy->getContain()->removeFromContain)
// and ends with the same m_behaviors onDelete walk (BehaviorModule slot 8).
// BFME inserts the power-influence release (controlling player of the current
// team or of m_originalTeamName) and the five Drawable forward4125F0 calls.
// m_status is the BitFlags<86> status mask the layout witness places at
// Object+0x90 (matched GameLogic::destroyObject 0x0038B0C0 reads it there);
// the tested bit 61 lives in its second dword.
// Object vtable 0x0109EE58 slot 9 reaches this body through ILT 0x0001E295,
// and the matched GameLogic::destroyObject ends with that +0x24 call, as the
// Zero Hour destroyObject ends with obj->onDestroy().

typedef bool Bool;

#include "ascii_string.h"

class Object;

class Player
{
public:
	void bfmeObjectLeavingInfluence(Object *object); // retail ILT 0x0000EACA
};

class Team
{
public:
	Player *getControllingPlayer() const; // retail ILT 0x0002369B -> 0x000EC8F0
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name); // retail ILT 0x000273EF -> 0x000F8290
};

extern TeamFactory *TheTeamFactory; // VA 0x012ED810

class Drawable
{
public:
	void forward4125F0(int slot, Bool flag); // retail ILT 0x00039BAD
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits) = 0;
};

class BehaviorModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void onDelete() = 0;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void onDestroy(); // slot 9: GameLogic::destroyObject 0x0038B0C0 calls +0x24
	virtual Drawable *getDrawable() const = 0; // slot 10, 0x001BE440

	BehaviorModule **getBehaviorModules() { return m_behaviors; }
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	unsigned char m_pad004[0x8c];
	unsigned int m_status[3];
	unsigned char m_pad09c[0x154];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[0x08];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x14];
	Object *m_containedBy;
	unsigned char m_pad218[0x24];
	Team *m_team;
	AsciiString m_originalTeamName;
	unsigned char m_pad244[0x158];
	Bool m_byte39C;
};

void Object::onDestroy()
{
	// Zero Hour Object::onDestroy spells the containment guard through the
	// inline getContain() accessor; that spelling is what gives MSVC 7.1
	// retail's register schedule (behavior walk in ESI, not the dying EDI).
	if (m_containedBy && m_containedBy->getContain())
		m_containedBy->getContain()->removeFromContain(this, false);

	if (m_byte39C)
	{
		Player *player = m_team ? m_team->getControllingPlayer() : 0;
		if ((m_status[1] & 0x20000000) != 0)
		{
			Team *originalTeam = TheTeamFactory->findTeam(m_originalTeamName);
			if (originalTeam)
				player = originalTeam->getControllingPlayer();
		}
		if (player)
		{
			player->bfmeObjectLeavingInfluence(this);
			m_byte39C = false;
		}
	}

	Drawable *drawable = getDrawable();
	if (drawable)
	{
		for (int slot = 1; slot < 6; ++slot)
			drawable->forward4125F0(slot, true);
	}

	for (BehaviorModule **module = m_behaviors; *module; ++module)
		(*module)->onDelete();
}
