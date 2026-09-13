// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1MobMemberSlavedUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/MobMemberSlavedUpdate.cpp

// MobMemberSlavedUpdate's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape from OpenContain: the UpdateModule base's vptrs
// at 0x00, 0x0C and 0x10, the inlined ~UpdateModule and ~BehaviorModule vptr
// restores, and the out-of-line base destructor at 0x00113D40. Two interface
// bases follow, at 0x20 and 0x28 -- the gap says the first of them carries a
// word of data.
//
// The body is eight `delete` statements over eight pointer members running from
// 0x2C to 0x48, each emitted as the null check plus a call through vtable slot 0
// with the flag argument, which is what `delete p` compiles to when p's class
// has a virtual destructor. There are no destructible members of this class
// itself.

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

class MobMemberSlave
{
public:
	virtual ~MobMemberSlave();
};

// Plain virtuals rather than virtual destructors: retail gives these subobjects
// a vptr write and no unwind state.
class MobMemberSlavedUpdateSecondaryBase1
{
public:
	virtual void slot();

private:
	unsigned char m_unreconstructed_24[4];
};

class MobMemberSlavedUpdateSecondaryBase2
{
public:
	virtual void slot();
};

class MobMemberSlavedUpdate
	: public UpdateModule,
	  public MobMemberSlavedUpdateSecondaryBase1,		///< vptr at 0x20
	  public MobMemberSlavedUpdateSecondaryBase2		///< vptr at 0x28
{
public:
	virtual ~MobMemberSlavedUpdate();

private:
	MobMemberSlave *m_slave0;							///< retail this+0x2C
	MobMemberSlave *m_slave1;							///< retail this+0x30
	MobMemberSlave *m_slave2;							///< retail this+0x34
	MobMemberSlave *m_slave3;							///< retail this+0x38
	MobMemberSlave *m_slave4;							///< retail this+0x3C
	MobMemberSlave *m_slave5;							///< retail this+0x40
	MobMemberSlave *m_slave6;							///< retail this+0x44
	MobMemberSlave *m_slave7;							///< retail this+0x48
};

// ??1MobMemberSlavedUpdate@@UAE@XZ
MobMemberSlavedUpdate::~MobMemberSlavedUpdate()
{
	delete m_slave0;
	delete m_slave1;
	delete m_slave2;
	delete m_slave3;
	delete m_slave4;
	delete m_slave5;
	delete m_slave6;
	delete m_slave7;
}
