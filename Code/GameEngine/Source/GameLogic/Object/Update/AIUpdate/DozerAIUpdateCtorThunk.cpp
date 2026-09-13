// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DozerAIUpdate constructor.  The factory and matched destructor
// fix the AI base, AudioEventRTS member, and 3x3 dock-point array.

class Thing;
class ModuleData;

class Object;
class BehaviorModule
{
public: virtual void slot();
private: unsigned int m_04; Object *m_object;
};

template <int Number> class __declspec(novtable) DozerIface { public: virtual void slot() = 0; };
class __declspec(novtable) DozerWideIface
{
public: virtual void slot() = 0;
private: unsigned int m_14, m_18, m_1c;
};
class __declspec(novtable) DozerPaddedIface
{
public: virtual void slot() = 0;
private: unsigned char m_pad[0x318];
};
class DozerAIInterface
{
public:
	virtual ~DozerAIInterface();
	virtual void slot();
};

class AnimalAIUpdateBase : public BehaviorModule
{
public:
	AnimalAIUpdateBase(Thing *, const ModuleData *);
};

class AsciiString {};
extern const AsciiString Rva01336E50Str;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, int);
	virtual ~AudioEventRTS();
private:
	unsigned char m_pad[0x6c];
};

struct DozerTaskInfo
{
	unsigned int m_targetObjectID;
	unsigned int m_taskOrderFrame;
};

struct Coord3D
{
	void zero() { x = 0; y = 0; z = 0; }
	unsigned int x, y, z;
};

struct DozerDockPointInfo
{
	DozerDockPointInfo();
	~DozerDockPointInfo();
	bool valid;
	unsigned char m_pad[3];
	Coord3D location;
};

class DozerAIUpdate : public AnimalAIUpdateBase,
	public DozerIface<1>, public DozerWideIface, public DozerIface<2>,
	public DozerPaddedIface, public DozerAIInterface
{
public:
	DozerAIUpdate(Thing *, const ModuleData *);
	virtual ~DozerAIUpdate();
private:
	DozerTaskInfo m_task[3];
	void *m_dozerMachine;
	int m_currentTask;
	AudioEventRTS m_buildingSound;
	bool m_isRebuild;
	unsigned char m_pad3d5[3];
	DozerDockPointInfo m_dockPoint[3][3];
	unsigned int m_buildSubTask;
	void createMachines();
};

// ??0DozerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DozerAIUpdate::DozerAIUpdate(Thing *thing, const ModuleData *data)
	: AnimalAIUpdateBase(thing, data), m_buildingSound(Rva01336E50Str, 0)
{
	for (int i = 0; i != 3; ++i)
	{
		m_task[i].m_targetObjectID = 0;
		m_task[i].m_taskOrderFrame = 0;
		for (int j = 0; j != 3; ++j)
		{
			m_dockPoint[i][j].valid = false;
			m_dockPoint[i][j].location.zero();
		}
	}
	m_currentTask = -1;
	m_buildSubTask = 0;
	m_dozerMachine = 0;
	m_isRebuild = false;
	createMachines();
}
