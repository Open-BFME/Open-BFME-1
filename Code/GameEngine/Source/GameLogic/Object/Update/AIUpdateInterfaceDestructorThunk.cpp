// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

class Object;

class Module
{
public:
	virtual ~Module();

protected:
	const void *m_moduleData;
	Object *m_object;
};

class AIUpdateBehaviorInterface
{
public:
	virtual void behaviorInterfaceAnchor();
};

class AIUpdateUpdateInterface
{
public:
	virtual void updateInterfaceAnchor();
};

class BehaviorModule : public Module,
	public AIUpdateBehaviorInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule,
	public AIUpdateUpdateInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class AIUpdateCommandInterface
{
public:
	virtual void commandInterfaceAnchor();
};

class AIUpdateExtraInterface
{
public:
	virtual void extraInterfaceAnchor();
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void stateSlot00();
	virtual void stateSlot01();
	virtual void stateSlot02();
	virtual void stateSlot03();
	virtual void stateSlot04();
	virtual void stateSlot05();
	virtual void stateSlot06();
	virtual void stateSlot07();
	virtual void stateSlot08();
	virtual void stateSlot09();
	virtual void stateSlot10();
	virtual void stateSlot11();
	virtual void stateSlot12();
	virtual void stateSlot13();
	virtual void halt();

	void deleteInstance()
	{
		delete this;
	}
};

class Path
{
protected:
	virtual ~Path();
};

class BFMEDeletablePath : public Path
{
public:
	void destroy()
	{
		Path::~Path();
	}
};

class TurretAI
{
public:
	virtual ~TurretAI();

	void deleteInstance()
	{
		delete this;
	}
};

struct Mem0027E9C0Element
{
	int m_pad0;
	int m_pad1;
	_STL::list<int> m_values;
};

typedef _STL::vector<Mem0027E9C0Element> Mem0027E9C0;

class BfmeBaseW
{
public:
	virtual ~BfmeBaseW() {}
	};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() {}
};

class BfmeEmbedded : public BfmeBaseVUQ
{
private:
	Mem0027E9C0 m_vector;
};

