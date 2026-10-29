// ?unitTimings@Rva0038C1E0UnitTimings@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Include
// Retail 0x0038C1E0 (2892 bytes): BFME's port of Zero Hour's DO_UNIT_TIMINGS
// harness, unitTimings() (inputs/reference/CnC_Generals_Zero_Hour/Generals/
// Code/GameEngine/Source/GameLogic/System/GameLogic.cpp:2724). The literals
// "No Object", "**NO MODEL**", "CINE" and "GLAInfantryAngryMobNexus" and the
// settle/time/report state machine are the twin's; BFME keeps the function's
// statics in one object at VA 0x012F08A0, which GameLogic::update (0x0038DA10
// +0x188) passes in ECX through ILT 0x7E32. The method keeps the twin's name;
// the owning object's class is not recovered, so it keeps the address.

// This unit's ThingTemplate view defines getDrawModuleInfo inline at another offset than
// retail's 0x000C8B80 (+0x114) and emits that COMDAT copy; rename it so only
// retail-equal copies carry the name. Inlined calls are unchanged.
#define getDrawModuleInfo getDrawModuleInfo_LocalView
#include "ascii_string.h"

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);
#pragma intrinsic(memset)

#define THING_TU_MEMBERS \
	const ThingTemplate *getTemplate() const; \
	void setOrientation(Real angle); \
	void setPosition(const Coord3D *pos);
#include "object.h"
#include "Lib/Coord3D.h"
// StringBase<char>::compare (0x0005FEB0) and operator== (0x0007FFF0) stay
// out-of-line calls, but retail's caller assumes neither writes memory: it keeps
// m_curThing in ESI across the name test and walks the template chain with it.
// Visible noinline bodies (selectany, as in StringBase.cpp) give MSVC that view.
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
template <> inline __declspec(noinline) int StringBase<char>::compare(const StringBase<char> &str) const
{
	const int len = str.m_data ? str.m_data->length : 0;
	const char *data = str.m_data ? &str.m_data->data[0] : "";
	const int myLen = m_data ? m_data->length : 0;
	const char *myData = m_data ? &m_data->data[0] : "";
	int result = memcmp(myData, data, myLen < len ? myLen : len);
	if (result == 0)
		result = myLen - len;
	return result;
}
template <typename T> inline __declspec(noinline) bool operator==(const StringBase<T> &left, const StringBase<T> &right)
{
	return left.compare(right) == 0;
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);

void HideControlBar(bool immediate);

enum KindOfType { KINDOF_STRUCTURE = 7, KINDOF_INFANTRY = 8, KINDOF_CAVALRY = 9, KINDOF_MONSTER = 10, KINDOF_MACHINE = 11 };

// Retail 0x001701A0 / 0x001C2B80: the forty-byte model-condition record the
// draw module is asked about, built and then cleared.
class Rva001701A0Record
{
public:
	char m_storage[40];
	Rva001701A0Record();
};
class Rva001C2B80 { public: void clear(); };

class ModuleData
{
public:
	virtual void moduleDataSlot00();
	virtual void moduleDataSlot01();
	virtual void moduleDataSlot02();
	virtual void moduleDataSlot03();
	virtual void moduleDataSlot04();
	virtual void moduleDataSlot05();
	virtual void moduleDataSlot06();
	virtual void moduleDataSlot07();
	virtual AsciiString getBestModelNameForWB(const Rva001701A0Record &state) const;	// slot 8
};

class ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const ModuleData *second;
		Int interfaceMask;
		bool copiedFromDefault;
	};
	Int getCount() const { return m_end - m_begin; }
	UnsignedInt size() const { return m_end - m_begin; }
	const ModuleData *getNthData(Int i) const
	{
		if (i >= 0 && (UnsignedInt)i < size())
			return m_begin[i].second;
		return 0;
	}
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

