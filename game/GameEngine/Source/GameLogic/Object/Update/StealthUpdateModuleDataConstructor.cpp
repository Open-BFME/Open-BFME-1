// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// StealthUpdateModuleData's constructor, retail 0x0012A3A0, 372 bytes.
//
// The ModuleFactory registration for StealthUpdate reaches the module data
// factory at 0x0012A680. That factory allocates 0x324 bytes and calls this body,
// which names the body and sets the class size at 0x324 bytes. The last dword
// this body writes sits at +0x320, so the two figures agree.
//
// The same factory hands INI::initFromINIMultiProc the field-parse forwarder at
// 0x002AC120, and that forwarder registers the FieldParse table at 0x010C41C0.
// Every field name and member offset below is read out of that table. Members
// the table never names carry their offsets instead.
//
// tools/eh_info.py reads the unwind map behind the handler at 0x00C02154 and
// lists eight tracked objects. State 0 destroys the object at this+0 through
// 0x00122D40, state 1 destroys the object at this+0x64 through 0x000658A0, and
// states 2 through 7 destroy this+0x70, +0xE0, +0x150, +0x1C0, +0x230 and
// +0x2A0 through 0x000B31F0. So the base at +0x00 has a destructor, the member
// at +0x64 is the vector of AsciiString whose destructor is 0x000658A0, and the
// six members from +0x70 on are AudioEventRTS. The body at 0x00122D40 stores
// 0x01073744, which the ledger spells ??_7BfmeBaseVUQ@@6B@, so the base
// destructor restores that vptr.
//
// Declaring the base destructor is what takes this body from 43 differing bytes
// to exact. Without it MSVC tracks seven objects instead of eight, every EH
// state constant comes out one low, and the final state store lands thirteen
// instructions early.
//
// The member at +0x10 clears twelve bytes twice, once when it is built and once
// from the body. Writing those as three field assignments makes MSVC fold both
// runs onto [esi+0x10] and drop the EBP save. Writing them as one memset makes
// MSVC compute lea ebp,[esi+0x10] once and store through a copy in ECX, which is
// what retail does.
//
// Retail builds each AudioEventRTS with the shared empty AsciiString at
// 0x01336E50 and the value 0, the same two arguments MiscAudio::MiscAudio uses
// for its 32 members.

#include <vector>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// The empty-string global the six audio members take. Declared here the way
// MiscAudio::MiscAudio declares it, because ascii_string.h does not carry it.
class AsciiString
{
public:
	AsciiString();
	~AsciiString();

	static const AsciiString TheEmptyString;

private:
	char *m_text;
};

class FXList;

// Retail builds these with one call each, so both stay declared and undefined.
// The complete owner has a virtual destructor. This TU only makes direct
// subobject calls and emits no vtable of its own.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	~AudioEventRTS();

private:
	void *m_vptr;
	unsigned char m_bfmeData[0x6C];
};

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// The base supplies the vptr at +0x00 and one dword at +0x04 that retail never
// stores to.
class BfmeModuleDataBase
{
public:
	virtual ~BfmeModuleDataBase() {}

	virtual void slot();

private:
	char m_bfmePad[0x08 - 0x04];
};

// HintDetectableConditions parses through BitFlags<45>::parseFromINI and covers
// +0x10 to +0x1B. Both its constructor and its clear() zero the same three
// dwords.
extern "C" void *__cdecl memset(void *dst, int c, unsigned int n);
#pragma intrinsic(memset)

struct BfmeStatusFlags
{
	BfmeStatusFlags() { memset(m_bfme, 0, sizeof(m_bfme)); }

	void clear() { memset(m_bfme, 0, sizeof(m_bfme)); }

	UnsignedInt m_bfme[3];
};

// RevealWeaponSets is one dword with the same two-step shape.
struct BfmeWeaponSetFlags
{
	BfmeWeaponSetFlags() : m_bfme00(0) {}

	void clear() { m_bfme00 = 0; }