class Gen_001BA9E0 : public BfmeBaseW
{
public:
	virtual ~Gen_001BA9E0();
	void bfmeFinish();

private:
	char m_body[0x1c];
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

class GiantBirdMemberA
{
public:
	~GiantBirdMemberA();

private:
	char m_body[0x3c];
};

class AIUpdateArrayElement
{
public:
	~AIUpdateArrayElement();

private:
	char m_body[0xc];
};

#pragma comment(linker, "/alternatename:??1AIUpdateArrayElement@@QAE@XZ=?j_0001364c@@YAXXZ")

class AIUpdateInterface : public UpdateModule,
	public AIUpdateCommandInterface,
	public AIUpdateExtraInterface
{
public:
	virtual ~AIUpdateInterface();

	virtual void aiSlot00();
	virtual void aiSlot01();
	virtual void aiSlot02();
	virtual void aiSlot03();
	virtual void aiSlot04();
	virtual void aiSlot05();
	virtual void aiSlot06();
	virtual void aiSlot07();
	virtual void aiSlot08();
	virtual void aiSlot09();
	virtual void aiSlot10();
	virtual void aiSlot11();
	virtual void aiSlot12();
	virtual void aiSlot13();
	virtual void aiSlot14();
	virtual void aiSlot15();
	virtual void aiSlot16();
	virtual void aiSlot17();
	virtual void aiSlot18();
	virtual void aiSlot19();
	virtual void aiSlot20();
	virtual void aiSlot21();
	virtual void aiSlot22();
	virtual void aiSlot23();
	virtual void aiSlot24();
	virtual void aiSlot25();
	virtual void aiSlot26();
	virtual void aiSlot27();
	virtual void aiSlot28();
	virtual void aiSlot29();
	virtual void aiSlot30();
	virtual void aiSlot31();
	virtual void aiSlot32();
	virtual void aiSlot33();
	virtual void aiSlot34();
	virtual void aiSlot35();
	virtual void aiSlot36();
	virtual void aiSlot37();
	virtual void aiSlot38();
	virtual void aiSlot39();
	virtual void aiSlot40();
	virtual void aiSlot41();
	virtual void aiSlot42();
	virtual void aiSlot43();
	virtual void aiSlot44();
	virtual void aiSlot45();
	virtual void aiSlot46();
	virtual void aiSlot47();
	virtual void aiSlot48();
	virtual void aiSlot49();
	virtual void aiSlot50();
	virtual void aiSlot51();
	virtual void aiSlot52();
	virtual void aiSlot53();
	virtual void aiSlot54();
	virtual void aiSlot55();
	virtual void aiSlot56();
	virtual void aiSlot57();
	virtual void aiSlot58();
	virtual void aiSlot59();
	virtual void aiSlot60();
	virtual void aiSlot61();
	virtual void aiSlot62();
	virtual void aiSlot63();
	virtual void aiSlot64();
	virtual void aiSlot65();
	virtual void aiSlot66();
	virtual void aiSlot67();
	virtual void aiSlot68();
	virtual void aiSlot69();
	virtual void aiSlot70();
	virtual void aiSlot71();
	virtual void aiSlot72();
	virtual void aiSlot73();
	virtual void aiSlot74();
	virtual void aiSlot75();
	virtual void aiSlot76();
	virtual void aiSlot77();
	virtual void aiSlot78();
	virtual void aiSlot79();
	virtual void aiSlot80();
	virtual void aiSlot81();
	virtual void aiSlot82();
	virtual void aiSlot83();
	virtual void aiSlot84();
	virtual void aiSlot85();
	virtual void aiSlot86();
	virtual void aiSlot87();
	virtual void aiSlot88();
	virtual void aiSlot89();
	virtual void aiSlot90();
	virtual void aiSlot91();
	virtual void aiSlot92();
	virtual void aiSlot93();
	virtual void aiSlot94();
	virtual void aiSlot95();
	virtual void aiSlot96();
	virtual void aiSlot97();
	virtual void aiSlot98();
	virtual void aiSlot99();
	virtual void aiSlot100();
	virtual void aiSlot101();
	virtual void aiSlot102();
	virtual void aiSlot103();
	virtual void aiSlot104();
	virtual void aiSlot105();
	virtual void aiSlot106();
	virtual void aiSlot107();
	virtual void aiSlot108();
	virtual void aiSlot109();
	virtual void aiSlot110();
	virtual void aiSlot111();
	virtual void aiSlot112();
	virtual void aiSlot113();
	virtual void aiSlot114();
	virtual void aiSlot115();
	virtual void aiSlot116();
	virtual void aiSlot117();
	virtual void aiSlot118();
	virtual void aiSlot119();
	virtual void aiSlot120();
	virtual void setLocomotorGoalNone();

private:
	char m_padding000[0x30 - 0x28];
	StateMachine *m_stateMachine;
	char m_padding034[0x74 - 0x34];
	AIUpdateArrayElement m_array[0x10];
	char m_padding134[0x140 - 0x134];
	Path *m_path;
	char m_padding144[0x1a8 - 0x144];
	Gen_001BA9E0 m_locomotorSet;
	char m_padding1c8[0x1cc - 0x1c8];
	void *m_curLocomotor;
	char m_padding1d0[0x1e8 - 0x1d0];
	TurretAI *m_turretAI[2];
	char m_padding1f0[0x1f4 - 0x1f0];
	BFMERetailAsciiString m_string;
	char m_padding1f8[0x204 - 0x1f8];
	BfmeEmbedded m_embeddedBase;
	char m_padding214[0x27c - 0x214];
	GiantBirdMemberA m_giantBird;
	char m_padding2b8[0x31e - 0x2b8];
	unsigned char m_waitingForPath;
	unsigned char m_isAttackPath;
	char m_padding320[0x326 - 0x320];
	unsigned char m_isBlockedAndStuck;

	void destroyPath()
	{
		Path *path = m_path;
		if (path)
		{
			reinterpret_cast<BFMEDeletablePath *>(path)->destroy();
			::operator delete(path);
		}
		m_path = 0;
		m_waitingForPath = 0;
		m_isBlockedAndStuck = 0;
		m_isAttackPath = 0;
		setLocomotorGoalNone();
	}
};

AIUpdateInterface::~AIUpdateInterface()
{
	m_locomotorSet.bfmeFinish();
	m_curLocomotor = 0;

	if (m_stateMachine)
	{
		m_stateMachine->halt();
		m_stateMachine->deleteInstance();
	}

	for (int i = 0; i < 2; ++i)
	{
		if (m_turretAI[i])
			m_turretAI[i]->deleteInstance();
		m_turretAI[i] = 0;
	}
	m_stateMachine = 0;
	destroyPath();
}
