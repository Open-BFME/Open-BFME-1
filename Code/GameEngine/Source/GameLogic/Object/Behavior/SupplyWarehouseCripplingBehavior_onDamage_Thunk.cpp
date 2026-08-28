// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SupplyWarehouseCripplingBehavior::onDamage, retail 0x0020D770.
//
// The Zero Hour body unchanged, three lines of it. What the bytes settle is the
// layout around it, and all of it agrees with what the AIUpdateInterface bodies
// landed earlier today:
//
//   lea edi,[esi-0x20]   `this` is the DamageModuleInterface subobject, so
//                        UpdateModule is exactly 0x20 bytes -- the same width
//                        AIUpdateInterface::privateGetHealed pins from the
//                        other side, where AICommandInterface starts at +0x20
//   mov ecx,[esi-0x18]   getObject(), object+0x08
//   mov eax,[esi+0x04]   m_healingSupressedUntilFrame, object+0x24 -- the first
//                        member past the 0x20 base
//   call [edx+0x2c]      resetSelfHealSupression, slot 11 of the *primary*
//                        vtable: it is declared in this class but lands in
//                        UpdateModule's table, not the interface's
//
// TheGameLogic is 0x012F0898 and getFrame() inlines to its +0x3c.

class Object;
class DamageInfo;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE		= 1,
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};

#define UPDATE_SLEEP(numFrames)				((UpdateSleepTime)(numFrames))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame( void ) const { return m_frame; }

private:
	char m_unreconstructed_00[0x3c];
	unsigned int m_frame;						///< retail this+0x3c
};

extern GameLogic *TheGameLogic;					///< retail 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	// Eleven slots before the one this class adds. Only their count is known;
	// retail reaches resetSelfHealSupression at [vtable+0x2c], which is slot 11.
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;

protected:
	void setWakeFrame( Object *obj, UpdateSleepTime whenToWakeUp );		///< ILT 0x000157DA -> 0x002B2040

	Object *getObject( void ) const { return m_obj; }

	char m_unreconstructed_04[4];
	Object *m_obj;								///< retail this+0x08
	char m_unreconstructed_0c[0x20 - 0x0c];		///< brings UpdateModule to 0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModuleInterface
{
public:
	virtual void onDamage( DamageInfo *damageInfo ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseCripplingBehavior.h
class SupplyWarehouseCripplingBehavior : public UpdateModule,
																				 public DamageModuleInterface
{
public:
	virtual void onDamage( DamageInfo *damageInfo );

protected:
	virtual void resetSelfHealSupression();		///< primary vtable slot 11

private:
	unsigned int m_healingSupressedUntilFrame;	///< retail object+0x24
	unsigned int m_nextHealingFrame;			///< retail object+0x28
};

// ?onDamage@SupplyWarehouseCripplingBehavior@@UAEXPAVDamageInfo@@@Z
void SupplyWarehouseCripplingBehavior::onDamage( DamageInfo *damageInfo )
{
	unsigned int now = TheGameLogic->getFrame();
	resetSelfHealSupression();
	setWakeFrame(getObject(), UPDATE_SLEEP(m_healingSupressedUntilFrame - now));// we got hit, time to get up for work after a quick snooze
}
