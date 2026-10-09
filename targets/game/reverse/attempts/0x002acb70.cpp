// ??0StealthUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc
// readable body of ??0StealthUpdate@@: game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp
//
// Retail 0x002ACB70, 252 bytes (ret 8 at +0xF9). BFME keeps the Zero Hour
// constructor order minus the pulse phase, the black-market frame and the
// granted-by-special-power branch, and adds four flags at +0x2D..+0x30.

#include <string.h>

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, int bit)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[bit >> 5] |= 1u << (bit & 31);
	}

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

enum
{
	OBJECT_STATUS_CAN_STEALTH = 18
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, bool set = true);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
struct StealthUpdateModuleData
{
	unsigned char m_pad00[0x08];
	unsigned int m_stealthDelay;		///< +0x08
	unsigned char m_pad0C[0x2C - 0x0C];
	bool m_teamDisguised;			///< +0x2C
	unsigned char m_pad2D[0x50 - 0x2D];
	bool m_innateStealth;			///< +0x50
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;		///< +0x04
	Object *m_object;			///< +0x08
};

class BehaviorModuleInterface { public: virtual void slot(); };
class UpdateInterface { public: virtual void slot(); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
                     public BehaviorModuleInterface,
                     public UpdateInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
	{
	}

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;	///< +0x14
	int m_indexInLogic;			///< +0x18
	int m_updateState;			///< +0x1C
};

// Retail [0x012F0898] is EA's GameLogic *TheGameLogic; only the +0x3C frame
// counter is read here, so the view is cast at the use.
struct StealthUpdateGameLogicView
{
	unsigned char m_pad00[0x3C];
	unsigned int m_frame;
};
class GameLogic;
extern GameLogic *TheGameLogic;

class StealthUpdate : public UpdateModule
{
public:
	StealthUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const StealthUpdateModuleData *getStealthUpdateModuleData() const
	{
		return (const StealthUpdateModuleData *)m_moduleData;
	}

	unsigned int m_stealthAllowedFrame;	///< +0x20
	unsigned int m_detectionExpiresFrame;	///< +0x24
	unsigned int m_unknown28;		///< +0x28
	bool m_enabled;				///< +0x2C
	bool m_unknown2D;
	bool m_unknown2E;
	bool m_unknown2F;
	bool m_unknown30;
	int m_disguiseAsPlayerIndex;		///< +0x34
	const void *m_disguiseAsTemplate;	///< +0x38
	unsigned int m_disguiseTransitionFrames;	///< +0x3C
	bool m_disguiseHalfpointReached;	///< +0x40
	bool m_transitioningToDisguise;		///< +0x41
	bool m_disguised;			///< +0x42
	bool m_xferRestoreDisguise;		///< +0x43
};

// ??0StealthUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StealthUpdate::StealthUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();

	m_stealthAllowedFrame = ((StealthUpdateGameLogicView *)TheGameLogic)->m_frame + data->m_stealthDelay;
	m_enabled = !data->m_teamDisguised;
	m_detectionExpiresFrame = 0;
	m_unknown28 = 0;
	m_disguiseAsPlayerIndex = -1;
	m_disguiseAsTemplate = 0;
	m_transitioningToDisguise = false;
	m_disguised = false;
	m_disguiseTransitionFrames = 0;
	m_disguiseHalfpointReached = false;
	m_unknown2D = false;
	m_unknown2E = false;
	m_unknown2F = false;
	m_unknown30 = true;

	if (data->m_innateStealth)
		getObject()->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, OBJECT_STATUS_CAN_STEALTH));

	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

	m_xferRestoreDisguise = false;
}
