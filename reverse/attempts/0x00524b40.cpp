// ?Rva00524B40Tooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.96 date=2026-09-20
// cl: /DNDEBUG /MD

class GameWindow
{
public:
	void *winGetUserData();
};

class WinInstanceData;
class GameSlot;

class GameInfo
{
public:
	GameSlot *getSlot(int index);
};

class MpGameSetupOwner
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual void slot3(void) = 0;
	virtual void slot4(void) = 0;
	virtual void slot5(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual bool contains(GameInfo *game) = 0;
	virtual void slot10(void) = 0;
	virtual void updateSlot(GameSlot *slot) = 0;
};

class MpGameSetup
{
public:
	unsigned char m_unmodelled000[4];
	MpGameSetupOwner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled010[0x58];
	GameWindow *m_player[8];
};

void Rva00524B40Tooltip(GameWindow *window, WinInstanceData *, unsigned int)
{
	if (*(MpGameSetup **)0x012F49D4 == 0)
		return;

	int playerIndex = 0;
	int offset = 0x68;
	do
	{
		if (window != 0)
		{
			GameWindow *player = *(GameWindow **)(
				(char *)*(MpGameSetup **)0x012F49D4 + offset);
		void *data = player->winGetUserData();
		if (data != 0)
		{
			data = *(void **)((char *)data + 0x28);
			if (data != 0)
				goto compare;
		}
		data = 0;
	compare:
		if (window == data)
			goto cleanup;
		}

		offset += 4;
		++playerIndex;
	}
	while (offset < 0x88);
	return;

cleanup:
	if (playerIndex == -1)
		return;

	MpGameSetup *setup = *(MpGameSetup **)0x012F49D4;
	GameInfo *first = setup->m_first;
	if (first && !setup->m_owner->contains(first))
		setup->m_first = 0;
	if (setup->m_second && !setup->m_owner->contains(setup->m_second))
		setup->m_second = 0;

	if (setup->m_first)
	{
		GameSlot *slot = setup->m_first->getSlot(playerIndex);
		if (slot)
			setup->m_owner->updateSlot(slot);
	}
}
