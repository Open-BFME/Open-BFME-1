// ?getUnpackCost@CastleBehavior@@QBEIPAVPlayer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
	AsciiString(const AsciiString &other);
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// The retail callee at 0x000C7C30 is the two-field value used by Player's
// money object.  Its one argument is intentionally unused by the body.
class Rva000C7C30Holder
{
public:
	Int get(Int unused) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_00[0x28];
	AsciiString m_playerName;
	unsigned char m_unmodelled_2c[4];
	Rva000C7C30Holder m_money;
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
	CastleUnpackCostMap m_castleToUnpackForFaction;
};

class CastleBehavior
{
public:
	UnsignedInt getUnpackCost(Player *player) const;

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;
};

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
			if (minimumMoney > 0 && player->m_money.get(0) < minimumMoney)
				return 0x05F5E0FF;

			return it->second.m_cost;
		}
	}

	return 0;
}
