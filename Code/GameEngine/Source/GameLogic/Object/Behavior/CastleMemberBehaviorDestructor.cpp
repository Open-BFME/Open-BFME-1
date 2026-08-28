// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
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

class Rva0036BBA0BehaviorModule
{
public:
	virtual ~Rva0036BBA0BehaviorModule();

private:
	unsigned char m_data[ 8 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

struct ModuleInterfaceDispatch { };

extern const ModuleInterfaceDispatch
	g_castleMemberBehaviorModuleInterfaceDispatch;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public Rva0036BBA0BehaviorModule,
	public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() { }

protected:
	const ModuleInterfaceDispatch *m_moduleInterface;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_audioHandle;
	bool m_24;
	bool m_25;
};

class CastleMemberBehavior : public UpdateModule
{
public:
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