class ThingTemplate
{
public:
	bool isKindOf(KindOfType t) const;
	const AsciiString &getName() const { return m_name; }
	const AsciiString &getDefaultOwningSide() const { return m_defaultOwningSide; }
	const ModuleInfo &getDrawModuleInfo() const { return m_drawModuleInfo; }
	const ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }

	char m_unmodelled00[0x20];
	AsciiString m_name;									// +0x20
	char m_unmodelled24[0x4];
	AsciiString m_defaultOwningSide;					// +0x28
	char m_unmodelled2C[0x2A0 - 0x2C];
	ModuleInfo m_drawModuleInfo;						// +0x2A0
	char m_unmodelled2AC[0x38C - 0x2AC];
	ThingTemplate *m_nextThingTemplate;					// +0x38C
	char m_unmodelled390[0x3C0 - 0x390];
	Real m_assetScale;									// +0x3C0
	char m_unmodelled3C4[0x494 - 0x3C4];
	unsigned char m_editorSorting;						// +0x494
};

class BFMEActionObject { public: bool testStatus(Int status) const; };

class CreateModuleInterface
{
public:
	virtual void createSlot00();
	virtual void onBuildComplete();
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot00();
	virtual void behaviorSlot01();
	virtual void behaviorSlot02();
	virtual CreateModuleInterface *getCreate();
};
class Rva0038C1E0ModuleBase
{
public:
	virtual void moduleSlot00();
	char m_unmodelled04[0x8];
};
class BehaviorModule
{
public:
	CreateModuleInterface *getCreate() { return m_behaviorInterface.getCreate(); }
	void *m_vfptr00;
	char m_unmodelled04[0x8];
	BehaviorModuleInterface m_behaviorInterface;		// +0x0C
};

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }
	UnsignedInt m_bits[3];
};
typedef BitFlags<86> ObjectStatusMaskType;

class Team
{
public:
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	char m_unmodelled00[0x31];
	bool m_active;										// +0x31
	bool m_created;										// +0x32
};
class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
	char m_unmodelled00[0x230];
	Team *m_defaultTeam;								// +0x230
};
class PlayerList { public: Player *getNthPlayer(Int i); };
extern PlayerList *ThePlayerList;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const ObjectStatusMaskType &statusBits, UnsignedInt flags);
	const ThingTemplate *firstTemplate() const { return m_firstTemplate; }
	char m_unmodelled00[0x8];
	const ThingTemplate *m_firstTemplate;				// +0x08
};
extern ThingFactory *TheThingFactory;

class GameLogic
{
public:
	void destroyObject(Object *obj);
	Object *getFirstObject() const { return m_objList; }
	char m_unmodelled00[0xA8];
	Object *m_objList;									// +0xA8
};
extern GameLogic *TheGameLogic;

class Pathfinder { public: void addObjectToPathfindMap(Object *obj); };
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_unmodelled00[0xC];
	Pathfinder *m_pathfinder;							// +0x0C
};
extern AI *TheAI;

class Matrix3D
{
public:
	explicit Matrix3D(bool init)
	{
		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
	}
	Real Row[3][4];
};

// Retail calls these three placement helpers as TerrainLogic methods (ECX is
// loaded with TheTerrainLogic), through their ILT thunks.
void j_000364ad();
void j_000050c9();
void j_00037f83();

class TerrainLogic
{
public:
	virtual void terrainSlot00();
	virtual void terrainSlot01();
	virtual void terrainSlot02();
	virtual void terrainSlot03();
	virtual void terrainSlot04();
	virtual void terrainSlot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;	// slot 6
	typedef void (TerrainLogic::*Placer)(const ThingTemplate *, const Coord3D *, const Matrix3D *, Real);
	void rva001AD080(const ThingTemplate *t, const Coord3D *p, const Matrix3D *m, Real s) { union { void (*entry)(); Placer method; } fn; fn.entry = &j_000364ad; (this->*fn.method)(t, p, m, s); }
	void rva001A7A90(const ThingTemplate *t, const Coord3D *p, const Matrix3D *m, Real s) { union { void (*entry)(); Placer method; } fn; fn.entry = &j_000050c9; (this->*fn.method)(t, p, m, s); }
	void rva001A34C0(const ThingTemplate *t, const Coord3D *p, const Matrix3D *m, Real s) { union { void (*entry)(); Placer method; } fn; fn.entry = &j_00037f83; (this->*fn.method)(t, p, m, s); }
};
extern TerrainLogic *TheTerrainLogic;

