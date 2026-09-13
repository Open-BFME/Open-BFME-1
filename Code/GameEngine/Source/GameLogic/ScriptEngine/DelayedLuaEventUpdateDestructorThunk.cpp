// cl: /DNDEBUG /MD /EHsc

// DelayedLuaEventUpdate's destructor, lifted from its MASM dump to C++.
//
// The smallest instance of the module-destructor shape
// OpenContainDestructorThunk.cpp works out in full: three vptr writes at 0x00,
// 0x0C and 0x10, one container member, then the inlined ~UpdateModule and
// ~BehaviorModule vptr restores (0x109CBAC at 0x10, 0x109CB5C at 0x00,
// 0x109CA98 at 0x0C) and the out-of-line base destructor at 0x00113D40.
//
// UpdateModule ends at 0x20 and the member sits at 0x24, so this class adds one
// word of its own ahead of it. The member is an _STL::list<int> reached through
// the 0x000E5E70 copy of _List_base<int>::~_List_base.


class Gen_uw_00013156
{
public:
	~Gen_uw_00013156();

private:
	void *m_p;
};

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

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	virtual ~DelayedLuaEventUpdate();

private:
	unsigned char m_unreconstructed_20[4];		///< retail this+0x20
	// The member at 0x24 is destroyed through the ILT thunk at RVA 0x13156,
	// which the ledger pins only under a synthetic name. Using that existing
	// pin rather than inventing a type -- the same convention the model file
	// already uses for Gen_dtor_00113d40.
	Gen_uw_00013156 m_member;					///< retail this+0x24
};

// ??1DelayedLuaEventUpdate@@UAE@XZ
DelayedLuaEventUpdate::~DelayedLuaEventUpdate()
{
}
