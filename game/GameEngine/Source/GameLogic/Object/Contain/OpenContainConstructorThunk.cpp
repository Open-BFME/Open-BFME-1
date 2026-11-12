// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x002277A0 (722 B,
// ret 8 at +0x2CF).
//
// Zero Hour OpenContain::OpenContain (OpenContain.cpp) on BFME 1's layout. The
// class view is the matched destructor's (0x002262E0, OpenContainDestructors.cpp):
// the UpdateModule base (out-of-line ObjectModule constructor 0x00113C60, the
// inline Behavior/Update module constructors setting +0x14 = 0 and
// +0x18/+0x1C = -1), six interface subobjects at +0x20..+0x34, and its six
// containers (+0x38 list, +0x40/+0x4C/+0x58 maps, +0x70 list, +0xC8 map). The
// scalars between them are named by address: their stores follow Zero Hour's
// statement order (enter-exit map clear, player mask word, two sound frames,
// list size, stealth count, door countdown, rally point and flag, condition
// clear, exit path = 1, load sounds = true, passenger-fire flag from the module
// data's +0x154 byte) plus BFME's +0xB7/+0xB8/+0xB9 flags and +0xBC/+0xC0/+0xC4
// words, so they are mapped by order, not proven names. The 40-byte model
// condition set at +0x80 is a 320-bit bitset, zeroed at construction and again
// by clear().
//
// [BFME 2 donor] open-bfme-2 76f0baefa6
// Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainCtor.cpp (BFME 2
// 0x004649F8, 386 B, a different 0xFC layout) confirmed the six interface
// bases, the container lifetimes and the null-guarded module-data flag read.
// The flag ternary's false arm is the int 0: an int-typed conditional gives
// retail's movzx load. The rally point is zeroed through an inline helper
// standing for Coord3D::zero(); three direct stores schedule differently.
#include <list>
#include <map>
#include <bitset>

// payload spellings from game/gen_small/tgrid_*.cpp
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

#include "../object.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Thing;
class ModuleData;

// --- the module base chain, as modelled by the Update destructor thunks -------

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

protected:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113d40
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);

private:
	void *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData) : ObjectModule(thing, moduleData) {}
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData) :
		BehaviorModule(thing, moduleData),
		m_nextCallFrameAndPhase(0),
		m_indexInLogic(-1),
		m_updateState(-1)
	{
	}
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;							///< out to sizeof() == 0x20
};

// The six interface subobjects. Each interface's implicit constructor stores
// its own vtable before OpenContain's, so each is spelled with the name
// dir32_addresses.csv records at that retail vtable: +0x20 0x010ABD60
// (Rva00220630), +0x24 CollideModuleInterface, +0x28 0x010A257C
// (Rva001F1EE0), +0x2C DamageModuleInterface, +0x30 ExitInterface and +0x34
// CreateModuleInterface. They are reached through this unit's
// OpenContainSecondaryBase<N> spelling (the one the matched destructor and
// derived containers use for OpenContain's own vtables); the specialisations
// are novtable because the retail constructor stores no vtable of their own.
// Each declares a plain virtual rather than a virtual destructor: in retail
// they cost a vptr write but no unwind state.
class Rva00220630 { public: virtual void slot(); };
class CollideModuleInterface { public: virtual void slot(); };
class Rva001F1EE0 { public: virtual void slot(); };
class DamageModuleInterface { public: virtual void slot(); };
class ExitInterface { public: virtual void slot(); };
class CreateModuleInterface { public: virtual void slot(); };

template <int Number> class OpenContainSecondaryBase;
template <> class __declspec(novtable) OpenContainSecondaryBase<2> : public Rva00220630 {};
template <> class __declspec(novtable) OpenContainSecondaryBase<3> : public CollideModuleInterface {};
template <> class __declspec(novtable) OpenContainSecondaryBase<4> : public Rva001F1EE0 {};
template <> class __declspec(novtable) OpenContainSecondaryBase<5> : public DamageModuleInterface {};
template <> class __declspec(novtable) OpenContainSecondaryBase<6> : public ExitInterface {};
template <> class __declspec(novtable) OpenContainSecondaryBase<7> : public CreateModuleInterface {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h
// The module data byte the constructor copies into +0xB6.
class OpenContainModuleData
{
public:
	unsigned char m_pad[0x154];
	bool m_passengersAllowedToFire;			///< +0x154
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
// BFME's model-condition set: 320 bits, cleared at construction and again by
// the constructor body.
class ModelConditionFlags
{
public:
	ModelConditionFlags() {}
	void clear() { m_bits.reset(); }

private:
	_STL::bitset<320> m_bits;
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// Zero Hour's Coord3D::zero(); the canonical struct carries no methods.
inline void zeroCoord3D(Coord3D *c) { c->x = 0.0f; c->y = 0.0f; c->z = 0.0f; }

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
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();

private:
	const OpenContainModuleData *getOpenContainModuleData() const { return (const OpenContainModuleData *)m_moduleData; }

	_STL::list<Object *> m_containList;					///< retail this+0x38
	int m_bfme3C;
	_STL::map<int, Gen_t_00225aa0_p4pod> m_mapA;		///< retail this+0x40
	_STL::map<int, Gen_t_00223550_p4pod> m_mapB;		///< retail this+0x4C
	_STL::map<int, Gen_t_002236c0_p4pod> m_mapC;		///< retail this+0x58
	int m_bfme64;
	int m_bfme68;
	int m_bfme6C;
	_STL::list<int> m_xferContainIDList;				///< retail this+0x70
	unsigned short m_bfme74;
	int m_bfme78;
	int m_bfme7C;
	ModelConditionFlags m_conditionState;				///< retail this+0x80
	Coord3D m_bfmeA8;
	bool m_bfmeB4;
	bool m_bfmeB5;
	bool m_bfmeB6;
	bool m_bfmeB7;
	bool m_bfmeB8;
	bool m_bfmeB9;
	int m_bfmeBC;
	int m_bfmeC0;
	int m_bfmeC4;
	_STL::map<int, Gen_t_002237f0_p4pod> m_mapD;		///< retail this+0xC8
};

// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z
OpenContain::OpenContain(Thing *thing, const ModuleData *moduleData) : UpdateModule(thing, moduleData)
{
	// initialize our lists
	m_containList.clear();
	m_mapC.clear();
	m_bfme74 = 0;
	m_bfme78 = 0;
	m_bfme7C = 0;
	m_bfme3C = 0;
	m_bfme64 = 0;
	m_bfme6C = 0;
	m_bfmeB7 = false;
	m_bfmeB8 = false;
	m_bfmeB9 = true;

	zeroCoord3D(&m_bfmeA8);
	m_bfmeB4 = false;

	m_conditionState.clear();
	m_bfme68 = 1;
	m_bfmeB5 = true;
	m_bfmeBC = 0;
	m_bfmeC4 = 0;
	m_bfmeC0 = 0;

	m_bfmeB6 = getOpenContainModuleData() ? getOpenContainModuleData()->m_passengersAllowedToFire : 0;
}
