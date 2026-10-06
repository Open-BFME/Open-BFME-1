// cl: /DNDEBUG /MD /EHsc
// Complete destructor 0x0036BBA0 also emits scalar wrapper 0x0036CF10.
// Constructor 0x0036CEA0 and the wrapper's ILT 0x0003FB89 establish
// this shared class identity. The inherited retail ABI slice is unchanged.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent( unsigned int handle );
};

extern AudioManager *TheAudio;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	unsigned char m_data[ 8 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

struct ModuleInterfaceDispatch { };

extern const ModuleInterfaceDispatch
	g_castleMemberBehaviorModuleInterfaceDispatch;

// The tables restored before ~ObjectModule are BehaviorModule's (0x0109CB5C,
// 0x0109CA98), the pair ~UpdateModule (0x001B2B10) also ends with.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule,
	public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() { }

protected:
	const ModuleInterfaceDispatch *m_moduleInterface;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_audioHandle;
	bool m_24;
	bool m_25;
};

class CastleMemberBehavior : public BehaviorModule
{
protected:
	virtual ~CastleMemberBehavior();
};

CastleMemberBehavior::~CastleMemberBehavior()
{
	m_moduleInterface = &g_castleMemberBehaviorModuleInterfaceDispatch;

	if( TheAudio )
	{
		TheAudio->removeAudioEvent( m_audioHandle );
		m_audioHandle = 1;
	}
}
