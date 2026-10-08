// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	unsigned int withdraw( unsigned int amount, bool playSound );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	char m_unreconstructed00[ 0x48 ];
	Money m_money;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// Retail calls ILT 0x0000DA8A, which lands on ThingTemplate::calcCostToBuild
// (0x0013E390).
class ThingTemplate
{
public:
	int calcCostToBuild( const Player *player, int index ) const;
};

class Rva0036BA60Cost : public ThingTemplate
{
};

class Rva0036BA60PurchaseContext
{
public:
	unsigned int withdrawPurchaseCost( const Rva0036BA60Cost *cost ) const;

private:
	char m_unreconstructed00[ 8 ];
	Object *m_object;
};

unsigned int Rva0036BA60PurchaseContext::withdrawPurchaseCost( const Rva0036BA60Cost *cost ) const
{
	if( !m_object )
		return 0;

	Player *player = m_object->getControllingPlayer();
	if( !player )
		return 0;

	unsigned int amount = cost->calcCostToBuild( player, -1 );
	player->m_money.withdraw( amount, true );
	return amount;
}
