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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public DozerRootBase, public DozerIface1, public DozerIface2,
	public DozerIface3, public DozerIface4
{
public:
	virtual ~AIUpdateInterface();

private:
	unsigned char m_pad[0x318];
};

class DozerAIInterface { public: virtual void vslot(); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerPrimaryStateMachine
{
public:
	virtual ~DozerPrimaryStateMachine();
};

// The 0x70-byte member released through the ILT at 0x00026F35 (which jumps to
// the 162-byte AudioEventRTS destructor at 0x000B31F0) is a retail
// AudioEventRTS, so the member carries that class's own name and the BFME
// 0x70-byte footprint: vptr + 0x6C.  The destructor is declared
// non-virtual because the call at +0xB3 is the SCALAR AudioEventRTS destructor
// named by the ledger at 0x000B31F0, not the 77-byte virtual body at
// 0x000CFA40; the vptr is spelled as a member to keep the size at 0x70.
class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	void *m_vptr;				// +0x00
	unsigned char m_pad[0x6C];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
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
	AudioEventRTS m_buildingSound;
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
