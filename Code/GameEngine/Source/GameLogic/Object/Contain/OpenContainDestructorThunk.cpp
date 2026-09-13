// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1OpenContain@@: Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp

// OpenContain's destructor, lifted from its MASM dump to C++.
//
// Zero Hour's body is empty apart from two DEBUG_ASSERTCRASHes; BFME's actually
// destroys what is still inside, walking m_containList and handing every object
// to TheGameLogic->destroyObject after clearing the object's containedBy slot at
// its +0x214.
//
// The base chain is the module hierarchy the Update destructor thunks already
// model: the three vptr writes just before the out-of-line base call are at
// 0x10, 0x00 and 0x0C, which is ~UpdateModule followed by ~BehaviorModule with
// their dead stores folded away, and UpdateModule ends at 0x20 -- exactly where
// OpenContain's own six interface bases start (0x20, 0x24, 0x28, 0x2C, 0x30,
// 0x34). That is the nine-vptr group every Contain destructor in this directory
// restores.
//
// The six container members are read off the destructor's own call sites and
// destroyed in reverse declaration order under an SEH funclet apiece:
//
//   0x38  _STL::list<int>                  thunk 0x0000E68D -> 0x000CEBD0
//   0x40  _STL::map<int, 4-byte pod>       thunk 0x00015C30 -> 0x00225AA0
//   0x4C  _STL::map<int, 4-byte pod>       thunk 0x0001311A -> 0x00223550
//   0x58  _STL::map<int, 4-byte pod>       thunk 0x0004313F -> 0x002236C0
//   0x70  _STL::list<int>                  thunk 0x00013449 -> 0x000E5E70
//   0xC8  _STL::map<int, 4-byte pod>       thunk 0x0002D1E6 -> 0x002237F0
//
// Every payload is spelled the way Code/gen_small/tgrid_*.cpp spells that
// instantiation, so each emitted destructor mangles to the name the ledger
// already carries at its address.

#include <list>
#include <map>

// payload spellings from Code/gen_small/tgrid_*.cpp
struct Gen_t_00225aa0_p4pod { int a[1]; };
bool operator==(const Gen_t_00225aa0_p4pod&, const Gen_t_00225aa0_p4pod&);
bool operator<(const Gen_t_00225aa0_p4pod&, const Gen_t_00225aa0_p4pod&);
struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
struct Gen_t_002236c0_p4pod { int a[1]; };
bool operator==(const Gen_t_002236c0_p4pod&, const Gen_t_002236c0_p4pod&);
bool operator<(const Gen_t_002236c0_p4pod&, const Gen_t_002236c0_p4pod&);
struct Gen_t_002237f0_p4pod { int a[1]; };
bool operator==(const Gen_t_002237f0_p4pod&, const Gen_t_002237f0_p4pod&);
bool operator<(const Gen_t_002237f0_p4pod&, const Gen_t_002237f0_p4pod&);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed_00[0x214];
	void *m_containedBy;								///< retail this+0x214
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

// --- the module base chain, as modelled by the Update destructor thunks -------

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
	unsigned int m_updateState;							///< out to sizeof() == 0x20
};

// Declared with a plain virtual rather than a virtual destructor: these are the
// interface subobjects, and in retail they cost the destructor a vptr write but
// no unwind state.
template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual void slot();
};

class OpenContain
	: public UpdateModule,
	  public OpenContainSecondaryBase<2>,				///< vptr at 0x20
	  public OpenContainSecondaryBase<3>,				///< vptr at 0x24
	  public OpenContainSecondaryBase<4>,				///< vptr at 0x28
	  public OpenContainSecondaryBase<5>,				///< vptr at 0x2C
	  public OpenContainSecondaryBase<6>,				///< vptr at 0x30
	  public OpenContainSecondaryBase<7>				///< vptr at 0x34
{
public:
	virtual ~OpenContain();

private:
	_STL::list<Object *> m_containList;					///< retail this+0x38
	unsigned char m_unreconstructed_3c[4];
	_STL::map<int, Gen_t_00225aa0_p4pod> m_mapA;		///< retail this+0x40
	_STL::map<int, Gen_t_00223550_p4pod> m_mapB;		///< retail this+0x4C
	_STL::map<int, Gen_t_002236c0_p4pod> m_mapC;		///< retail this+0x58
	unsigned char m_unreconstructed_64[12];
	_STL::list<int> m_xferContainIDList;				///< retail this+0x70
	unsigned char m_unreconstructed_74[0x54];
	_STL::map<int, Gen_t_002237f0_p4pod> m_mapD;		///< retail this+0xC8
};

// ??1OpenContain@@UAE@XZ
OpenContain::~OpenContain()
{
	// BFME destroys whatever is still inside rather than just asserting.
	_STL::list<Object *>::iterator it = m_containList.begin();
	while (it != m_containList.end())
	{
		Object *obj = *it;
		++it;
		obj->m_containedBy = 0;
		TheGameLogic->destroyObject(obj);
	}
}
