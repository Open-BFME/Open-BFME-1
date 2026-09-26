// ?bfmeFlush15@SkirmishScreenState@@QAEXXZ
// partial score=0.93 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

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

class SkirmishScreenState
{
public:
	unsigned char m_vtable[4];
	void rva00525080(int index, int state);
	void setSlotState(int index, int state);
	void bfmeFlush15(void);

private:
	SkirmishScreenOwner *m_owner;
	GameInfo *m_firstGame;
	GameInfo *m_secondGame;
	unsigned char m_unmodelled10[0xB8];
	void *m_playerTemplateCombos[8];
};

#pragma comment(linker, "/alternatename:?setSlotState@SkirmishScreenState@@QAEXHH@Z=?j_0002bedb@@YAXXZ")

void GadgetComboBoxSetSelectedPos(void *window, int item, bool dontHide);

void SkirmishScreenState::bfmeFlush15(void)
{
	register SkirmishScreenState *self = this;
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
	register int numPlayers = 0;
	for (register int index = 0; index < 8; ++index)
	{
		slot = self->m_firstGame->getSlot(index);
		if (slot && !slot->isAI() && !slot->isOpen() &&
			slot->isHuman() && slot->m_playerTemplate != -2)
			++numPlayers;
	}

	if (numPlayers > map->m_numPlayers)
	{
		for (register int index = 7; numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isOpen())
			{
				self->rva00525080(index, SLOT_CLOSED);
				--numPlayers;
			}
		}
		for (register int index = 7; numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isOpen())
			{
					self->rva00525080(index, SLOT_CLOSED);
				--numPlayers;
			}
		}
		for (register int index = 7; numPlayers > map->m_numPlayers; --index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isHuman() && slot->m_playerTemplate == -2)
			{
				self->setSlotState(index, -2);
				--numPlayers;
			}
		}
	}
	else if (numPlayers < map->m_numPlayers)
	{
		for (register int index = 0; numPlayers < map->m_numPlayers && index < 8; ++index)
		{
			slot = self->m_firstGame->getSlot(index);
			if (slot && slot->isHuman() && slot->m_playerTemplate == -2)
			{
				GadgetComboBoxSetSelectedPos(self->m_playerTemplateCombos[index], 0, false);
				++numPlayers;
			}
		}
		for (register int index = 0; numPlayers < map->m_numPlayers && index < 8; ++index)
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
