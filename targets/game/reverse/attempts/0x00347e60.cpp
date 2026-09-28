// ??0ScriptEngine@@QAE@XZ
// partial score=0.99 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>
#include <list>
#include <map>
#include <utility>

// ScriptEngine's constructor, retail 0x00347E60 (1164 bytes).
//
// Identity: the only caller is GameEngine::init (through the ILT). The body
// installs vtable 0x010E7A30 (slot 1 is the matched ScriptEngine::init at
// 0x00340B80) and the Snapshot-side vtable 0x010E7A18, after the inline
// Snapshot constructor. Its tail is the Zero Hour constructor's body
// (st_CanAppCont, the two frame counters, setGlobalDifficulty(NORMAL)).
//
// Layout: every member with a destructor is pinned by the retail unwind table
// (FuncInfo 0x00E086DC, 24 states). ActionTemplate[543] and
// ConditionTemplate[184] follow Zero Hour's order; m_attackPriorityInfo[256]
// and m_numAttackInfo are witnessed by the matched findAttackInfo
// (0x0033DD70); m_objectsShouldReceiveDifficultyBonus and
// m_ChooseVictimAlwaysUsesNormal by their matched setters; m_useLogicDebugFrame
// by the matched debug-frame bodies. Members without such a witness keep
// their offset as their name.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

class Xfer;
class Object;
class SequentialScript;
struct Coord3D { float x, y, z; };
enum ObjectID { INVALID_ID = 0 };
enum ScienceType { SCIENCE_INVALID = -1 };

struct ScriptCounter
{
	int value;
	bool isCountdownTimer;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class Template
{
public:
	Template();

protected:
	~Template();

private:
	char m_data[124];
};

class ConditionTemplate : public Template {};
class ActionTemplate : public Template {};

class AttackPriorityInfo
{
public:
	AttackPriorityInfo();
	virtual ~AttackPriorityInfo();

private:
	AsciiString m_name;
	int m_defaultPriority;
	void *m_priorityMap;
};

struct NamedReveal
{
	NamedReveal(void) {}

	AsciiString m_revealName;
	AsciiString m_waypointName;
	float m_radiusToReveal;
	AsciiString m_playerName;
};

struct Coord2D { float x, y; };

struct BreezeInfo
{
	float m_direction;
	Coord2D m_directionVec;
	float m_intensity;
	float m_lean;
	float m_randomness;
	short m_breezePeriod;
	short m_breezeVersion;
};

class ObjectTypes;

typedef _STL::pair<AsciiString, AsciiString> ScriptNamePair;

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	ScriptEngine();
	virtual ~ScriptEngine();
	virtual void init();
	virtual void reset();
	virtual void update();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	void setGlobalDifficulty(int difficulty) { m_17620 = difficulty; }

	_STL::vector<SequentialScript *> m_sequentialScripts;             // +0x0C
	int m_00018;
	ActionTemplate m_actionTemplates[543];                            // +0x1C
	ConditionTemplate m_conditionTemplates[184];                      // +0x10720
	_STL::map<ScriptNamePair, ScriptCounter> m_16040;
	_STL::map<ScriptNamePair, unsigned int> m_1604C;
	_STL::map<ScriptNamePair, ObjectID> m_16058;
	_STL::map<ScriptNamePair, bool> m_16064;
	_STL::map<AsciiString, bool> m_16070;
	AttackPriorityInfo m_attackPriorityInfo[256];                     // +0x1607C
	int m_numAttackInfo;                                              // +0x1707C
	int m_17080;
	int m_17084;
	AsciiString m_17088;
	int m_1708C;
	int m_17090;
	int m_17094;
	int m_17098;
	_STL::vector<_STL::pair<AsciiString, ObjectID> > m_1709C;
	bool m_170A8;
	int m_170AC;
	int m_170B0;
	int m_170B4;
	bool m_170B8;
	int m_170BC;
	int m_170C0;
	int m_170C4;
	int m_170C8;
	int m_170CC;
	int m_170D0;
	int m_170D4;
	int m_170D8;
	int m_170DC;
	_STL::map<AsciiString, int> m_170E0[32];
	_STL::list<AsciiString> m_17260;
	_STL::list<_STL::pair<AsciiString, unsigned int> > m_17264;
	_STL::list<_STL::pair<AsciiString, unsigned int> > m_17268;
	_STL::list<AsciiString> m_1726C;
	_STL::list<AsciiString> m_17270;
	_STL::list<_STL::pair<AsciiString, ObjectID> > m_17274[32];
	_STL::list<_STL::pair<AsciiString, ObjectID> > m_172F4[32];
	_STL::list<_STL::pair<AsciiString, ObjectID> > m_17374[32];
	_STL::list<_STL::pair<AsciiString, ObjectID> > m_173F4[32];
	_STL::vector<ScienceType> m_17474[32];
	_STL::list<_STL::pair<AsciiString, Coord3D> > m_175F4;
	_STL::vector<NamedReveal> m_namedReveals;                        // +0x175F8
	BreezeInfo m_breezeInfo;                                          // +0x17604
	int m_17620;
	bool m_17624;
	_STL::vector<ObjectTypes *> m_17628;
	bool m_objectsShouldReceiveDifficultyBonus;                       // +0x17634
	bool m_ChooseVictimAlwaysUsesNormal;                              // +0x17635
	bool m_17636;
	bool m_17637;
	bool m_useLogicDebugFrame;                                        // +0x17638
	double m_17640;
	double m_17648;
	double m_17650;
	double m_17658;
};

extern int g_scriptFrame012F0760;
extern int g_scriptFrame012F0764;
extern bool LogicCanAppContinue;
extern bool ClientCanAppContinue;

// ??0ScriptEngine@@QAE@XZ
ScriptEngine::ScriptEngine()
	: m_00018(0),
	  m_numAttackInfo(0),
	  m_17080(0),
	  m_17084(0),
	  m_1708C(0),
	  m_17090(0),
	  m_17094(0),
	  m_17098(0),
	  m_170A8(true),
	  m_170AC(0),
	  m_170B0(0),
	  m_170B4(0),
	  m_170B8(false),
	  m_170BC(0),
	  m_170C0(0),
	  m_170C4(0),
	  m_170C8(0),
	  m_170CC(0),
	  m_170D0(0),
	  m_170D4(0),
	  m_170D8(0),
	  m_170DC(0),
	  m_17624(false),
	  m_objectsShouldReceiveDifficultyBonus(true),
	  m_ChooseVictimAlwaysUsesNormal(false),
	  m_17636(false),
	  m_17637(false),
	  m_useLogicDebugFrame(true),
	  m_17640(0.0),
	  m_17648(0.0),
	  m_17650(0.0),
	  m_17658(0.0)
{
	setGlobalDifficulty(1);
	LogicCanAppContinue = true;
	ClientCanAppContinue = true;
	g_scriptFrame012F0760 = g_scriptFrame012F0764 = 0;
}
