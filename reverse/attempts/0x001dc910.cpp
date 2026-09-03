// ?query@Rva001DC910PlayerListQuery@@QAEHXZ
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Object at +8, flag dword at +0xC remapped into a 3-bit field, extra byte
// at +0x10. Player index is Player+0x24. Null controlling player returns -1.

class Player
{
public:
	int getPlayerIndex(void) const { return m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class PlayerList
{
public:
	unsigned short lookup(int playerIndex, int flags, int extra);
};

extern PlayerList *ThePlayerList;

class Rva001DC910PlayerListQuery
{
public:
	int query(void);

private:
	unsigned char m_unreconstructed_00[8];
	Object *m_object;
	unsigned int m_flags;
	unsigned char m_extra;
};

int Rva001DC910PlayerListQuery::query(void)
{
	Player *player = m_object->getControllingPlayer();
	if (!player)
		return -1;

	unsigned int flags = m_flags;
	int remapped = 0;
	if (flags & 4)
		remapped = 3;
	if (flags & 1)
		remapped |= 4;
	if (flags & 2)
		remapped |= 8;

	int index = player->getPlayerIndex();
	unsigned int extra = 0;
	extra = m_extra;
	return ThePlayerList->lookup(index, remapped, extra);
}
