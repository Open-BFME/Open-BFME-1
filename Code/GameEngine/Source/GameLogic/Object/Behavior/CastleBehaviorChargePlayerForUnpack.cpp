// ?chargePlayerForUnpack@CastleBehavior@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	const char *str() const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

private:
	void *m_data;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, bool playSound);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_00[0x28];
	AsciiString m_playerName;
	unsigned char m_unmodelled_2c[0x48 - 0x2c];
	Money m_money;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
	CastleUnpackCostMap m_castleToUnpackForFaction;
};

class CastleBehavior
{
public:
	void chargePlayerForUnpack();

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0c[0xb4 - 0x0c];
	Real m_unpackedCost;
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
