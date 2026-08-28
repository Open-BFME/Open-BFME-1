// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?setDockCrippled@SupplyWarehouseDockUpdate@@UAEX_N@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp
// Lift the SupplyWarehouseDockUpdate::setDockCrippled naked dump to clean C++.
//
// Zero Hour's SupplyWarehouseDockUpdate.cpp body, unchanged. The base call is
// qualified and appears twice in the bytes because the optimiser duplicated the
// tail rather than jumping to it, which is why the kill path has an epilogue of
// its own.
//
// aiIdle is reached through a pointer adjusted by 0x20, so it is declared in a
// second base of the AI interface rather than the primary one -- the primary
// base carries the vtable that getSupplyTruckAIInterface sits in at +0x144, and
// the command base is non-polymorphic so it stays after it in the layout.
//
// Retail pins the layout: the active docker id is at this+0x60 and the inside
// flag at this+0x64, and the AI pointer is at object+0x204, which agrees with
// the TransportContain conversion done earlier.

typedef int Int;
typedef bool Bool;
typedef Int ObjectID;

enum { INVALID_ID = 0 };
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_AI = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();

	virtual void setForceWantingState(Bool state);		///< vtable +0x2C
};

// Non-polymorphic, so it keeps its place after the primary base and lands at
// +0x20 of the AI interface -- which is the adjustment retail applies.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);			///< ILT thunk at 0x00024D70
};

class AIPrimaryInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual void unused79();
	virtual void unused80();

	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface(void);	///< vtable +0x144

private:
	// this base must occupy 0x20 bytes so the command base lands where retail
	// adjusts to; without it the derived base sits right after the vtable pointer
	unsigned char m_unreconstructed_04[0x20 - 4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIPrimaryInterface, public AICommandInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isUsingAirborneLocomotor(void) const;			///< ILT thunk at 0x0000A001
	void kill(DamageType damageType, DeathType deathType);	///< ILT thunk at 0x00014506

	AIUpdateInterface *getAI(void) { return m_ai; }

private:
	unsigned char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;							///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);				///< ILT thunk at 0x0001F253
};

extern GameLogic *TheGameLogic;							///< retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdate
{
public:
	virtual void setDockCrippled(Bool setting);			///< ILT thunk at 0x0003B912
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h
class SupplyWarehouseDockUpdate : public DockUpdate
{
public:
	virtual void setDockCrippled(Bool setting);

private:
	unsigned char m_unreconstructed_04[0x60 - 4];
	ObjectID m_activeDocker;							///< retail this+0x60
	Bool m_dockerInside;								///< retail this+0x64
};

// ?setDockCrippled@SupplyWarehouseDockUpdate@@UAEX_N@Z
void SupplyWarehouseDockUpdate::setDockCrippled( Bool setting )
{
	// At this level, Crippling means I kill any activeDocker between enter and exit.
	if( setting )
	{
		if( m_activeDocker != INVALID_ID )
		{
			Object *victim = TheGameLogic->findObjectByID( m_activeDocker );
			if( victim )
			{
				if( m_dockerInside )
				{
					if( !victim->isUsingAirborneLocomotor() )
						victim->kill( DAMAGE_UNRESISTABLE, DEATH_NORMAL );
				}
				else
				{
					// Else, he was between Approach and Enter.  Lucky guy.  Tell him to stop, but then
					// remind him that he wants to try again later
					SupplyTruckAIInterface* supplyTruckAI = victim->getAI()->getSupplyTruckAIInterface();
					if( supplyTruckAI )
					{
						victim->getAI()->aiIdle( CMD_FROM_AI );
						supplyTruckAI->setForceWantingState( true );
					}
				}
			}
		}
	}

	DockUpdate::setDockCrippled( setting );
}
