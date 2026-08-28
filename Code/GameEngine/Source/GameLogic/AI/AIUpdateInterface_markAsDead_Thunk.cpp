// cl: /DNDEBUG /MD /EHsc
// readable body of ?markAsDead@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// Open-BFME5: AIUpdateInterface::markAsDead, retail 0x0026EE80.
//
// Same reason this lives beside setQueueForPathTime's thunk rather than in
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp: that TU's
// vendored AIUpdate.h (reference/shims/aiupdatelayout) gets two class-offset
// constants wrong for this body, both already characterised there:
//
//     target:   8b 4e 08              mov ecx,[esi+0x08]     getObject()  (m_obj)
//     AIUpdate: 8b 4e 0c              mov ecx,[esi+0x0c]
//     target:   c6 86 2b 03 00 00 01  mov byte[esi+0x32b],1  m_isAiDead
//     AIUpdate: c6 86 11 02 00 00 01  mov byte[esi+0x211],1
//     target:   8a 86 30 03 00 00     mov al,[esi+0x330]     m_isInUpdate
//     AIUpdate: 8a 86 16 02 00 00     mov al,[esi+0x216]
//
// The two flag offsets (0x32b, 0x330) sit 5 bytes apart in BOTH retail and
// the header-driven compile (0x211, 0x216) -- m_isAiDead is declared
// immediately before m_isInUpdate in both layouts, so the +0x11a drift here
// is a block shift of everything from m_isAiDead onward, not a re-derivation
// of two independent offsets. It is the SAME +0x11a delta already logged for
// m_isInUpdate alone in setQueueForPathTime's thunk and in
// AIUpdateInterface::friend_notifyStateMachineChanged's body comment. The
// m_obj delta (+0x08 retail vs +0x0c header) is the separate, smaller,
// OPPOSITE-signed shift documented in both those places too -- the two drifts
// do not share one constant, so nothing here is a "uniform +4" fix; it is two
// independently-measured deltas applied to the fields that actually carry
// them. Nothing else in AIUpdateInterface's layout is asserted by this file.
//
// wakeUpNow() is fully inlined into markAsDead here exactly as it is inlined
// into friend_notifyStateMachineChanged; there is no separate call in the
// retail bytes.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setEffectivelyDead( bool isEffectivelyDead );
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE		= 1,
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
private:
	char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	// Undefined: it exists so the vptr occupies +0x00.
	virtual ~UpdateModule();

	Object *getObject( void ) const { return m_obj; }

protected:
	UpdateSleepTime getWakeFrame( void ) const;								///< ILT 0x000176C5
	void setWakeFrame( Object *obj, UpdateSleepTime whenToWakeUp );			///< ILT 0x000157DA -> 0x002B2040

	char m_unreconstructed_04[4];
	Object *m_obj;								///< retail this+0x08
	char m_unreconstructed_0c[0x20 - 0x0c];		///< brings UpdateModule to 0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	void markAsDead();

private:
	char m_unreconstructed_24[0x32b - 0x24];
	bool m_isAiDead;							///< retail this+0x32b
	char m_unreconstructed_32c[0x330 - 0x32c];
	bool m_isInUpdate;							///< retail this+0x330
};

// ?markAsDead@AIUpdateInterface@@QAEXXZ
void AIUpdateInterface::markAsDead()
{
	m_isAiDead = true;
	getObject()->setEffectivelyDead(true);

	// wakeUpNow(), spelled out.
	if (getWakeFrame() > UPDATE_SLEEP_NONE && !m_isInUpdate)
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
