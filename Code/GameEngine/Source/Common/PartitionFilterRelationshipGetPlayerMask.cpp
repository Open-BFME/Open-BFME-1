// cl: /DNDEBUG /MD /EHs-c-
// PartitionFilterRelationship layout: Object* at +8, relationship flags at +0xC,
// extra bool at +0x10. Flags remap PartitionFilterRelationship::ALLOW_* into
// AllowPlayerRelationship for PlayerList::getPlayersWithRelationship.

typedef unsigned short PlayerMaskType;

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
	PlayerMaskType getPlayersWithRelationship(int playerIndex, int flags, bool extra);
};

extern PlayerList *ThePlayerList;

class PartitionFilterRelationship
{
public:
	int getPlayerMask(void);

private:
	unsigned char m_unreconstructed_00[8];
	Object *m_obj;
	unsigned int m_flags;
	bool m_extra;
};

int PartitionFilterRelationship::getPlayerMask(void)
{
	Player *player = m_obj->getControllingPlayer();
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
	return ThePlayerList->getPlayersWithRelationship(index, remapped, m_extra);
}