class Rva0038C1E0TerrainVisualBase4
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
};
class TerrainVisual
{
public:
	void *m_vfptr00;
	Rva0038C1E0TerrainVisualBase4 m_base04;				// +0x04
};
extern TerrainVisual *TheTerrainVisual;

class GameEngine
{
public:
	Int getFramesPerSecondLimit() const { return m_maxFPS; }
	char m_unmodelled00[0x34];
	Int m_maxFPS;										// +0x34
};
extern GameEngine *TheGameEngine;

class GlobalData
{
public:
	char m_unmodelled00[0x1E];
	bool m_useFpsLimit;									// +0x1E
	char m_unmodelled1F[0x5];
	Int m_framesPerSecondLimit;							// +0x24
};
extern GlobalData *TheWritableGlobalData;

class Display
{
public:
	virtual void displaySlot00();
	virtual void displaySlot01();
	virtual void displaySlot02();
	virtual void displaySlot03();
	virtual void displaySlot04();
	virtual void displaySlot05();
	virtual void displaySlot06();
	virtual void displaySlot07();
	virtual void displaySlot08();
	virtual void displaySlot09();
	virtual void displaySlot0A();
	virtual void displaySlot0B();
	virtual void displaySlot0C();
	virtual void displaySlot0D();
	virtual void displaySlot0E();
	virtual void displaySlot0F();
	virtual void displaySlot10();
	virtual void displaySlot11();
	virtual void displaySlot12();
	virtual void displaySlot13();
	virtual void displaySlot14();
	virtual void displaySlot15();
	virtual void displaySlot16();
	virtual void displaySlot17();
	virtual void displaySlot18();
	virtual void displaySlot19();
	virtual void displaySlot1A();
	virtual void displaySlot1B();
	virtual void displaySlot1C();
	virtual void displaySlot1D();
	virtual void displaySlot1E();
	virtual void displaySlot1F();
	virtual void displaySlot20();
	virtual void displaySlot21();
	virtual void displaySlot22();
	virtual void displaySlot23();
	virtual void displaySlot24();
	virtual void displaySlot25();
	virtual void displaySlot26();
	virtual void displaySlot27();
	virtual void displaySlot28();
	virtual void displaySlot29();
	virtual void displaySlot2A();
	virtual void displaySlot2B();
	virtual void displaySlot2C();
	virtual void displaySlot2D();
	virtual void displaySlot2E();
	virtual void displaySlot2F();
	virtual void displaySlot30();
	virtual void displaySlot31();
	virtual void displaySlot32();
	virtual void displaySlot33();
	virtual void displaySlot34();
	virtual void displaySlot35();
	virtual void displaySlot36();
	virtual void displaySlot37();
	virtual void displaySlot38();
	virtual void displaySlot39();
	virtual void displaySlot3A();
	virtual void displaySlot3B();
	virtual void displaySlot3C();
	virtual void displaySlot3D();
	virtual void displaySlot3E();
	virtual void displaySlot3F();
	virtual void displaySlot40();
	virtual void displaySlot41();
	virtual void displaySlot42();
	virtual void displaySlot43();
	virtual void displaySlot44();
	virtual void displaySlot45();
	virtual void displaySlot46();
	virtual void displaySlot47();
	virtual void displaySlot48();
	virtual void displaySlot49();
	virtual void displaySlot4A();
	virtual void displaySlot4B();
	virtual void displaySlot4C();
	virtual void displaySlot4D();
	virtual void displaySlot4E();
	virtual void displaySlot4F();
	virtual void displaySlot50();
	virtual void displaySlot51();
	virtual void displaySlot52();
	virtual Int getLastFrameDrawCalls();				// slot 83
	virtual void getDrawCallStats(Int *stats);			// slot 84
};
extern Display *TheDisplay;

