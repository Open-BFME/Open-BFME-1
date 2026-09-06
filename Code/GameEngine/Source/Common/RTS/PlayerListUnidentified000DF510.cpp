// cl: /O2
//
// PlayerList method, unidentified. Retail body at RVA 0x000DF510 (107B) sits
// directly between two other real PlayerList methods (getEachPlayerFromMask
// 0x000DF4A0 and getPlayersMask 0x000DF6F0) and its `this` object matches
// PlayerList's established field layout (m_players[32] at +0x14) exactly,
// so the owning class is not in doubt even though the method's real name is.
//
// Sole caller (BfmePlayerMapState::bfmeNewMap, 0x000C7A30) passes a literal
// bool argument and feeds the int result into a `cmp eax,7/5/4/3` bucket
// cascade selecting a start-position table row, i.e. this counts something
// about the currently-eligible players.
//
// Loops i=0..31 via the same inlined getNthPlayer(i) bounds check used by
// the already-matched getPlayersMask.cpp (hence the redundant i<0 test that
// a plain `i<32` for-loop alone would not produce). Per non-null player it
// calls three already-matched byte/bool getters -- Rva000C9D40::get() (an
// indirect byte read through +4, already matched at 0x000C9D40),
// Rva000C9D00::get() (a direct byte read at +0x680, already matched at
// 0x000C9D00) and Player::isPlayerObserver() (already matched at
// 0x000C9CF0) -- to decide whether the player counts at all. When it does,
// and the incoming bool is true, it additionally adds two ints living at
// player+0x40 and player+0x44 into the running total; either way the count
// itself always increments. Those two ints' real field names are not
// established -- only their offsets, from the raw instruction operands.

typedef int Int;

class Rva000C9D40
{
public:
	int get();
};

class Rva000C9D00
{
public:
	unsigned char get();
};

class Rva00DF510PlayerFields
{
public:
	char m_pad[0x10];
	int m_at10;
	int m_at14;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool isPlayerObserver() const;

	Rva00DF510PlayerFields *getRva00DF510Fields()
	{
		return (Rva00DF510PlayerFields *)((char *)this + 0x30);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	int unidentified_000df510(bool includeFields);

	Player *getNthPlayer(Int i)
	{
		if (i < 0 || i >= 32)
			return 0;
		return m_players[i];
	}

private:
	unsigned char m_pad[0x10];
	Int m_playerCount;
	Player *m_players[32];
};

int PlayerList::unidentified_000df510(bool includeFields)
{
	int total = 0;
	for (Int i = 0; i < 32; ++i)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;
		if (!(unsigned char)((Rva000C9D40 *)player)->get())
			continue;
		if (((Rva000C9D00 *)player)->get())
			continue;
		if (player->isPlayerObserver())
			continue;
		if (includeFields)
		{
			Rva00DF510PlayerFields *fields = player->getRva00DF510Fields();
			if (fields)
				total += fields->m_at10 + fields->m_at14;
		}
		++total;
	}
	return total;
}