	UnsignedInt m_bfme00;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdateModuleData : public BfmeModuleDataBase
{
public:
	StealthUpdateModuleData();

	virtual void slot();

	UnsignedInt m_stealthDelay;			// +0x008  StealthDelay
	UnsignedInt m_stealthForbiddenConditions;	// +0x00C  StealthForbiddenConditions
	BfmeStatusFlags m_hintDetectableConditions;	// +0x010  HintDetectableConditions
	Real m_moveThresholdSpeed;			// +0x01C  MoveThresholdSpeed
	Real m_friendlyOpacityMin;			// +0x020  FriendlyOpacityMin
	Real m_friendlyOpacityMax;			// +0x024  FriendlyOpacityMax
	UnsignedInt m_pulseFrequency;			// +0x028  PulseFrequency
	bool m_disguisesAsTeam;				// +0x02C  DisguisesAsTeam
	Real m_revealDistanceFromTarget;		// +0x030  RevealDistanceFromTarget
	bool m_orderIdleEnemiesToAttackMeUponReveal;	// +0x034  OrderIdleEnemiesToAttackMeUponReveal
	FXList *m_disguiseRevealFX;			// +0x038  DisguiseRevealFX
	FXList *m_disguiseFX;				// +0x03C  DisguiseFX
	FXList *m_becomeStealthedFX;			// +0x040  BecomeStealthedFX
	FXList *m_exitStealthFX;			// +0x044  ExitStealthFX
	FXList *m_becomeStealthedOneRingFX;		// +0x048  BecomeStealthedOneRingFX
	FXList *m_exitStealthOneRingFX;			// +0x04C  ExitStealthOneRingFX
	bool m_startsActive;				// +0x050  StartsActive
	bool m_innateStealth;				// +0x051  InnateStealth
	bool m_detectedByFriendliesOnly;		// +0x052  DetectedByFriendliesOnly
	UnsignedInt m_disguiseTransitionTime;		// +0x054  DisguiseTransitionTime
	UnsignedInt m_disguiseRevealTransitionTime;	// +0x058  DisguiseRevealTransitionTime
	Real m_detectedByAnyoneRange;			// +0x05C  DetectedByAnyoneRange
	BfmeWeaponSetFlags m_revealWeaponSets;		// +0x060  RevealWeaponSets
	_STL::vector<AsciiString> m_removeTerrainRestrictionOnUpgrade;	// +0x064  RemoveTerrainRestrictionOnUpgrade
	AudioEventRTS m_voiceMoveToStealthyArea;		// +0x070
	AudioEventRTS m_voiceMoveToStealthyAreaGroup;		// +0x0E0
	AudioEventRTS m_voiceMoveToStealthyArea2;		// +0x150
	AudioEventRTS m_voiceMoveToStealthyAreaGroup2;		// +0x1C0
	AudioEventRTS m_voiceEnterStateMoveToStealthyArea;	// +0x230
	AudioEventRTS m_voiceEnterStateMoveToStealthyArea2;	// +0x2A0
	UnsignedInt m_oneRingDelayOn;			// +0x310  OneRingDelayOn
	UnsignedInt m_oneRingDelayOff;			// +0x314  OneRingDelayOff
	UnsignedInt m_ringAnimTimeOn;			// +0x318  RingAnimTimeOn
	UnsignedInt m_ringAnimTimeOff;			// +0x31C  RingAnimTimeOff
	UnsignedInt m_ringDelayAfterRemoving;		// +0x320  RingDelayAfterRemoving
};

// ??0StealthUpdateModuleData@@QAE@XZ
StealthUpdateModuleData::StealthUpdateModuleData() :
	m_voiceMoveToStealthyArea(AsciiString::TheEmptyString, 0),
	m_voiceMoveToStealthyAreaGroup(AsciiString::TheEmptyString, 0),
	m_voiceMoveToStealthyArea2(AsciiString::TheEmptyString, 0),
	m_voiceMoveToStealthyAreaGroup2(AsciiString::TheEmptyString, 0),
	m_voiceEnterStateMoveToStealthyArea(AsciiString::TheEmptyString, 0),
	m_voiceEnterStateMoveToStealthyArea2(AsciiString::TheEmptyString, 0)
{
	m_disguiseFX = 0;
	m_disguiseRevealFX = 0;
	m_becomeStealthedFX = 0;
	m_exitStealthFX = 0;
	m_becomeStealthedOneRingFX = 0;
	m_exitStealthOneRingFX = 0;
	m_stealthDelay = 0xFFFFFFFF;
	m_stealthForbiddenConditions = 0;
	m_hintDetectableConditions.clear();
	m_moveThresholdSpeed = 0.0f;
	m_friendlyOpacityMin = 0.5f;
	m_friendlyOpacityMax = 1.0f;
	m_pulseFrequency = 30;
	m_disguisesAsTeam = false;
	m_revealDistanceFromTarget = 0.0f;
	m_orderIdleEnemiesToAttackMeUponReveal = false;
	m_startsActive = true;
	m_innateStealth = true;
	m_detectedByFriendliesOnly = false;
	m_disguiseTransitionTime = 0;
	m_disguiseRevealTransitionTime = 0;
	m_detectedByAnyoneRange = 0.0f;
	m_revealWeaponSets.clear();
	m_removeTerrainRestrictionOnUpgrade.clear();
	m_oneRingDelayOn = 10;
	m_oneRingDelayOff = 10;
	m_ringAnimTimeOn = 0;
	m_ringAnimTimeOff = 0;
	m_ringDelayAfterRemoving = 0;
}
