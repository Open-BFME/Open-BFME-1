// cl: /DNDEBUG /MD /EHsc

extern "C" void *memset(void *destination, int value, unsigned int size);
#pragma intrinsic(memset)

class LANGameSlot
{
public:
	bool isLocalPlayer() const;
};

class LANGameInfo
{
public:
	char m_fields[0x0c];
	bool m_hasLocalPlayer;
	char m_fieldsBeforeSlots[0x58 - 0x0d];
	LANGameSlot m_slots[1];
};

class LANAPI
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void reserved10();
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void reserved24();
	virtual void reserved25();
	virtual void reserved26();
	virtual void reserved27();
	virtual void reserved28();
	virtual void reserved29();
	virtual void reserved30();
	virtual void reserved31();
	virtual void reserved32();
	virtual void reserved33();
	virtual void reserved34();
	virtual void reserved35();
	virtual void reserved36();
	virtual void reserved37();
	virtual void reserved38();
	virtual void reserved39();
	virtual void reserved40();
	virtual void reserved41();
	virtual void reserved42();
	virtual void reserved43();
	virtual void reserved44();
	virtual void reserved45();
	virtual void reserved46();
	virtual void reserved47();
	virtual LANGameInfo *GetMyGame();
};

extern LANAPI *TheLAN;
void writeLANGameInfo(const LANGameInfo *game, char *buffer, unsigned int size);

void fillCurrentLANGameInfo(char *buffer, unsigned int size)
{
	if (TheLAN->GetMyGame() != 0) {
		LANGameInfo *game = TheLAN->GetMyGame();
		if (game->m_hasLocalPlayer && game->m_slots[0].isLocalPlayer()) {
			writeLANGameInfo(TheLAN->GetMyGame(), buffer, size);
			return;
		}
	}

	memset(buffer, 0, size);
}
