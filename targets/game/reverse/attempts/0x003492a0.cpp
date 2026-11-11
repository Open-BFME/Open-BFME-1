// ??1ScriptEngine@@UAE@XZ
// partial score=1.0 date=2026-11-11
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ScriptEngine::~ScriptEngine, retail 0x003492A0 (928 B). Probe: EXACT (928 B).
// Identity: installs the ScriptEngine vftables (0x010E7A30,
// the vtable the ledger ties to ScriptEngine::init, and 0x010E7A18 for Snapshot),
// clears TheScriptEngine, and runs ZH's GetProcAddress(dll, "DestroyDebugDialog")
// / FreeLibrary teardown and reset() before the members go. Member offsets and
// the 25 member EH states are read from the destruction order; names follow the
// ZH ScriptEngine.h members where the type and order agree, otherwise the address.
// The node pointer at 0x012F0754 is file-static (BFME 2 donor
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_dtor.cpp keeps its
// debug-window holder file-static too). Internal linkage is what gives retail's
// mov ecx,[g] / cmp / mov edi,ecx home at +0x6E; an extern or defined global
// homes the operand in EDI (7 bytes) or takes the 929-byte EAX form.
// 0x00339A80 (the particle sink start, ZH's particleEditorUpdate analogue)
// lazily creates the node, so it shares this TU and the static.
#include <list>
#include <vector>
#include "ascii_string.h"

typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

	int m_subsystemData;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// Types whose destructors retail calls out of line (opaque here).
class ActionTemplate { public: ~ActionTemplate(); char m[0x7c]; };
class ConditionTemplate { public: ~ConditionTemplate(); char m[0x7c]; };
class Rva003492A0Member16040 { public: ~Rva003492A0Member16040(); char m[0xc]; };
class Rva003492A0Member1604C { public: ~Rva003492A0Member1604C(); char m[0xc]; };
class Rva003492A0Member16058 { public: ~Rva003492A0Member16058(); char m[0xc]; };
class Rva003492A0Member16064 { public: ~Rva003492A0Member16064(); char m[0xc]; };
class Rva003492A0NameFlagMap { public: ~Rva003492A0NameFlagMap(); char m[0xc]; };
class AttackPriorityInfo { public: virtual ~AttackPriorityInfo(); char m[0xc]; };
class Rva003492A0Member1709C { public: ~Rva003492A0Member1709C(); char m[0x44]; };
class ObjectTypeCount { public: ~ObjectTypeCount(); char m[0xc]; };
class ScienceVec { public: ~ScienceVec(); char m[0xc]; };
class VecNamedReveal { public: ~VecNamedReveal(); char m[0xc]; };

struct AsciiStringUINT { AsciiString m_name; unsigned m_value; };
struct AsciiStringObjectID { AsciiString m_name; unsigned m_id; };
struct AsciiStringCoord3D { AsciiString m_name; float x, y, z; };

typedef _STL::list<AsciiString> ListAsciiString;
typedef _STL::list<AsciiStringUINT> ListAsciiStringUINT;
typedef _STL::list<AsciiStringObjectID> ListAsciiStringObjectID;
typedef _STL::list<AsciiStringCoord3D> ListAsciiStringCoord3D;

class Rva0033C070TailDtor;
class Rva00339A80ParticleSink
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void attach(void *p) = 0;
	virtual void adopt(Rva0033C070TailDtor *node) = 0;
	virtual void start() = 0;
};

// The auto-release holder the destructor empties (retail 0x003367E0 dtor).
class Rva003492A0Holder
{
public:
	Rva003492A0Holder(Rva003492A0Holder &other)
		: m_guard(other.m_guard), m_target(other.m_target)
	{
		other.m_guard = 0;
		other.m_target = 0;
	}
	virtual ~Rva003492A0Holder();

	void *m_guard;
	Rva00339A80ParticleSink *m_target;
};
extern Rva003492A0Holder g_rva012F0770Holder;

class Rva00020BA3TailBase
{
public:
	virtual ~Rva00020BA3TailBase();
};
class Rva0033C070TailDtor : public Rva00020BA3TailBase
{
public:
	Rva0033C070TailDtor() : m_value(0), m_flag(0) {}
	virtual ~Rva0033C070TailDtor() {}

	int m_value;
	char m_flag;
};
static Rva0033C070TailDtor *g_rva00339a80Node;

extern HMODULE TheScriptDebugWindowDLL;

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual ~ScriptEngine();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

	_STL::vector<void *> m_sequentialScripts;			// +0x0C
	int m_18;
	ActionTemplate m_actionTemplates[0x21f];			// +0x1C
	ConditionTemplate m_conditionTemplates[0xb8];			// +0x10720
	Rva003492A0Member16040 m_16040;
	Rva003492A0Member1604C m_1604C;
	Rva003492A0Member16058 m_16058;
	Rva003492A0Member16064 m_16064;
	Rva003492A0NameFlagMap m_16070;
	AttackPriorityInfo m_attackPriorityInfo[0x100];			// +0x1607C
	int m_1707C[3];
	AsciiString m_17088;
	char m_1708C[0x10];
	Rva003492A0Member1709C m_1709C;
	ObjectTypeCount m_objectCounts[0x20];				// +0x170E0
	ListAsciiString m_completedVideo;				// +0x17260
	ListAsciiStringUINT m_testingSpeech;				// +0x17264
	ListAsciiStringUINT m_testingAudio;				// +0x17268
	ListAsciiString m_uiInteractions;				// +0x1726C
	ListAsciiString m_17270;
	ListAsciiStringObjectID m_triggeredSpecialPowers[0x20];		// +0x17274
	ListAsciiStringObjectID m_midwaySpecialPowers[0x20];
	ListAsciiStringObjectID m_finishedSpecialPowers[0x20];
	ListAsciiStringObjectID m_completedUpgrades[0x20];
	ScienceVec m_acquiredSciences[0x20];				// +0x17474
	ListAsciiStringCoord3D m_toppleDirections;			// +0x175F4
	VecNamedReveal m_namedReveals;					// +0x175F8
	char m_17604[0x24];
	_STL::vector<void *> m_allObjectTypeLists;			// +0x17628
};

// ??1ScriptEngine@@UAE@XZ
ScriptEngine::~ScriptEngine()
{
	TheScriptEngine = 0;
	{
		Rva003492A0Holder released(g_rva012F0770Holder);
	}

	Rva0033C070TailDtor *object = g_rva00339a80Node;
	if (object)
	{
		object->Rva0033C070TailDtor::~Rva0033C070TailDtor();
		operator delete(object);
	}
	g_rva00339a80Node = 0;

	if (TheScriptDebugWindowDLL)
	{
		FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "DestroyDebugDialog");
		if (proc)
			proc();
		FreeLibrary(TheScriptDebugWindowDLL);
		TheScriptDebugWindowDLL = 0;
	}

	reset();
}

class ParticleSystemManager
{
public:
	unsigned char m_unported[0x84];
	void *m_sinkData;
};
extern ParticleSystemManager *TheParticleSystemManager;

void Rva00339A80ParticleSystemSinkStart()
{
	if (g_rva012F0770Holder.m_target == 0)
		return;

	if (g_rva00339a80Node == 0)
	{
		g_rva00339a80Node = new Rva0033C070TailDtor;
		g_rva012F0770Holder.m_target->adopt(g_rva00339a80Node);
	}

	g_rva012F0770Holder.m_target->attach(TheParticleSystemManager->m_sinkData);
	g_rva012F0770Holder.m_target->start();
}
