// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object last-damage player-index query, retail 0x001BF060,
// 51 bytes. BFME stores BodyModuleInterface at Object +0x200. Its slot 15
// (+0x3C) returns the last DamageInfo; the 16-bit source-player mask is at
// DamageInfo +0x0C. PlayerList::getPlayerFromMask resolves that mask, and the
// returned Player's index is at +0x24. Any missing body, damage record, mask,
// or player returns zero.
//
// SlowDeathBehavior::beginSlowDeath is the only named caller, but it does not
// expose this wrapper's retail spelling. The bfme-prefixed name is deliberately
// descriptive. This no-argument thiscall also cannot prove cv-qualification;
// const records the observed query-only behavior.

typedef int Int;
typedef unsigned short PlayerMaskType;

struct DamageInfoInput
{
	void *m_snapshotVtable;
	unsigned int m_sourceID;
	PlayerMaskType m_sourcePlayerMask;
};

struct DamageInfo
{
	void *m_snapshotVtable;
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual Int bfmeSlot00() = 0; virtual Int bfmeSlot01() = 0;
	virtual Int bfmeSlot02() = 0; virtual Int bfmeSlot03() = 0;
	virtual Int bfmeSlot04() = 0; virtual Int bfmeSlot05() = 0;
	virtual Int bfmeSlot06() = 0; virtual Int bfmeSlot07() = 0;
	virtual Int bfmeSlot08() = 0; virtual Int bfmeSlot09() = 0;
	virtual Int bfmeSlot10() = 0; virtual Int bfmeSlot11() = 0;
	virtual Int bfmeSlot12() = 0; virtual Int bfmeSlot13() = 0;
	virtual Int bfmeSlot14() = 0;
	virtual const DamageInfo *getLastDamageInfo() const = 0; // +0x3C
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_bfmePrefix[0x24];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

extern PlayerList *ThePlayerList;

class Object
{
public:
	Int bfmeGetLastDamagePlayerIndex() const;

private:
	unsigned char m_bfmePrefix[0x200];
	BodyModuleInterface *m_body;
};

// ?bfmeGetLastDamagePlayerIndex@Object@@QBEHXZ
Int Object::bfmeGetLastDamagePlayerIndex() const
{
	BodyModuleInterface *body = m_body;
	if (body != 0)
	{
		const DamageInfo *info = body->getLastDamageInfo();
		if (info != 0 && info->in.m_sourcePlayerMask != 0)
		{
			Player *player = ThePlayerList->getPlayerFromMask(info->in.m_sourcePlayerMask);
			if (player != 0)
				return player->getPlayerIndex();
		}
	}
	return 0;
}
