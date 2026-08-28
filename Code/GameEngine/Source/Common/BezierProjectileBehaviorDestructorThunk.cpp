// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BezierProjectileBehavior's destructor, lifted from its MASM dump to C++.
//
// The module-destructor shape from OpenContain: the UpdateModule base's vptrs
// at 0x00, 0x0C and 0x10, the inlined ~UpdateModule and ~BehaviorModule vptr
// restores, and the out-of-line base destructor at 0x00113D40. Two interface
// bases follow at 0x20 and 0x24.
//
// Two members, unwind states 0 and 1:
//
//   0x44  _STL::vector<12-byte pod>   inlined (imul 0x2AAAAAAB then *12)
//   0x7C  _STL::list<int>             thunk 0x00013449 -> 0x000E5E70
//
// The vector's elements are trivially destructible, so retail frees it inline
// and the 12-byte stride is the only thing the bytes pin.

#include <list>
#include <vector>

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

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p12pod { int a[3]; };

// Plain virtuals rather than virtual destructors: retail gives these subobjects
// a vptr write and no unwind state.
template <int Number>
class BezierProjectileBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class BezierProjectileBehavior
	: public UpdateModule,
	  public BezierProjectileBehaviorSecondaryBase<1>,		///< vptr at 0x20
	  public BezierProjectileBehaviorSecondaryBase<2>		///< vptr at 0x24
{
public:
	virtual ~BezierProjectileBehavior();

private:
	unsigned char m_unreconstructed_28[0x1c];
	_STL::vector<Gen_p12pod> m_vector;						///< retail this+0x44
	unsigned char m_unreconstructed_50[0x2c];
	_STL::list<int> m_list;									///< retail this+0x7C
};

// ??1BezierProjectileBehavior@@UAE@XZ
BezierProjectileBehavior::~BezierProjectileBehavior()
{
}
