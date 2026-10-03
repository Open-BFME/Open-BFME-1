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

class Rva0036BA60Cost
{
public:
	unsigned int costFor( Player *player, int index ) const;
};

// Retail calls the cost body through the ILT thunk at 0x0000DA8A, owned by
// game/gen_small/thunks_006.cpp as ?j_0000da8a@@YAXXZ.  The thunk is declared
// by that symbol and reached through a member-function pointer so the call keeps
// its thiscall shape (ECX = cost); costFor is never referenced by name.
extern "C" void __cdecl __identifier( "?j_0000da8a@@YAXXZ" )();
typedef unsigned int ( Rva0036BA60Cost::*Rva0036BA60CostForThunk )( Player *player, int index ) const;
union Rva0036BA60CostForThunkRef
{
	void *m_thunk;
	Rva0036BA60CostForThunk m_call;
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

	Rva0036BA60CostForThunkRef thunk;
	thunk.m_thunk = (void *)&__identifier( "?j_0000da8a@@YAXXZ" );
	unsigned int amount = ( cost->*thunk.m_call )( player, -1 );
	player->m_money.withdraw( amount, true );
	return amount;
}
