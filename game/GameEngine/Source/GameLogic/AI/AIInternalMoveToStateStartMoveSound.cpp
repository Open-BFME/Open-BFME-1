// ?startMoveSound@AIInternalMoveToState@@AAEXXZ
// byte-exact: probe EXACT (modulo relocations), ours=566 retail=566.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring8 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// AIInternalMoveToState::startMoveSound, retail RVA 0x0016E6C0, 566 bytes.
//
// The readable Zero Hour body is game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// and the retail bytes came from the 2026-08-11 Open-BFME5 lift that used to
// carry them.  BFME reshaped the ZH function in four ways, all visible in the
// disassembly and all reproduced below:
//
//   1. The template is fetched ONCE, before the damage test, and a null one
//      returns immediately (0x0016E6F2 calls vslot +0x28 into EBP; 0x0016E6F9
//      `je 0x0016E8DE` is the shared epilogue).  ZH re-read
//      obj->getTemplate() inside every branch.
//   2. getBodyModule() is a plain field read at Object+0x200 (0x0016E6E6), not
//      a virtual call, and the damage test is `state > BODY_DAMAGED`
//      (0x0016E715 `cmp eax,1` / `jle`), which is what IS_CONDITION_WORSE
//      expands to with BODY_DAMAGED == 1.
//   3. The damaged arm plays the LOOP event (slot 0x56) UNCONDITIONALLY after
//      the start event (0x0016E76A follows 0x0016E768 with no branch), and both
//      arms set a `played` flag that suppresses the trailing normal move-loop
//      block (0x0016E7E4 / 0x0016E845).
//   4. Each loop event first stops whatever ambient handle is still playing --
//      `TheAudioClientUpdate != 0 && m_ambientPlayingHandle >= 5` then
//      vslot +0x4C (0x0016E796, 0x0016E88F) -- which ZH has no equivalent of.
//      The 5 threshold and the handle type are the BFME spelling already landed
//      in Rva003720F0AudioRefresh.cpp and AIInternalMoveToState_onEnter.cpp.
//
// The slot numbers are retail's own: getSound(0x54/0x56/0x53/0x55) reaches
// ThingTemplate::getSound(Int) by value, and BFME's audio table has entries the
// ZH ThingTemplateAudioType does not, so the four indices are the honest
// spelling.  ZH's getSoundMoveStartDamaged() and friends are the same four
// events in a table that starts 0x47 entries earlier.
#include "Common/AsciiString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int AudioHandle;

enum ObjectID { INVALID_ID = 0 };

// The retail AudioEventRTS destructor, copy constructor and assignment are
// non-virtual (`??1AudioEventRTS@@QAE@XZ` and friends), so this shim carries no
// vtable: the locals are 0x70 bytes each (the landed AudioEventRTS ends with
// an AsciiString at +0x6C) and the event name is read at local+0x14
// (0x0016E731 `[esp+0x30]` with the local base at `[esp+0x1c]`).
// isEmpty() is the inlined AsciiString test retail emits, `test eax,eax` then
// `cmp word ptr [eax+4],0`, which is what the asciistring8 shim spells.
class AudioEventRTS
{
public:
	unsigned char m_pad00[0x14];
	AsciiString m_eventName;
	unsigned char m_pad18[0x70 - 0x18];

	AudioEventRTS(const AudioEventRTS &right);
	AudioEventRTS &operator=(const AudioEventRTS &right);
	~AudioEventRTS();

	const AsciiString &getEventName() const { return m_eventName; }
	void setObjectID(ObjectID objID);
};

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
// Only the damage enum and the comparison macro this body reads, so the real
// header -- and the BodyModuleInterface it declares -- stay out of the TU.
enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE,
	BODYDAMAGETYPE_COUNT
};

#define IS_CONDITION_WORSE(a, b) (a > b)

// getTemplate() is vslot +0x28 (0x0016E6F2) and the object ID is the field at
// +0x74 (0x0016E74B), the same offset AIInternalMoveToState::onEnter reads at
// 0x0017265E.  The body module is the field at +0x200 (0x0016E6E6), one dword
// below the AI update pointer onEnter reads at 0x00172634.
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	// vslot +0x20 (0x0016E712).  ZH declares this accessor eleventh, after the
	// three subdual-damage virtuals BFME's BodyModuleInterface does not carry;
	// dropping that block is what puts getDamageState() at index 8.
	virtual BodyDamageType getDamageState() const = 0;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual const ThingTemplate *getTemplate() const = 0;
	// The build's vftable pointer occupies four bytes whatever the virtual count
	// (AIInternalMoveToState_onEnter.cpp lays its own shim out that way and is
	// byte-exact), so the pads below start at +0x04 while the vcall itself still
	// goes through slot 10 at +0x28.
	unsigned char m_pad04[0x74 - 0x04];
	ObjectID m_id;
	unsigned char m_pad78[0x200 - 0x78];
	BodyModuleInterface *m_body;

	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
};

