// ?chargePlayerForUnpack@CastleBehavior@@QAEXXZ
// partial score=0.98 date=2026-09-03
// ?chargePlayerForUnpack@CastleBehavior@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

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

class NameKeyGenerator
{
public:
	Int nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, bool playSound);
};

class Player
{
public:
	unsigned char m_unmodelled_00[0x28];
	AsciiString m_playerName;
	unsigned char m_unmodelled_2c[0x48 - 0x2c];
	Money m_money;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct CastleUnpackCostNode
{
	unsigned char m_unmodelled_00[0x18];
	UnsignedInt m_cost;
};

struct CastleUnpackCostIterator
{
	CastleUnpackCostIterator(const CastleUnpackCostIterator &other);
	CastleUnpackCostNode *m_node;
};

class CastleUnpackCostMap
{
public:
	CastleUnpackCostIterator find(const Int &key);

	CastleUnpackCostNode *m_header;
};

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
	Int playerKey = TheNameKeyGenerator->nameToKey(playerName.str());
	CastleUnpackCostIterator it = data->m_castleToUnpackForFaction.find(playerKey);
	CastleUnpackCostNode *end = data->m_castleToUnpackForFaction.m_header;
	if (it.m_node != end)
	{
		UnsignedInt cost = it.m_node->m_cost;
		player->m_money.withdraw(cost, true);
		m_unpackedCost = (Real)cost;
	}
}