class View
{
public:
	virtual void viewSlot00();
	virtual void viewSlot01();
	virtual void viewSlot02();
	virtual void viewSlot03();
	virtual void viewSlot04();
	virtual void viewSlot05();
	virtual void viewSlot06();
	virtual void viewSlot07(Int);
	virtual void viewSlot08();
	virtual void viewSlot09();
	virtual void viewSlot0A();
	virtual void viewSlot0B();
	virtual void viewSlot0C();
	virtual void viewSlot0D();
	virtual void viewSlot0E();
	virtual void viewSlot0F();
	virtual void viewSlot10();
	virtual void viewSlot11();
	virtual void viewSlot12();
	virtual void viewSlot13();
	virtual void viewSlot14();
	virtual void lookAt(const Coord3D *o);				// slot 21
	virtual void viewSlot16();
	virtual void viewSlot17();
	virtual void viewSlot18();
	virtual void viewSlot19();
	virtual void viewSlot1A();
	virtual void viewSlot1B();
	virtual void viewSlot1C();
	virtual void viewSlot1D();
	virtual void viewSlot1E();
	virtual void viewSlot1F();
	virtual void viewSlot20();
	virtual void viewSlot21();
	virtual void viewSlot22();
	virtual void viewSlot23();
	virtual void viewSlot24();
	virtual void viewSlot25();
	virtual void viewSlot26();
	virtual void viewSlot27();
	virtual void viewSlot28();
	virtual void viewSlot29();
	virtual void viewSlot2A();
	virtual void viewSlot2B();
	virtual void viewSlot2C();
	virtual void viewSlot2D();
	virtual void viewSlot2E();
	virtual void viewSlot2F();
	virtual void viewSlot30();
	virtual void viewSlot31();
	virtual void viewSlot32();
	virtual void viewSlot33();
	virtual void viewSlot34();
	virtual void viewSlot35();
	virtual void viewSlot36();
	virtual void viewSlot37();
	virtual void viewSlot38();
	virtual void viewSlot39();
	virtual void viewSlot3A();
	virtual void viewSlot3B();
	virtual void viewSlot3C();
	virtual void viewSlot3D();
	virtual void viewSlot3E();
	virtual void viewSlot3F();
	virtual void viewSlot40();
	virtual void viewSlot41();
	virtual void viewSlot42();
	virtual void viewSlot43();
	virtual void viewSlot44();
	virtual void viewSlot45();
	virtual void viewSlot46();
	virtual void viewSlot47();
	virtual void viewSlot48();
	virtual void viewSlot49(Real);
	virtual Real getZoom();								// slot 74
	virtual void setZoom(Real z);						// slot 75
};
extern View *TheTacticalView;

class ParticleSystemManager
{
public:
	virtual void particleSlot00();
	virtual void particleSlot01();
	virtual void particleSlot02();
	virtual void particleSlot03();
	virtual void reset();								// slot 4
	UnsignedInt getParticleCount() const { return m_particleCount; }
	char m_unmodelled04[0x80];
	UnsignedInt m_particleCount;						// +0x84
};
extern ParticleSystemManager *TheParticleSystemManager;

class MessageStream
{
public:
	virtual void messageSlot00();
	virtual void messageSlot01();
	virtual void messageSlot02();
	virtual void messageSlot03();
	virtual void messageSlot04();
	virtual void messageSlot05();
	virtual void messageSlot06();
	virtual void messageSlot07();
	virtual void messageSlot08();
	virtual void messageSlot09();
	virtual void messageSlot0A();
	virtual void messageSlot0B();
	virtual void messageSlot0C();
	virtual void *appendMessage(Int type);				// slot 13
};
extern MessageStream *TheMessageStream;

// Retail 0x00382AD0 and 0x00382AA0 write to / close the FILE* this object
// keeps at +0x18; both are matched under their own address-derived owners.
struct BfmeThingDYC { void bfmeGoDYC(void *a); };
class Rva00382AA0 { public: void release(); };

