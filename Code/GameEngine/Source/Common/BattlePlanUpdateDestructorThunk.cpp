// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BattlePlanUpdate's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape from OpenContain: the UpdateModule base's vptrs
// at 0x00, 0x0C and 0x10, one interface base at 0x20, the inlined ~UpdateModule
// and ~BehaviorModule vptr restores, and the out-of-line base destructor at
// 0x00113D40.
//
// One member: a 4x4 array of 0x70-byte elements at 0x44, destroyed through the
// eh vector destructor iterator with count 0x10 and stride 0x70. Its element
// destructor is declared and never defined here, so the pushed address stays
// the DIR32 the comparison masks -- the identity is unknown.
//
// The body ahead of it is the nested loop retail unrolls as 4 outer by 4 inner:
// for every element it reads the word at element+0x0C -- the loop pointer
// starts at this+0x50, twelve past the array -- and passes it to vtable slot
// 0x4C of the global at 0x012ED668, stepping 0x70 bytes each time. The element
// stride the loop walks and the stride the iterator is given agree, which is
// what ties the loop to the same array.
//
// The named local for the argument is load-bearing, not style: retail loads the
// element word before it loads the global, and writing the member access
// directly in the argument list makes MSVC evaluate the callee's object first.
// Same instructions, opposite order.

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113d40
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;					///< out to sizeof() == 0x20
};

// Element of the 4x4 array. Non-trivially destructible; only its size and its
// destructor's address reach the bytes, and the address is masked.
class BattlePlanUpdateSlot
{
public:
	~BattlePlanUpdateSlot();

	unsigned char m_unreconstructed_00[0x0c];
	void *m_handle;										///< element+0x0C

private:
	unsigned char m_unreconstructed_10[0x60];
};

// Only slot 0x4C is used; the slots ahead of it are placeholders that put it at
// the offset the call site encodes.
class BattlePlanUpdateOwner
{
public:
	virtual void slot00();	virtual void slot04();	virtual void slot08();
	virtual void slot0c();	virtual void slot10();	virtual void slot14();
	virtual void slot18();	virtual void slot1c();	virtual void slot20();
	virtual void slot24();	virtual void slot28();	virtual void slot2c();
	virtual void slot30();	virtual void slot34();	virtual void slot38();
	virtual void slot3c();	virtual void slot40();	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(void *arg);
};

extern BattlePlanUpdateOwner *TheBattlePlanUpdateOwner;

// Plain virtual rather than a virtual destructor: retail gives this subobject a
// vptr write and no unwind state.
class BattlePlanUpdateSecondaryBase
{
public:
	virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanUpdate
	: public UpdateModule,
	  public BattlePlanUpdateSecondaryBase				///< vptr at 0x20
{
protected:
	virtual ~BattlePlanUpdate();

private:
	unsigned char m_unreconstructed_24[0x20];
	BattlePlanUpdateSlot m_slots[4][4];					///< retail this+0x44
};

// ??1BattlePlanUpdate@@MAE@XZ
BattlePlanUpdate::~BattlePlanUpdate()
{
	for (int plan = 0; plan < 4; ++plan)
	{
		for (int slot = 0; slot < 4; ++slot)
		{
			void *handle = m_slots[plan][slot].m_handle;
			TheBattlePlanUpdateOwner->slot4c(handle);
		}
	}
}
