// ?getUnpackCost@CastleBehavior@@QBEIPAVPlayer@@@Z
// ?canPlayerAffordUnpack@CastleBehavior@@QBE_NPAVPlayer@@@Z
// ?chargePlayerForUnpack@CastleBehavior@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// stlport
//
// Open-BFME: what unpacking a castle costs, whether the player can pay it, and
// taking the money.
//
//   ?chargePlayerForUnpack@  0x0036F0A0, 216 bytes
//   ?getUnpackCost@          0x0036F750, 307 bytes
//   ?canPlayerAffordUnpack@  0x0036F8D0,  51 bytes
//
// One question in three steps, and they read the same INI table to answer it:
// CastleBehaviorModuleData's faction map at +0x6C, keyed by the player's name,
// holding a cost and a minimum-money floor. getUnpackCost looks the entry up and
// returns 0x05F5E0FF -- 99,999,999, an "impossible" price rather than a refusal
// -- when the player is below that floor. canPlayerAffordUnpack compares the
// player's money against whatever that returns, so the sentinel is what makes
// the floor bite. chargePlayerForUnpack looks the SAME entry up again and
// withdraws the cost, and it does not consult the floor at all.
//
// THE MONEY. Three files, three different accounts of where a Player keeps it,
// and this is the merge's whole point:
//
//   +0x30  getUnpackCost calls m_money.get(0) on a two-field holder whose
//          callee is 0x000C7C30.
//   +0x48  chargePlayerForUnpack calls Money::withdraw on an object here.
//   +0x4C  canPlayerAffordUnpack reads a bare unsigned int here.
//
// The last two reconcile: +0x4C is four bytes into the object at +0x48, so the
// bare read is that object's amount field and canPlayerAffordUnpack was reading
// Money's insides without a name for them. That is how it is written below.
// The holder at +0x30 does NOT reconcile with either -- it is a different
// object, 0x18 bytes earlier, reached through a different callee -- so it keeps
// its own name and its own slot, and which of the two is "the" player's money is
// left open rather than guessed. A caller of 0x000C7C30 would settle it.
//
// The player name is at +0x28 in both files that read it. (A fourth
// CastleBehavior file, isPlayerAllowedToCapture, declares it at +0x1C and never
// reads it -- filler of the right width, the same shape as the AIGroup+0x0C
// m_speed that the AIGroup constructor disproved.)

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
private:
	struct SharedBuffer
	{
		unsigned int m_refCount;
		unsigned short m_length;
	};

	SharedBuffer *m_buffer;

public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

	Bool isEmpty() const
	{
		return m_buffer == 0 || m_buffer->m_length == 0;
	}

	const char *str() const
	{
		return m_buffer ? (const char *)((unsigned char *)m_buffer + 8) : "";
	}
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// The retail callee at 0x000C7C30 is the two-field value used by Player's money
// object. Its one argument is intentionally unused by the body.
class Rva000C7C30Holder
{
public:
	Int get(Int unused) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, bool playSound);

	unsigned char m_unmodelled_00[4];
	UnsignedInt m_amount;				// Player+0x4C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_00[0x28];
	AsciiString m_playerName;			// +0x28
	unsigned char m_unmodelled_2c[4];
	Rva000C7C30Holder m_moneyHolder;		// +0x30, callee 0x000C7C30
	unsigned char m_unmodelled_34[0x48 - 0x34];
	Money m_money;					// +0x48
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

struct CastleUnpackCost
{
	Int m_unmodelled_00;
	UnsignedInt m_cost;
	Int m_minimumMoney;
};

typedef _STL::map<NameKeyType, CastleUnpackCost> CastleUnpackCostMap;

class CastleBehaviorModuleData
{
public:
	unsigned char m_unmodelled_00[0x6c];
	CastleUnpackCostMap m_castleToUnpackForFaction;	// +0x6C
};

class CastleBehavior
{
public:
	void chargePlayerForUnpack();
	UnsignedInt getUnpackCost(Player *player) const;
	Bool canPlayerAffordUnpack(Player *player) const;

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;		// +0x04
	Object *m_object;				// +0x08
	unsigned char m_unmodelled_0c[0xb4 - 0x0c];
	Real m_unpackedCost;				// +0xB4
};

// ?chargePlayerForUnpack@CastleBehavior@@QAEXXZ
void CastleBehavior::chargePlayerForUnpack()
{
	CastleBehaviorModuleData *data = m_moduleData;
	if (!m_object)
		return;

	Player *player = m_object->getControllingPlayer();
	if (!player)
		return;

	AsciiString playerName(player->m_playerName);
	NameKeyType playerKey = TheNameKeyGenerator->nameToKey(playerName.str());
	CastleUnpackCostMap::iterator it = data->m_castleToUnpackForFaction.find(playerKey);
	if (it != data->m_castleToUnpackForFaction.end())
	{
		UnsignedInt cost = it->second.m_cost;
		player->m_money.withdraw(cost, true);
		m_unpackedCost = (Real)cost;
	}
}

// ?getUnpackCost@CastleBehavior@@QBEIPAVPlayer@@@Z
UnsignedInt CastleBehavior::getUnpackCost(Player *player) const
{
	if (player == 0)
		return 0;

	AsciiString playerName(player->m_playerName);
	if (playerName.isEmpty())
		return 0;
	else
	{
		CastleBehaviorModuleData *data;
		CastleUnpackCostMap *map;
		NameKeyType key = TheNameKeyGenerator->nameToKey(playerName.str());
		const NameKeyType &keyReference = key;
		data = m_moduleData;
		map = &data->m_castleToUnpackForFaction;
		CastleUnpackCostMap::iterator it = map->find(keyReference);
		if (it != map->end())
		{
			Int minimumMoney = it->second.m_minimumMoney;
			if (minimumMoney > 0 && player->m_moneyHolder.get(0) < minimumMoney)
				return 0x05F5E0FF;

			return it->second.m_cost;
		}
	}

	return 0;
}

// ?canPlayerAffordUnpack@CastleBehavior@@QBE_NPAVPlayer@@@Z
Bool CastleBehavior::canPlayerAffordUnpack(Player *player) const
{
	Player *controllingPlayer = m_object->getControllingPlayer();
	if (!player)
		return false;
	if (controllingPlayer != player)
		return false;

	unsigned int moneyAmount = player->m_money.m_amount;
	return moneyAmount >= getUnpackCost(player);
}