// Retail tests the string's length word in line here; StringBase keeps its
// header private, so this TU reads it through the same layout.
struct Rva0038C1E0StringHeader { Int refCount; unsigned short length; };
inline bool hasText(const AsciiString &s)
{
	const Rva0038C1E0StringHeader *h = *(Rva0038C1E0StringHeader *const *)&s;
	return h && h->length;
}

extern Int g_Va012F0A94[3];
Real g_rva012B44BCSavedZoom;

class Rva0038C1E0UnitTimings
{
public:
	void unitTimings();

	bool m_enabled;										// +0x00
	AsciiString m_singleUnit;							// +0x04
	AsciiString m_side;									// +0x08
	bool m_gotUnit;										// +0x0C
	const ThingTemplate *m_curThing;					// +0x10
	bool m_startTiming;									// +0x14
	void *m_commaLog;									// +0x18
	Int m_settleFrames;									// +0x1C
	Int m_timeFrames;									// +0x20
	Int m_unitTypes;									// +0x24
	bool m_veryFirstTime;								// +0x28
	__int64 m_startTime64;								// +0x30
	__int64 m_endTime64;								// +0x38
	__int64 m_freq64;									// +0x40
	Int m_drawCallTotal;								// +0x48
	Int m_mode;											// +0x4C
	double m_time50;
	double m_time58;
	double m_time60;
	double m_time68;
	double m_time70;
	double m_time78;
	double m_time80;
	Real m_drawCalls88;
	Real m_drawCalls8C;
	Real m_drawCalls90;
	Real m_drawCalls94;
};

