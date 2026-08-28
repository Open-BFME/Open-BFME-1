// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	char m_unreconstructed00[ 0x4C ];
	unsigned int m_availableMoney;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva0036BA60Cost
{
public:
	unsigned int costFor( Player *player, int index ) const;
};

class Rva0036BA60PurchaseContext
{
public:
	bool canAfford( Player *player, const Rva0036BA60Cost *cost ) const;

private:
	char m_unreconstructed00[ 8 ];
	Object *m_object;
};

bool Rva0036BA60PurchaseContext::canAfford( Player *player, const Rva0036BA60Cost *cost ) const
{
	Player *controllingPlayer = m_object->getControllingPlayer();
	if( !player )
		return false;
	if( !cost )
		return false;
	if( controllingPlayer != player )
		return false;

	unsigned int availableMoney = player->m_availableMoney;
	return availableMoney >= cost->costFor( player, -1 );
}