// Vtable 0x0111C0C0: +0x44 addAudioEvent (0x0016E765) and +0x4C
// removeAudioEvent (0x0016E7A5), the pair Rva003720F0AudioRefresh.cpp already
// names at those two slots.
class Rva005A00B0AudioClient
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual AudioHandle addAudioEvent(const AudioEventRTS *eventToAdd) = 0;
	virtual void slot18() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void slot00() = 0;
	unsigned char m_pad04[0x1c - 0x04];
	StateMachine *m_machine;
	unsigned char m_pad20[0x40 - 0x20];
	AudioHandle m_ambientPlayingHandle;

	Object *getMachineOwner() const { return m_machine->m_owner; }

private:
	// ZH AIStateMachine.h declares startMoveSound() under this access specifier,
	// and the retail mangling ?startMoveSound@AIInternalMoveToState@@AAEXXZ
	// carries it: the second A is __thiscall behind a PRIVATE first A.
	void startMoveSound(void);
};

// The audio table indices this body reads.  ZH's ThingTemplateAudioType numbers
// the same four events 12..15; BFME's table has 0x47 extra entries in front, so
// the retail numbers are what the code says.
enum
{
	BFME_SLOT_MOVE_START = 0x53,
	BFME_SLOT_MOVE_START_DAMAGED = 0x54,
	BFME_SLOT_MOVE_LOOP = 0x55,
	BFME_SLOT_MOVE_LOOP_DAMAGED = 0x56
};

// ?startMoveSound@AIInternalMoveToState@@AAEXXZ
void AIInternalMoveToState::startMoveSound(void)
{
	// Retail keeps `this` in ECX and spills it once at 0x0016E6EC instead of
	// dedicating a register to it, which is what naming the pointer buys.
	AIInternalMoveToState *state = this;
	Object *obj = getMachineOwner();
	// The body module is a field, so retail reads it before the template call
	// (0x0016E6E6 against 0x0016E6F2) and the source order has to match.
	const BodyModuleInterface *objBody = obj->getBodyModule();
	const ThingTemplate *objTemplate = obj->getTemplate();
	if (objTemplate == 0)
		return;

	bool moveStartPlayed = false;
	bool moveLoopPlayed = false;
	if (objBody && IS_CONDITION_WORSE(objBody->getDamageState(), BODY_DAMAGED))
	{
		AudioEventRTS soundEventMoveDamaged =
			*objTemplate->getSound(BFME_SLOT_MOVE_START_DAMAGED);
		if (!soundEventMoveDamaged.getEventName().isEmpty())
		{
			soundEventMoveDamaged.setObjectID(obj->getID());
			TheAudioClientUpdate->addAudioEvent(&soundEventMoveDamaged);
			moveStartPlayed = true;
		}

		soundEventMoveDamaged = *objTemplate->getSound(BFME_SLOT_MOVE_LOOP_DAMAGED);
		if (!soundEventMoveDamaged.getEventName().isEmpty())
		{
			if (TheAudioClientUpdate != 0 && state->m_ambientPlayingHandle >= 5)
				TheAudioClientUpdate->removeAudioEvent(state->m_ambientPlayingHandle);
			soundEventMoveDamaged.setObjectID(obj->getID());
			state->m_ambientPlayingHandle =
				TheAudioClientUpdate->addAudioEvent(&soundEventMoveDamaged);
			moveLoopPlayed = true;
		}
	}

	// Not an else: retail re-tests the start flag after the damaged arm at
	// 0x0016E7E4 (bl), then the loop flag again before the ambient block at
	// 0x0016E845 (stack slot [esp+0x13]). Two flags: the damaged start only
	// suppresses the normal start, the damaged loop only the normal loop.
	if (!moveStartPlayed)
	{
		AudioEventRTS soundEventMove = *objTemplate->getSound(BFME_SLOT_MOVE_START);
		if (!soundEventMove.getEventName().isEmpty())
		{
			soundEventMove.setObjectID(obj->getID());
			TheAudioClientUpdate->addAudioEvent(&soundEventMove);
		}
	}

	if (!moveLoopPlayed)
	{
		AudioEventRTS soundEventMoveLoop = *objTemplate->getSound(BFME_SLOT_MOVE_LOOP);
		if (!soundEventMoveLoop.getEventName().isEmpty())
		{
			if (TheAudioClientUpdate != 0 && state->m_ambientPlayingHandle >= 5)
				TheAudioClientUpdate->removeAudioEvent(state->m_ambientPlayingHandle);
			soundEventMoveLoop.setObjectID(obj->getID());
			state->m_ambientPlayingHandle =
				TheAudioClientUpdate->addAudioEvent(&soundEventMoveLoop);
		}
	}
}

// ---------------------------------------------------------------------------
// BYTE-EXACT. The last wall was a single bool read as one flag: retail keeps
// TWO flags. `moveStartPlayed` lives in bl (xor bl,bl init, mov bl,1 set,
// test bl,bl at +0x124 guarding the 0x53 block) and `moveLoopPlayed` lives in
// the stack slot at [esp+0x13] (mov [esp+0x13],bl init, mov byte [esp+0x13],1
// set, mov al,[esp+0x13] reload at +0x185 guarding the 0x55 block, with the
// early pop ebx between reload and jump). The damaged start only suppresses
// the normal start; the damaged loop only suppresses the normal loop. The
// second lever was the AudioEventRTS size: 0x70 (AsciiString tail at +0x6C),
// not 0x6C -- two temp slots times 4 bytes closed the frame gap
// (sub esp 0xe8) and aligned every local.
