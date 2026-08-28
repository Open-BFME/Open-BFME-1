// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SupplyCenterCreate::onBuildComplete, retail 0x002503B0.
//
// The Zero Hour body unchanged. The class is spelled locally in the same shape
// CreateCrateDie.cpp and SpecialPowerCompletionDie.cpp use, because that shape
// is what puts the module interface at object+0x10 -- and the bytes here confirm
// it three separate ways:
//
//   mov eax,[edi] / call [eax+0x8]   slot 2 of CreateModuleInterface, which is
//                                    shouldDoOnBuildComplete against Zero Hour's
//                                    onCreate / onBuildComplete / should... order
//   mov byte [edi+0x4],0             CreateModule::m_needToRunOnBuildComplete at
//                                    object+0x14, i.e. the first member past the
//                                    0x10 base -- this is CreateModule::onBuildComplete
//                                    inlined at the qualified call
//   mov ecx,[edi-0x8]                getObject(), object+0x08
//
// Inlined accessors: PlayerList::getPlayerCount is [this+0x10] and
// Player::getResourceGatheringManager is [this+0x228]. ThePlayerList is retail
// 0x012ED748, and retail reloads it on every iteration of the loop, which is
// what a global read inside the loop body gives.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ResourceGatheringManager.h
class ResourceGatheringManager
{
public:
	void addSupplyCenter( Object *obj );		///< ILT 0x0001E23B
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	ResourceGatheringManager *getResourceGatheringManager( void ) const { return m_resourceGatheringManager; }

private:
	unsigned char m_unreconstructed_00[0x228];
	ResourceGatheringManager *m_resourceGatheringManager;	///< retail this+0x228
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	int getPlayerCount( void ) const { return m_playerCount; }
	Player *getNthPlayer( int i );				///< ILT 0x00044F30

private:
	unsigned char m_unreconstructed_00[0x10];
	int m_playerCount;							///< retail this+0x10
};

extern PlayerList *ThePlayerList;				///< retail 0x012ED748

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

protected:
	Object *getObject( void ) const { return m_obj; }

private:
	const ModuleData *m_moduleData;				///< retail this+0x04
	Object *m_obj;								///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;				///< slot 0
	virtual void onBuildComplete() = 0;			///< slot 1
	virtual bool shouldDoOnBuildComplete() const = 0;	///< slot 2, retail call [eax+0x8]
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public CreateModuleInterface
{
public:
	CreateModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData ),
		  m_needToRunOnBuildComplete( true )
	{
	}

	// Declared, not defined. Zero Hour spells the body inline here and
	// SupplyCenterCreate calls it qualified, which inlines to the single store
	// the retail bytes show. Defining it in this TU would put an unclaimed
	// out-of-line copy in the object, so the store is written at the call site
	// instead and the base keeps only the declaration.
	virtual void onBuildComplete();
	virtual bool shouldDoOnBuildComplete() const { return m_needToRunOnBuildComplete; }

protected:
	bool m_needToRunOnBuildComplete;			///< retail object+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterCreate.h
class SupplyCenterCreate : public CreateModule
{
public:
	SupplyCenterCreate( Thing *thing, const ModuleData *moduleData )
		: CreateModule( thing, moduleData )
	{
	}

	virtual void onBuildComplete( void );
};

// ?onBuildComplete@SupplyCenterCreate@@UAEXXZ
void SupplyCenterCreate::onBuildComplete( void )
{
	if( ! shouldDoOnBuildComplete() )
		return;

	m_needToRunOnBuildComplete = false;	// CreateModule::onBuildComplete(), inlined -- mov byte [edi+4],0

	if( ThePlayerList == 0 )
		return;

	for( int playerIndex = ThePlayerList->getPlayerCount() - 1; playerIndex >= 0; playerIndex-- )
	{
		Player *currentPlayer = ThePlayerList->getNthPlayer( playerIndex );
		if( currentPlayer == 0 )
			continue;
		ResourceGatheringManager *manager = currentPlayer->getResourceGatheringManager();
		if( manager == 0 )
			continue;
		manager->addSupplyCenter( getObject() );
	}
}
