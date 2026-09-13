// cl: /DNDEBUG /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/turretai /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define ASCIISTRING_H
#define _H_AUDIOEVENTRTS_
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Errors.h"
#include "windows.h"

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) { }
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() { }
	AsciiString(const char *text) : StringBase<char>(text) { }
	AsciiString(const AsciiString &other) : StringBase<char>(other) { }
	~AsciiString() { }
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
	bool operator==(const AsciiString &other) const;
	int compareNoCase(const AsciiString &other) const;
	void clear();
	bool isNotEmpty() const;
	static const AsciiString TheEmptyString;
};

#define __SNAPSHOT_H_
class Xfer;
class Snapshot
{
public:
	Snapshot() { }
	~Snapshot() { }

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

#define DEFINE_WEAPONSLOTTYPE_NAMES
#include "Common/GameAudio.h"
#include "Common/AudioEventInfo.h"
#include "Common/GameType.h"

enum OwnerType
{
	OT_Positional, OT_Drawable, OT_Object, OT_Dead, OT_INVALID
};

enum PortionToPlay
{
	PP_Attack, PP_Sound, PP_Decay, PP_Done
};

class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS(const AsciiString& eventName);
	AudioEventRTS(const AsciiString& eventName, int extra);
	virtual ~AudioEventRTS();

protected:
	AsciiString m_filenameToLoad;
	const AudioEventInfo* m_eventInfo;
	AudioHandle m_playingHandle;
	AudioHandle m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	AudioPriority m_priority;
	Real m_volume;
	TimeOfDay m_timeOfDay;
	ObjectID m_objectID;
	OwnerType m_ownerType;
	Coord3D m_positionOfAudio;
	Bool m_shouldFade;
	Bool m_isLogicalAudio;
	Bool m_uninterruptable;
	UnsignedInt m_bfmeUnknown44;
	UnsignedInt m_bfmeUnknown48;
	Real m_pitchShift;
	Real m_volumeShift;
	Real m_delay;
	UnsignedInt m_bfmeUnknown58;
	Int m_playerIndex;
	PortionToPlay m_portionToPlayNext;
	UnsignedInt m_bfmeUnknown64;
	UnsignedInt m_bfmeUnknown68;
	UnsignedInt m_bfmeUnknown6C;
};

class DynamicAudioEventRTS
{
public:
	enum DynamicAudioEventRTSMagicEnum { DynamicAudioEventRTS_GLUE_NOT_IMPLEMENTED = 0 };
	void *operator new(size_t, DynamicAudioEventRTSMagicEnum);
	DynamicAudioEventRTS(const DynamicAudioEventRTS&);
	DynamicAudioEventRTS& operator=(const DynamicAudioEventRTS&);
	void deleteInstance();
	AudioEventRTS m_event;
};

#define Matrix4x4 Matrix4
#include "PreRTS.h"

namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
public: \
	inline void *operator new(size_t) { return ::operator new(0x48); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/INIException.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"

// BFME's state-machine vtable places initDefaultState at +0x1c.  The
// surviving ZH declaration exposes the same method at +0x14, so keep this
// dispatch-only view local to the constructor TU.
class BfmeTurretStateMachineInitDispatch
{
public:
	virtual void _slot0();
	virtual void _slot1();
	virtual void _slot2();
	virtual void _slot3();
	virtual void _slot4();
	virtual void _slot5();
	virtual void _slot6();
	virtual StateReturnType initDefaultState();
};

// ??0TurretAI@@QAE@PAVObject@@PBVTurretAIData@@W4WhichTurretType@@@Z
TurretAI::TurretAI(Object* owner, const TurretAIData* data, WhichTurretType tur) :
	m_owner(owner),
	m_whichTurret(tur),
	m_data(data),
	m_turretStateMachine(NULL),
	m_playRotSound(false),
	m_playPitchSound(false),
	m_positiveSweep(true),
	m_enableSweepUntil(0),
	m_sleepUntil(0),
	m_didFire(false),
	m_target(TARGET_NONE),
	m_targetWasSetByIdleMood(false),
	m_enabled(!data->m_initiallyDisabled),
	m_firesWhileTurning(data->m_firesWhileTurning),
	m_isForceAttacking(false),
	m_turretRotOrPitchSound(AsciiString::TheEmptyString, 0),
	m_victimInitialTeam(NULL)
{
	m_continuousFireExpirationFrame = -1;

	if (!m_data)
	{
		DEBUG_CRASH(("TurretAI MUST have ModuleData"));
		throw INIException(3, "TurretAI MUST have ModuleData");
	}

	if (m_data->m_turretWeaponSlots == 0)
	{
		DEBUG_CRASH(("TurretAI MUST specify controlled weapon slots!"));
		throw INIException(3, "TurretAI MUST specify controlled weapon slots!");
	}
	m_angle = getNaturalTurretAngle();
	m_pitch = getNaturalTurretPitch();

	m_turretStateMachine = new TurretStateMachine(this, m_owner, "TurretStateMachine");
	reinterpret_cast<BfmeTurretStateMachineInitDispatch *>(m_turretStateMachine)->initDefaultState();
}