// ?unitTimings@Rva0038C1E0UnitTimings@@QAEXXZ
void Rva0038C1E0UnitTimings::unitTimings()
{
	Real frameRate = TheGameEngine->m_maxFPS * 2.0f;
	if (!m_startTiming)
		return;

	if (m_settleFrames > 0) {
		m_settleFrames--;
		if (m_settleFrames > 0)
			return;
		QueryPerformanceCounter(&m_startTime64);
		QueryPerformanceFrequency(&m_freq64);
		m_timeFrames = 2;
		m_drawCallTotal = 0;
		return;
	}
	if (m_timeFrames > 0) {
		m_timeFrames--;
		if (m_timeFrames > 0)
			return;
		m_drawCallTotal = TheDisplay->getLastFrameDrawCalls();
		QueryPerformanceCounter(&m_endTime64);
		double timeToUpdate = (double)(m_endTime64 - m_startTime64) / (double)m_freq64 * 1000000.0 / (frameRate * 100.0f);
		Coord3D thePos;
		thePos.x = 400;
		thePos.y = 300;
		thePos.z = 0;

		if (m_mode == 0) {
			m_time78 = timeToUpdate;
			m_mode = 4;
			m_drawCalls94 = m_drawCallTotal * 0.01f;
			m_settleFrames = 2;
			g_rva012B44BCSavedZoom = TheTacticalView->getZoom();
			TheTacticalView->lookAt(&thePos);
			return;
		}
		if (m_mode == 4) {
			m_time50 = timeToUpdate;
			m_drawCalls88 = m_drawCallTotal * 0.01f;
			TheDisplay->getDrawCallStats(g_Va012F0A94);
			g_Va012F0A94[1] /= 100;
			g_Va012F0A94[2] /= 100;
			g_Va012F0A94[0] /= 100;
			m_mode = 3;
			m_settleFrames = 2;
			TheTacticalView->viewSlot07(0);
			TheTacticalView->setZoom(700.0f);
			TheTacticalView->viewSlot49(2.2f);
			return;
		}
		if (m_mode == 3) {
			m_time58 = timeToUpdate;
			m_mode = 1;
			m_settleFrames = 2;
			if (TheParticleSystemManager->getParticleCount() > 1)
				TheParticleSystemManager->reset();
			TheTacticalView->viewSlot49(1.0f);
			TheTacticalView->setZoom(g_rva012B44BCSavedZoom);
			TheTacticalView->lookAt(&thePos);
			return;
		}
		if (m_mode == 1) {
			m_time68 = timeToUpdate;
			m_mode = 2;
			m_drawCalls8C = m_drawCallTotal * 0.01f;
			bool gotSpawn = false;
			for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->m_next) {
				const ThingTemplate *keep = m_curThing;
				if (obj->getTemplate() != keep && !((const BFMEActionObject *)obj)->testStatus(0x25)) {
					TheGameLogic->destroyObject(obj);
					gotSpawn = true;
				}
			}
			if (gotSpawn) {
				m_settleFrames = 2;
				return;
			}
		}
		if (m_mode == 2) {
			m_time70 = timeToUpdate;
			m_drawCalls90 = m_drawCallTotal * 0.01f;
		}
		if (m_curThing == 0)
			return;

		AsciiString line;
		AsciiString thingName = m_curThing->getName();
		if (m_veryFirstTime)
			thingName = "No Object";
		{
			AsciiString type;
			if (m_unitTypes == 0)
				type = "Infantry";
			else if (m_unitTypes == 1)
				type = "Machine";
			else if (m_unitTypes == 3)
				type = "Monster";
			else if (m_unitTypes == 2)
				type = "Cavalry";
			else if (m_unitTypes == 4)
				type = "Structure";
			else
				type = "Other";
			AsciiString modelName;
			Rva001701A0Record state;
			((Rva001C2B80 *)&state)->clear();
			// Retail reads begin/end straight off the template; going through a
			// ModuleInfo reference leaves a dead `add eax,0x2a0`.
			const ModuleInfo::Nugget *b = m_curThing->getDrawModuleInfo().m_begin;
			Int cnt = m_curThing->getDrawModuleInfo().m_end - b;
			if (cnt > 0) {
				const ModuleData *mdd = (0 < (UnsignedInt)cnt) ? b[0].second : 0;
				if (mdd)
					modelName = mdd->getBestModelNameForWB(state);
			}
			if (m_veryFirstTime) {
				modelName = "**NO MODEL**";
				m_veryFirstTime = false;
			}
			line.format("%.1f,%d/%d/%d,%.1f,%.1f,%.1f,%.1f,%s,%s,%s,%s,%.1f,%.1f,%.1f\n", m_time50,
				g_Va012F0A94[0], g_Va012F0A94[1], g_Va012F0A94[2],
				m_time58, m_time68, m_time70, m_time78,
				thingName.str(), modelName.str(), type.str(), m_side.str(),
				m_drawCalls88, m_drawCalls8C, m_drawCalls90);
			((BfmeThingDYC *)this)->bfmeGoDYC((void *)line.str());
		}
		TheParticleSystemManager->reset();
		m_gotUnit = false;
	}

	if (hasText(m_singleUnit) && m_curThing && m_startTiming) {
		if (m_curThing->getName() == m_singleUnit) {
			((Rva00382AA0 *)this)->release();
			return;
		}
		while (m_curThing->friend_getNextTemplate()) {
			const ThingTemplate *next = m_curThing->friend_getNextTemplate();
			if (next->getName().StringBase<char>::compare(m_singleUnit) == 0)
				break;
			m_curThing = next;
		}
	}

	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->m_next)
		TheGameLogic->destroyObject(obj);
	TheTerrainVisual->m_base04.slot04();

	if (!m_startTiming || !m_curThing || m_gotUnit)
		return;
	TheWritableGlobalData->m_framesPerSecondLimit = 10000;
	TheWritableGlobalData->m_useFpsLimit = false;
	while (!m_gotUnit) {
		if (m_veryFirstTime) {
			m_gotUnit = true;
			break;
		}
		m_curThing = m_curThing->friend_getNextTemplate();
		if (m_curThing == 0) {
			m_unitTypes++;
			if (m_unitTypes == 6) {
				m_startTiming = false;
				((Rva00382AA0 *)this)->release();
				TheMessageStream->appendMessage(0x1d);
				break;
			}
			m_curThing = TheThingFactory->firstTemplate();
		}

		const ThingTemplate *btt = m_curThing;
		if (!(btt->getName() == m_singleUnit) && m_side.isNotEmpty()) {
			if (btt->getDefaultOwningSide().compareNoCase(m_side) != 0)
				continue;
			if (m_unitTypes == 0) {
				if (!btt->isKindOf(KINDOF_INFANTRY)) continue;
				if (btt->isKindOf(KINDOF_MACHINE)) continue;
				if (btt->isKindOf(KINDOF_STRUCTURE)) continue;
			} else if (m_unitTypes == 1) {
				if (!btt->isKindOf(KINDOF_MACHINE)) continue;
				if (btt->isKindOf(KINDOF_MONSTER)) continue;
				if (btt->isKindOf(KINDOF_STRUCTURE)) continue;
			} else if (m_unitTypes == 2) {
				if (!btt->isKindOf(KINDOF_CAVALRY)) continue;
				if (btt->isKindOf(KINDOF_MACHINE)) continue;
				if (btt->isKindOf(KINDOF_MONSTER)) continue;
				if (btt->isKindOf(KINDOF_STRUCTURE)) continue;
			} else if (m_unitTypes == 3) {
				if (!btt->isKindOf(KINDOF_MONSTER)) continue;
				if (btt->isKindOf(KINDOF_STRUCTURE)) continue;
			} else if (m_unitTypes == 4) {
				if (!btt->isKindOf(KINDOF_STRUCTURE)) continue;
			} else {
				if (btt->isKindOf(KINDOF_INFANTRY)) continue;
				if (btt->isKindOf(KINDOF_CAVALRY)) continue;
				if (btt->isKindOf(KINDOF_STRUCTURE)) continue;
				if (btt->isKindOf(KINDOF_MACHINE)) continue;
				if (btt->isKindOf(KINDOF_MONSTER)) continue;
			}
		}
		if (btt->getName().startsWith("CINE")) continue;
		if (btt->getName().compare("GLAInfantryAngryMobNexus") == 0) continue;
		if (btt->getName().compare("FlockOfBirds") == 0) continue;
		if (btt->m_editorSorting == 13) continue;
		if (m_singleUnit.isNotEmpty() && btt->getName().compareNoCase(m_singleUnit) != 0) continue;

		for (Int i = 0; i < 10; i++) {
			for (Int j = 0; j < 10; j++) {
				Coord3D pos;
				pos.x = 20 * i + 300.0f;
				pos.y = 20 * j + 300.0f;
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
				if (!btt->isKindOf((KindOfType)0x63) && !btt->isKindOf((KindOfType)0x5d) && !btt->isKindOf((KindOfType)0x5e)) {
					Team *team = ThePlayerList->getNthPlayer(1)->getDefaultTeam();
					Object *obj = TheThingFactory->newObject(btt, team, ObjectStatusMaskType(), 0);
					if (obj == 0)
						break;
					m_gotUnit = true;
					obj->setOrientation(0);
					obj->setPosition(&pos);
					for (BehaviorModule **m = obj->m_behaviors; *m; ++m) {
						CreateModuleInterface *create = (*m)->getCreate();
						if (!create)
							continue;
						create->onBuildComplete();
					}
					team->setActive();
					TheAI->pathfinder()->addObjectToPathfindMap(obj);
				} else {
					Real scale = btt->m_assetScale;
					Matrix3D mtx(true);
					if (btt->isKindOf((KindOfType)0x5d))
						TheTerrainLogic->rva001AD080(btt, &pos, &mtx, scale);
					else if (btt->isKindOf((KindOfType)0x5e))
						TheTerrainLogic->rva001A7A90(btt, &pos, &mtx, scale);
					else
						TheTerrainLogic->rva001A34C0(btt, &pos, &mtx, scale);
					m_gotUnit = true;
				}
			}
		}
	}
	if (m_gotUnit) {
		m_settleFrames = 4;
		if (m_veryFirstTime) {
			HideControlBar(true);
			m_settleFrames *= 100;
		}
		Coord3D thePos;
		thePos.x = 800;
		thePos.y = 800;
		thePos.z = 0;
		TheTacticalView->lookAt(&thePos);
		m_mode = 0;
	}
}
