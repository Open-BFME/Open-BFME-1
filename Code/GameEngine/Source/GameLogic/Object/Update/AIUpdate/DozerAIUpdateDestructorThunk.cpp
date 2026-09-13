// cl: /DNDEBUG /MD /EHsc

class DozerRootBase
{
public:
	virtual ~DozerRootBase();

private:
	unsigned char m_pad[8];
};

class DozerIface1 { public: virtual void vslot(); };
class DozerIface2 { public: virtual void vslot(); private: unsigned char m_pad[0xC]; };
class DozerIface3 { public: virtual void vslot(); };
class DozerIface4 { public: virtual void vslot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public DozerRootBase, public DozerIface1, public DozerIface2,
	public DozerIface3, public DozerIface4
{
public:
	virtual ~AIUpdateInterface();

private:
	unsigned char m_pad[0x318];
};

class DozerAIInterface { public: virtual void vslot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerPrimaryStateMachine
{
public:
	virtual ~DozerPrimaryStateMachine();
};

class DozerAudioEventRTS
{
public:
	virtual ~DozerAudioEventRTS();

private:
	unsigned char m_pad[0x6C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
protected:
	virtual ~DozerAIUpdate();

private:
	struct DozerTaskInfo
	{
		unsigned int m_targetObjectID;
		unsigned int m_taskOrderFrame;
	};

	struct DozerDockPointInfo
	{
		~DozerDockPointInfo();

		unsigned int m_valid;
		float m_location[3];
	};

	DozerTaskInfo m_task[3];
	DozerPrimaryStateMachine *m_dozerMachine;
	unsigned int m_currentTask;
	DozerAudioEventRTS m_buildingSound;
	unsigned int m_isRebuild;
	DozerDockPointInfo m_dockPoint[3][3];
	unsigned int m_buildSubTask;
};

// ??1DozerAIUpdate@@MAE@XZ
DozerAIUpdate::~DozerAIUpdate()
{
	delete m_dozerMachine;
	m_dozerMachine = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_task[i].m_targetObjectID = 0;
		m_task[i].m_taskOrderFrame = 0;
	}
}
