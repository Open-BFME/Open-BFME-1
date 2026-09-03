// ?canPlayerAffordUnpack@CastleBehavior@@QBE_NPAVPlayer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_00[0x4c];
	unsigned int m_moneyAmount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

class CastleBehavior
{
public:
	Bool canPlayerAffordUnpack(Player *player) const;
	unsigned int getUnpackCost(Player *player) const;

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

Bool CastleBehavior::canPlayerAffordUnpack(Player *player) const
{
	Player *controllingPlayer = m_object->getControllingPlayer();
	if (!player)
		return false;
	if (controllingPlayer != player)
		return false;

	unsigned int moneyAmount = player->m_moneyAmount;
	return moneyAmount >= getUnpackCost(player);
}
