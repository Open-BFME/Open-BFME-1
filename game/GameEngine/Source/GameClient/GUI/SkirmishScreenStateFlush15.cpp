// ?bfmeFlush15@SkirmishScreenState@@QAEXXZ
// Retail extent and matched-caller identity: identity_evidence/005260f0-slot-predicates.md
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

class GameSlot
{
public:
	unsigned char m_vtable[4];
	unsigned char m_unmodelled04[0x10];
	int m_playerTemplate;

	bool isAI(void) const;
	bool isOpen(void) const;
	bool isHuman(void) const;
};

class GameInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;

	AsciiString getMap(void) const;
	GameSlot *getSlot(int index);
};

class MapMetaData
{
private:
	unsigned char m_unmodelled00[0x20];

public:
	int m_numPlayers;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class SkirmishScreenOwner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual bool contains(GameInfo *game) = 0;
};

class GameWindow;
class Rva00525080SkirmishScreenState { public: void rva00525080(int index, int state); };
class Rva00523460Owner { public: void rva00523460(int index, int data); };

class SkirmishScreenState
{
public:
	unsigned char m_vtable[4];
	void bfmeFlush15(void);
	// Preserve the bank's local adapter name; bind its call to the proven body.
	void setSlotState(int index, int state)
	{ ((Rva00523460Owner *)this)->rva00523460(index, state); }

private:
	SkirmishScreenOwner *m_owner;
	GameInfo *m_firstGame;
	GameInfo *m_secondGame;
	unsigned char m_unmodelled10[0xB8];
	GameWindow *m_playerTemplateCombos[8];
};


void GadgetComboBoxSetSelectedPos(GameWindow *window, int item, bool dontHide);

void SkirmishScreenState::bfmeFlush15(void)
{
	SkirmishScreenState *self = this;
	if (self->m_firstGame && !self->m_owner->contains(self->m_firstGame))
		self->m_firstGame = 0;

	if (self->m_secondGame && !self->m_owner->contains(self->m_secondGame))
		self->m_secondGame = 0;

	if (!self->m_firstGame)
		return;

	const MapMetaData *map = TheMapCache->findMap(self->m_firstGame->getMap());
	if (!map)
		return;

	GameSlot *slot = 0;
	int numPlayers = 0;
	for (int index = 0; index < 8; ++index)
	{
		slot = self->m_firstGame->getSlot(index);
		if (slot && (slot->isAI() || slot->isOpen() ||
			(slot->isHuman() && slot->m_playerTemplate != -2)))
			++numPlayers;
	}

	if (numPlayers > map->m_numPlayers)
	{
		for (int index = 7; index >= 0 && numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isOpen())
			{
				((Rva00525080SkirmishScreenState *)self)->rva00525080(index, SLOT_CLOSED);
				--numPlayers;
			}
		}
		for (int index = 7; index >= 0 && numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isAI())
			{
					((Rva00525080SkirmishScreenState *)self)->rva00525080(index, SLOT_CLOSED);
				--numPlayers;
			}
		}
		for (int index = 7; index >= 0 && numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isHuman() && slot->m_playerTemplate != -2)
			{
				self->setSlotState(index, -2);
				--numPlayers;
			}
		}
	}
	else if (numPlayers < map->m_numPlayers)
	{
		for (int index = 0; index < 8 && numPlayers < map->m_numPlayers; ++index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isHuman() && slot->m_playerTemplate == -2)
			{
				GadgetComboBoxSetSelectedPos(self->m_playerTemplateCombos[index], 0, false);
				++numPlayers;
			}
		}
		for (int index = 0; index < 8 && numPlayers < map->m_numPlayers; ++index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && !slot->isOpen() && !slot->isAI() && !slot->isHuman())
			{
				GadgetComboBoxSetSelectedPos(self->m_playerTemplateCombos[index], 0, false);
				++numPlayers;
			}
		}
	}
}
