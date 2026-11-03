// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x00271DB0, 2099 bytes (ret 4): AIUpdateInterface::DoXfer(Xfer &),
// the snapshot slot (+0x0C) of AIUpdateInterface's own vtable 0x010BA8A8; the
// derived AI updates' xfer bodies delegate to it (Dozer 0x002B7080). Identity:
// tools/ilt_oracle.py CONFIRMS ?DoXfer@AIUpdateInterface@@MAEXAAVXfer@@@Z through
// ILT 0x00043441; evidence targets/game/reverse/identity_evidence/00271db0-aiupdateinterface-xfer.md.
//
// Port of the BFME 2 donor Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateXfer.cpp
// (open-bfme-2 45afcff3), its quoted headers inlined (BFME 2 Snapshot, Xfer,
// UpdateModule, BehaviorModule, ObjectModule and Module views) with BFME 1's
// ascii_string.h instead of the donor's string shim. BFME 1 deltas, all read from
// the retail body: version 6; one Xfer operator== slot fewer (unsigned int +0x74,
// bool +0x8C); makeStateMachine at vtable +0x218; the tertiary state machine only
// from version 5; the trigger area looked up by value through TerrainLogic +0x90
// and waypoints through +0x80; the attack-info name from a by-value getter; two
// turret AIs; the member layout (0x92 bytes smaller: smaller BitFlags) re-derived
// offset by offset; and the BFME 1 tail (float +0x168, uint +0x178, the
// AICommandParmsStorage-style member at +0x27C, version 2/3/4/6 gated transfers).
// Members named m_bXXX/m_fXXX/m_iXXX are known only by offset and type.
// Callees without a proven name are called through their ILT rows (?j_XXXXXXXX).
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
// ---- inlined inputs/reference/open-bfme-2/reference/shims/moduledata/Common/Snapshot.h
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Snapshot.h ///////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Snapshot base. Retail vtable 0x00BBB554 has a
//         deleting destructor followed by three pure virtual slots, in
//         retail order: loadPostProcess, GetSnapshotName, xfer.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __SNAPSHOT_H_
#define __SNAPSHOT_H_

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Xfer;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// LivingWorldBattle (003F6A3A, 003F6F0D) and LivingWorldBuildPlot
// (004FC807) complete this base before calling their list-base constructor,
// without storing Snapshot's vptr. Their first unwind state still calls the
// shared destructor at 0049B47C, which restores table 00BBB554. Constructor
// units can select that novtable surface and bind the existing destructor;
// destructor units retain the inline body that emits the native vptr store.
#ifdef BFME_SNAPSHOT_CONSTRUCTOR_ONLY
class __declspec(novtable) Snapshot
#else
class Snapshot
#endif
{

friend class GameState;
// Xfer::operator==(Snapshot &) (0x0060B8C6) calls slot 3 itself.
friend class Xfer;
friend class XferLoad;
friend class XferSave;
friend class XferCRC;
// Xfer::operator&(Snapshot &) (export, 0x0060B8C6) is a member of the
// Xfer base itself and calls the protected slot-3 transfer directly.
friend class Xfer;

public:
	
#ifdef BFME_SNAPSHOT_CONSTRUCTOR_ONLY
	__declspec(dllimport) __forceinline Snapshot() {}
	virtual ~Snapshot( void );
#else
	Snapshot() {}
	virtual ~Snapshot( void ) {}
#endif
	Snapshot( const Snapshot &that ) {}

protected:

	// Retail order. Vtable 0x00BBB554 is the deleting destructor, then three
	// __purecall slots, and the overriders fix what each slot is:
	//  - the exports name every FXParticleSystem info's overriders
	//    LoadPostProcess, GetSnapshotName and DoXfer(Xfer &), and their
	//    vtables (e.g. 0x00BBB5C8) hold them in slots 1, 2 and 3;
	//  - Xfer::operator&(Snapshot &) (export, 0x0060B8C6) calls slot 3
	//    ([eax+0Ch]) with the Xfer;
	//  - Module and ModuleData vtables (0x00C59368, 0x00C52534, 0x00C594E0)
	//    hold loadPostProcess in slot 1, a getter returning the class-name
	//    literal in slot 2 and xfer in slot 3.
	// Retail has no crc. The Zero Hour classes still compiled against this
	// header override crc(Xfer *), so it stands in for GetSnapshotName in
	// slot 2 and keeps every derived table at four base slots; slots 1 and 3
	// keep the Zero Hour spellings the ledger's rows use.

	/** post process phase for loading save games.  All save systems have their xfer
	run using XferLoad mode, and then all systems each have their post process run */
// BFME2's named tracker table has the capitalized API. This selects the
	// spelling of the same three slots; the default ZH surface stays available.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess( void ) = 0;
#else
	virtual void loadPostProcess( void ) = 0;
#endif

	// Named BFME2 snapshot getters use the proven retail slot-2 signature.
	// Other imported units retain the Zero Hour crc spelling described above.
	// Both declarations occupy the same single slot, never an added fifth one.
#ifdef BFME_SNAPSHOT_NAME_SLOT
// FX info exports and retail vtable C1BBA0 use the non-const getter at
// 001F354A. Other consumers retain their established const signature.
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName( void ) = 0;
#else
	virtual const char *GetSnapshotName( void ) const = 0;
#endif
#else
	virtual void crc( Xfer *xfer ) = 0;
#endif

	/** run save, load, or deep CRC check on this data structure, the type depends on the
	setup of the Xfer pointer */
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
// FX info DoXfer exports take Xfer& (e.g. 0047A69C); it occupies the same
// slot and has the same one-pointer ABI as the existing pointer surface.
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer( Xfer &xfer ) = 0;
#else
	virtual void DoXfer( Xfer *xfer ) = 0;
#endif
#else
	virtual void xfer( Xfer *xfer ) = 0;
#endif

};

#endif // __SNAPSHOT_H_
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/Common/BfmeXfer.h
// Xfer: the shared BFME2 Xfer interface view, adopted by tools/header_adopt_lane.py.
// The declaration is the private view 354 ledger units carried verbatim
// (class_views layout fb2837e782): retail-dispatched virtual slots in vtable
// order, the out-of-line Version1 (0x000053EE), SkipBadBlock (0x0050B238),
// XferRawBytes (0x0060B886) and XferEnum (0x0060BBD5) spellings the ledger rows use.
// reverse/class_contracts/Xfer.json leaves slots 4-38 undecided (their names
// differ across views); this header keeps the majority spelling. Slot names
// are not identity claims beyond the rows above and the notes below.
//
// Slots 5-7 are _purecall in Xfer's own table (RVA 0x007BB910). XferLoad's table
// (RVA 0x0087AF18) fills them with 0x0060C629 int(const char *), 0x0060C469
// void() and 0x0060C6F6 void(const char *) (ledger rows in xfer_load.cpp);
// WorldBuilder names the overriders XferLoad::BeginBlock, ::EndBlock and
// ::SkipBlock (XferSave and XferSaveAsText: EndBlock, SkipBlock), so the
// base slots carry those names and signatures.
// Slot 11 is _purecall too and sits inside the operator== run (MSVC keeps
// overloads together), so it is one more operator== overload. Its operand
// is the container type name callers pass as a string literal ("std::list",
// "std::vector", ...): the 59 private views that call it agree on
// `const char *const &`, and XferSave's slot-11 body (0x0060CE41) reads the
// interned string pointer through the reference.
//
// The operand types (Snapshot, AsciiString, the Coord/Region value types,
// RealRange, the RGBA colors, PooledString) are deliberately
// not forward-declared here: units declare them with their own class-keys
// before including this header; a forward declaration here could disagree
// with the class-key a unit already uses.
#ifndef BFME_XFER_H
#define BFME_XFER_H

class Xfer
{
public:
	class Version;

	// XferSaveAsText inlines base construction without emitting another
	// external constructor; System/Xfer.cpp owns the out-of-line body.
#ifdef BFME_XFER_INLINE_CTOR
	__declspec(dllimport) __forceinline Xfer() {}
#else
	Xfer();
#endif
	// Retail's scalar deleting destructor (Xfer.cpp) calls ~Xfer instead of
	// inlining its vtable restore; only the defining TU sees the body.
	// XferVectorDeletingDtor.cpp defines BFME_XFER_INLINE_DTOR: retail's
	// vector deleting destructor inlines the vptr store.
#ifdef BFME_XFER_INLINE_DTOR
	virtual ~Xfer();
#else
	__declspec(noinline) virtual ~Xfer();
#endif

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual int BeginBlock(const char *name) = 0;
	virtual void EndBlock() = 0;
	virtual void SkipBlock(const char *name) = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(const char *const &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

#endif // BFME_XFER_H

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};


// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
// Target facts (all code addresses are RVAs; vftables are VAs):
// 0x00253390 calls BehaviorModule at 0x00253330, installs 0x00BF004C at +0,
// 0x00BEFF90 at +0x0C and 0x00BFBCE4 at +0x10, and writes 0, -1, -1 at
// +0x14, +0x18, +0x1C. AIGateUpdate's 0x004B08E8 starts its fields at +0x20,
// bounding UpdateModule at sizeof 0x20; its added interface occupies 4 bytes.
// BehaviorModule's 0x00BEEA7C has 12 primary slots; 0x00BF004C has 13,
// ending before the UpdateModule string at 0x00BF0080. Slots 1, 2, 3 are
// loadPostProcess (0x0058B03E), GetSnapshotName (0x002533CD), xfer (0x0044DF9F);
// slot 12 is getUpdatePhase (0x0022C4CB, returns 2). There is no crc slot.
// 0x00BEFF90 has BehaviorModuleInterface's 47 slots with slot 9 = 0x002533D3,
// which converts the +0x0C interface pointer to the +0x10 update interface.
// The interface's 0x00BE2B78 holds three pure slots; 0x00BFBCE4 holds pure
// update, getDisabledTypesToProcess (0x00253376), rva0044DF8D (0x0044DF8D).
// The getter's row names BitFlags<11>; its bytes copy four bytes from
// 0x00E030CC. BitFlags<11>::xfer (0x00292414) loops to 11, not 13.
// The wake body subtracts 0x10, loads Object at +8 and calls
// setWakeFrame (0x0044DF71). Neither interface has a virtual destructor.
// 0x0024A797 stores 0x00BFBCE4 at +0x10, then BehaviorModule's 0x00BEEA7C
// and 0x00BEE9C0 at +0/+0x0C, and jumps to 0x0049B47C (Snapshot reset).
// The latter stores are inlined base destruction, not UpdateModule tables.
// 0x0023C3C6 clamps and stores the raw frame at +0x14; 0x0023C3DA returns
// +0x18 and writes +0x1C through its argument. 0x0044DF5B reads raw +0x14.
// frameToSleepTime is rowed at 0x0044DF28. These methods and the destructor
// at 0x0024A797 have out-of-line owners.
// Donor facts: Zero Hour UpdateModule.h names update, getUpdate, getUpdatePhase,
// m_nextCallFrameAndPhase, m_indexInLogic, the wake/sleep helpers and the
// SleepyUpdatePhase and UpdateSleepTime enum types. BFME2's getter row selects
// BitFlags value 11; its parameter type is spelled as BodyModule.h spells it.


#ifndef __BFME2_UPDATEMODULE_H_
#define __BFME2_UPDATEMODULE_H_

// A unit that already read Snapshot without the name slot spells that slot crc.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
// FILE: BehaviorModule.h ////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 BehaviorModuleInterface and BehaviorModule.
//
// Target facts:
//  - ??0BehaviorModule (0x00253330) calls ??0ObjectModule, then stores the
//    interface's own table 0x00BEE900 and its BehaviorModule table 0x00BEE9C0 at
//    +0x0C and the primary table 0x00BEEA7C at +0: sizeof 0x10.
//  - 0x00BEE900 holds exactly 47 __purecall slots (0x00BEEA7C follows 0x00BEE9C0
//    after 47 entries; the interface has no virtual destructor). In 0x00BEE9C0
//    slots 0-42 are 0x000D43D0 `xor eax,eax; ret` (getters returning NULL),
//    43, 45 and 46 are 0x0047A69C `ret 4` and 44 is 0x000B3FD0 `ret`.
//  - Each module family overrides one getter (the classes' constructors store their
//    own +0x0C tables): body modules slot 0, collides 1, contains 2, creates 3,
//    damages 4, dies 7 (DieModule's 0x002533D3 returns its +0x10
//    DieModuleInterface), special powers 8, updates 9, upgrades 10, AI updates 19.
//  - The primary table 0x00BEEA7C is ObjectModule's ten slots plus two of
//    BehaviorModule's own, both 0x000D43D0 (returning 0).
//  - ~DieModule (0x0045CE54) restores 0x00BEEA7C and 0x00BEE9C0 inline: the
//    BehaviorModule destructor is inline and empty.
// Donor (Zero Hour BehaviorModule.h) facts: the getter names. Zero Hour's order
// has getDestroy at 5 and getDie at 6; BFME2's dies override slot 7, so one slot
// was added before getDie. Only the slots a family's override pins carry a name;
// the rest are placeholders (slotNN, vslot10/11) until evidence names them.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __BFME2_BEHAVIORMODULE_H_
#define __BFME2_BEHAVIORMODULE_H_

// BFME2's Snapshot has the GetSnapshotName slot where Zero Hour spells crc.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/Common/ObjectModule.h
// FILE: ObjectModule.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ObjectModule, the base of every object module.
//
// Target facts (docs/linking_obstacles.md, "Module base chain"):
//  - ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z (0x00306AA7) installs
//    vftable 0x00C07E1C, stores the ModuleData argument at +4 (Module's
//    m_moduleData) and the thing's object at +8;
//  - that vftable holds exactly 10 slots (its class-name literal follows):
//    Module's nine, then slot 9 = 0x0050B238 `ret 8`, an empty virtual with
//    two stack arguments. Zero Hour's ObjectModule declares
//    onCapture(Player *, Player *) there; its onDisabledEdge has no slot in
//    BFME2.
// The view majority (127 of 163 census views) spells the destructor out of
// line, which this header keeps.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __BFME2_OBJECTMODULE_H_
#define __BFME2_OBJECTMODULE_H_

// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/Common/Module.h
// FILE: Module.h /////////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Module, the common base of object and drawable modules.
//
// Written from the retail vftables (docs/linking_obstacles.md, "Module base
// chain"); tools/header_adopt_lane.py cannot generate it while the private
// views disagree on its size. Target facts:
//  - no Module vftable survives (its constructor inlines and the store dies);
//    ObjectModule's 0x00C07E1C has exactly 10 slots, DrawableModule's
//    0x00C07E54 11, and slot 9 differs between them, so Module has 9;
//  - ??_GObjectModule (0x004A10FD) calls 0x0049B47C, which restores
//    Snapshot's vftable 0x00BBB554 at [this]: Snapshot is the base at offset 0
//    and every destructor between them is empty;
//  - slots 1-3 are Snapshot's (Snapshot.h); slot 4 is __purecall in every
//    abstract table and Object::findModule (0x0028B6D6) compares [vtable+0x10];
//  - slots 5-8 are the empty `ret` 0x000B3FD0 in the base tables; matched
//    overriders name slot 5 onObjectCreated, 6 onDrawableBoundToObject and
//    8 onDelete. Slot 7 sits where Zero Hour has preloadAssets(TimeOfDay),
//    but every BFME2 implementation takes no stack argument;
//  - the ObjectModule and DrawableModule constructors store the ModuleData
//    argument at +4.
// Donor (Zero Hour Module.h) facts: the method names and the empty inline
// bodies. Zero Hour's MemoryPoolObject base and its TimeOfDay argument are not
// BFME2's.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __BFME2_MODULE_H_
#define __BFME2_MODULE_H_


enum NameKeyType;
class ModuleData;

//-------------------------------------------------------------------------------------------------
class Module : public Snapshot
{
public:

	Module( const ModuleData *moduleData ) : m_moduleData( moduleData ) { }
	virtual ~Module() { }

	virtual NameKeyType getModuleNameKey() const = 0;					// slot 4

	/** called after all the Modules for a given Thing are created */
	virtual void onObjectCreated() { }									// slot 5

	/** called whenever a drawable is bound to the object */
	virtual void onDrawableBoundToObject() { }							// slot 6

	/// Zero Hour's preloadAssets position; BFME2's slot takes no argument
	virtual void preloadAssets() { }										// slot 7

	/** called on every module of an object or drawable before any is deleted */
	virtual void onDelete( void ) { }										// slot 8

protected:

	inline const ModuleData *getModuleData() const { return m_moduleData; }

	const ModuleData *m_moduleData;										// +0x04

};

#endif // __BFME2_MODULE_H_

class Object;
class Player;
class Thing;

//-------------------------------------------------------------------------------------------------
class ObjectModule : public Module
{
public:

	ObjectModule( Thing *thing, const ModuleData *moduleData );
	virtual ~ObjectModule();

	virtual void onCapture( Player *oldOwner, Player *newOwner ) { }		// slot 9

protected:

	inline Object *getObject() { return m_object; }
	inline const Object *getObject() const { return m_object; }

	Object *m_object;														// +0x08

};

#endif // __BFME2_OBJECTMODULE_H_

class AIUpdateInterface;
class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;
class UpgradeModuleInterface;

//-------------------------------------------------------------------------------------------------
class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;			// 0
	virtual CollideModuleInterface *getCollide() = 0;			// 1
	virtual ContainModuleInterface *getContain() = 0;			// 2
	virtual CreateModuleInterface *getCreate() = 0;			// 3
	virtual DamageModuleInterface *getDamage() = 0;			// 4
	virtual void *slot05() = 0;			// 5
	virtual void *slot06() = 0;			// 6
	virtual DieModuleInterface *getDie() = 0;			// 7
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;			// 8
	virtual UpdateModuleInterface *getUpdate() = 0;			// 9
	virtual UpgradeModuleInterface *getUpgrade() = 0;			// 10
	virtual void *slot11() = 0;			// 11
	virtual void *slot12() = 0;			// 12
	virtual void *slot13() = 0;			// 13
	virtual void *slot14() = 0;			// 14
	virtual void *slot15() = 0;			// 15
	virtual void *slot16() = 0;			// 16
	virtual void *slot17() = 0;			// 17
	virtual void *slot18() = 0;			// 18
	virtual AIUpdateInterface *getAIUpdateInterface() = 0;			// 19
	virtual void *slot20() = 0;			// 20
	virtual void *slot21() = 0;			// 21
	virtual void *slot22() = 0;			// 22
	virtual void *slot23() = 0;			// 23
	virtual void *slot24() = 0;			// 24
	virtual void *slot25() = 0;			// 25
	virtual void *slot26() = 0;			// 26
	virtual void *slot27() = 0;			// 27
	virtual void *slot28() = 0;			// 28
	virtual void *slot29() = 0;			// 29
	virtual void *slot30() = 0;			// 30
	virtual void *slot31() = 0;			// 31
	virtual void *slot32() = 0;			// 32
	virtual void *slot33() = 0;			// 33
	virtual void *slot34() = 0;			// 34
	virtual void *slot35() = 0;			// 35
	virtual void *slot36() = 0;			// 36
	virtual void *slot37() = 0;			// 37
	virtual void *slot38() = 0;			// 38
	virtual void *slot39() = 0;			// 39
	virtual void *slot40() = 0;			// 40
	virtual void *slot41() = 0;			// 41
	virtual void *slot42() = 0;			// 42
	virtual void slot43(int) = 0;			// 43
	virtual void slot44() = 0;			// 44
	virtual void slot45(int) = 0;			// 45
	virtual void slot46(int) = 0;			// 46
};

//-------------------------------------------------------------------------------------------------
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );
	virtual ~BehaviorModule() { }

	virtual void *vslot10() { return 0; }			// primary slot 10
	virtual void *vslot11() { return 0; }			// primary slot 11

	virtual BodyModuleInterface *getBody() { return 0; }
	virtual CollideModuleInterface *getCollide() { return 0; }
	virtual ContainModuleInterface *getContain() { return 0; }
	virtual CreateModuleInterface *getCreate() { return 0; }
	virtual DamageModuleInterface *getDamage() { return 0; }
	virtual void *slot05() { return 0; }
	virtual void *slot06() { return 0; }
	virtual DieModuleInterface *getDie() { return 0; }
	virtual SpecialPowerModuleInterface *getSpecialPower() { return 0; }
	virtual UpdateModuleInterface *getUpdate() { return 0; }
	virtual UpgradeModuleInterface *getUpgrade() { return 0; }
	virtual void *slot11() { return 0; }
	virtual void *slot12() { return 0; }
	virtual void *slot13() { return 0; }
	virtual void *slot14() { return 0; }
	virtual void *slot15() { return 0; }
	virtual void *slot16() { return 0; }
	virtual void *slot17() { return 0; }
	virtual void *slot18() { return 0; }
	virtual AIUpdateInterface *getAIUpdateInterface() { return 0; }
	virtual void *slot20() { return 0; }
	virtual void *slot21() { return 0; }
	virtual void *slot22() { return 0; }
	virtual void *slot23() { return 0; }
	virtual void *slot24() { return 0; }
	virtual void *slot25() { return 0; }
	virtual void *slot26() { return 0; }
	virtual void *slot27() { return 0; }
	virtual void *slot28() { return 0; }
	virtual void *slot29() { return 0; }
	virtual void *slot30() { return 0; }
	virtual void *slot31() { return 0; }
	virtual void *slot32() { return 0; }
	virtual void *slot33() { return 0; }
	virtual void *slot34() { return 0; }
	virtual void *slot35() { return 0; }
	virtual void *slot36() { return 0; }
	virtual void *slot37() { return 0; }
	virtual void *slot38() { return 0; }
	virtual void *slot39() { return 0; }
	virtual void *slot40() { return 0; }
	virtual void *slot41() { return 0; }
	virtual void *slot42() { return 0; }
	virtual void slot43(int) { }
	virtual void slot44() { }
	virtual void slot45(int) { }
	virtual void slot46(int) { }
};

#endif // __BFME2_BEHAVIORMODULE_H_

template <int N> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

enum UpdateSleepTime;
enum SleepyUpdatePhase;

class UpdateModuleInterface
{
public:
    virtual UpdateSleepTime update() = 0;
    virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();

    virtual UpdateModuleInterface *getUpdate() { return this; }
    virtual UpdateSleepTime update() = 0;
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay);
    virtual void DoXfer(Xfer &xfer);

    void friend_setNextCallFrame(unsigned int frame);
    int rva0023C3DA(int *phase);

    unsigned int m_nextCallFrameAndPhase; // +0x14
    int m_indexInLogic; // +0x18
    int m_field1C; // +0x1C

protected:
    virtual void LoadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual SleepyUpdatePhase getUpdatePhase() const;

    void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
    UpdateSleepTime getWakeFrame() const;
    UpdateSleepTime frameToSleepTime(unsigned int frame1,
        unsigned int frame2, unsigned int frame3, unsigned int frame4);
};

typedef UpdateModule *UpdateModulePtr;

#endif
class AIUpdateSnapshotMember : public Snapshot {
public:
 virtual void LoadPostProcess(); virtual void crc(Xfer *); virtual void DoXfer(Xfer &);
};
class StateMachine : public Snapshot {
public:
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void initDefaultState();
};
class Path {
public:
 Path(); void xfer00401C70(Xfer *);
 char m_data[0x24];	// retail news 0x24 bytes
};
class Locomotor;
class Rva001E7E25 { public: void rva001E7E25(); };
class LocomotorSet {
public:
 void clear(); void xferSelfAndCurLocoPtr(Xfer *, Locomotor **);
 char m_data[0x24];
};
template<int N> class BitFlags {
public:
 void xfer(Xfer *);
 unsigned int m_bits[(N+31)/32];
};
class Rva0026AFDAMember { public: void doXfer(Xfer *); char m_data[0xA0]; };
struct Rva00336283Element;
class LuaScriptEngine;
class Rva001D0610Lua { public: void *rva002EBF60(const AsciiString &); };
extern LuaScriptEngine *TheLuaScriptEngine;
void XferCommandSourceType(Xfer *, int *);
Xfer *Rva00263569Xfer(Xfer *, int *);
void XferLocomotorSetType(Xfer *, int *);
void XferWhichTurretType(Xfer *, int *);
void XferAttitudeType(Xfer *, int *);
class PolygonTrigger { public: char m_pad[0x8]; AsciiString m_name; };
class AttackPriorityInfo { public: AsciiString getName() const; };
class Waypoint { public: char m_pad[4]; unsigned int m_id; };
class TerrainLogic { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual Waypoint *getWaypointByID(unsigned int);
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual PolygonTrigger *getTriggerAreaByName(AsciiString);
};
extern TerrainLogic *TheTerrainLogic;
class AIUpdateInterface : public UpdateModule {
protected:
 virtual void DoXfer(Xfer &);
public:
 virtual void gap13();
 virtual void gap14();
 virtual void gap15();
 virtual void gap16();
 virtual void gap17();
 virtual void gap18();
 virtual void gap19();
 virtual void gap20();
 virtual void gap21();
 virtual void gap22();
 virtual void gap23();
 virtual void gap24();
 virtual void gap25();
 virtual void gap26();
 virtual void gap27();
 virtual void gap28();
 virtual void gap29();
 virtual void gap30();
 virtual void gap31();
 virtual void gap32();
 virtual void gap33();
 virtual void gap34();
 virtual void gap35();
 virtual void gap36();
 virtual void gap37();
 virtual void gap38();
 virtual void gap39();
 virtual void gap40();
 virtual void gap41();
 virtual void gap42();
 virtual void gap43();
 virtual void gap44();
 virtual void gap45();
 virtual void gap46();
 virtual void gap47();
 virtual void gap48();
 virtual void gap49();
 virtual void gap50();
 virtual void gap51();
 virtual void gap52();
 virtual void gap53();
 virtual void gap54();
 virtual void gap55();
 virtual void gap56();
 virtual void gap57();
 virtual void gap58();
 virtual void gap59();
 virtual void gap60();
 virtual void gap61();
 virtual void gap62();
 virtual void gap63();
 virtual void gap64();
 virtual void gap65();
 virtual void gap66();
 virtual void gap67();
 virtual void gap68();
 virtual void gap69();
 virtual void gap70();
 virtual void gap71();
 virtual void gap72();
 virtual void gap73();
 virtual void gap74();
 virtual void gap75();
 virtual void gap76();
 virtual void gap77();
 virtual void gap78();
 virtual void gap79();
 virtual void gap80();
 virtual void gap81();
 virtual void gap82();
 virtual void gap83();
 virtual void gap84();
 virtual void gap85();
 virtual void gap86();
 virtual void gap87();
 virtual void gap88();
 virtual void gap89();
 virtual void gap90();
 virtual void gap91();
 virtual void gap92();
 virtual void gap93();
 virtual void gap94();
 virtual void gap95();
 virtual void gap96();
 virtual void gap97();
 virtual void gap98();
 virtual void gap99();
 virtual void gap100();
 virtual void gap101();
 virtual void gap102();
 virtual void gap103();
 virtual void gap104();
 virtual void gap105();
 virtual void gap106();
 virtual void gap107();
 virtual void gap108();
 virtual void gap109();
 virtual void gap110();
 virtual void gap111();
 virtual void gap112();
 virtual void gap113();
 virtual void gap114();
 virtual void gap115();
 virtual void gap116();
 virtual void gap117();
 virtual void gap118();
 virtual void gap119();
 virtual void gap120();
 virtual void gap121();
 virtual void gap122();
 virtual void gap123();
 virtual void gap124();
 virtual void gap125();
 virtual void gap126();
 virtual void gap127();
 virtual void gap128();
 virtual void gap129();
 virtual void gap130();
 virtual void gap131();
 virtual void gap132();
 virtual void gap133();
 virtual StateMachine *makeStateMachine();
 char m_unknown20[0x8];
 unsigned int m_priorWaypointID; // +0x28
 unsigned int m_currentWaypointID; // +0x2C
 StateMachine * m_stateMachine; // +0x30
 StateMachine * m_secondaryStateMachine; // +0x34
 StateMachine * m_tertiaryStateMachine; // +0x38
 unsigned int m_nextEnemyScanTime; // +0x3C
 ObjectID m_currentVictimID; // +0x40
 float m_desiredSpeed; // +0x44
 int m_lastCommandSource; // +0x48
 int m_guardMode; // +0x4C
 int m_guardTargetType[2]; // +0x50
 Coord3DBase m_locationToGuard; // +0x58
 ObjectID m_objectToGuard; // +0x64
 unsigned int m_extra68; // +0x68
 PolygonTrigger * m_areaToGuard; // +0x6C
 AttackPriorityInfo * m_attackInfo; // +0x70
 Coord3DBase m_waypointQueue[16]; // +0x74
 int m_waypointCount; // +0x134
 int m_waypointIndex; // +0x138
 Waypoint * m_completedWaypoint; // +0x13C
 Path * m_path; // +0x140
 ObjectID m_requestedVictimID; // +0x144
 Coord3DBase m_requestedDestination; // +0x148
 Coord3DBase m_requestedDestination2; // +0x154
 char m_pad160[0x4];
 ObjectID m_ignoreObstacleID; // +0x164
 float m_f168; // +0x168
 char m_pad16C[0x8];
 float m_extra174; // +0x174
 unsigned int m_u178; // +0x178
 unsigned int m_queueForPathFrame; // +0x17C
 Coord3DBase m_finalPosition; // +0x180
 ObjectID m_repulsor1; // +0x18C
 ObjectID m_repulsor2; // +0x190
 char m_pad194[0x4];
 ObjectID m_moveOutOfWay1; // +0x198
 ObjectID m_moveOutOfWay2; // +0x19C
 float m_f1A0; // +0x1A0
 char m_pad1A4[0x4];
 LocomotorSet m_locomotorSet; // +0x1A8
 Locomotor * m_curLocomotor; // +0x1CC
 int m_curLocomotorSet; // +0x1D0
 float m_f1D4; // +0x1D4
 int m_locomotorGoalType; // +0x1D8
 Coord3DBase m_locomotorGoalData; // +0x1DC
 Snapshot * m_turretAI[2]; // +0x1E8
 int m_turretSyncFlag; // +0x1F0
 AsciiString m_attackInfoName; // +0x1F4
 int m_attitude; // +0x1F8
 unsigned int m_nextMoodCheckTime; // +0x1FC
 Rva00336283Element * m_extra220; // +0x200
 AIUpdateSnapshotMember m_extra224; // +0x204
 char m_pad208[0xC];
 unsigned int m_extra234; // +0x214
 ObjectID m_extra238; // +0x218
 char m_pad21C[0x4];
 BitFlags<320> m_flags220; // +0x220
 BitFlags<320> m_flags248; // +0x248
 BitFlags<96> m_flags270; // +0x270
 Rva0026AFDAMember m_lastOutsideCommand; // +0x27C
 bool m_b31C; // +0x31C
 bool m_doFinalPosition; // +0x31D
 bool m_waitingForPath; // +0x31E
 bool m_isAttackPath; // +0x31F
 bool m_isFinalGoal; // +0x320
 bool m_isApproachPath; // +0x321
 bool m_isSafePath; // +0x322
 bool m_movementComplete; // +0x323
 bool m_b324; // +0x324
 bool m_b325; // +0x325
 bool m_b326; // +0x326
 bool m_upgradedLocomotors; // +0x327
 bool m_canPathThroughUnits; // +0x328
 bool m_b329; // +0x329
 bool m_randomlyOffsetMoodCheck; // +0x32A
 bool m_isAiDead; // +0x32B
 bool m_isRecruitable; // +0x32C
 bool m_executingWaypointQueue; // +0x32D
 bool m_b32E; // +0x32E
 bool m_b32F; // +0x32F
 bool m_b330; // +0x330
 char m_pad331[0x1];
 bool m_b332; // +0x332
 bool m_b333; // +0x333
 bool m_b334; // +0x334
 bool m_b335; // +0x335
 bool m_b336; // +0x336
 bool m_b337; // +0x337
 bool m_b338; // +0x338
 bool m_b339; // +0x339
 bool m_b33A; // +0x33A
 bool m_b33B; // +0x33B
 int m_i33C; // +0x33C
};


// Retail reaches these callees only through their incremental-link thunks;
// the thunk rows (?j_XXXXXXXX) are the names the ledger resolves.
extern void j_000044c1(); extern void j_0000c9b4(); extern void j_00004b79(); extern void j_0003c529();
extern void j_000111da(); extern void j_0003786c(); extern void j_000068fc(); extern void j_00016c1b();
extern void j_00026dd7(); extern void j_00002dec(); extern void j_00035a0d();
class ThunkReceiver {};
static __forceinline void thunkThis1(void (*p)(), void *self, Xfer *x)
{ union { void (*p)(); void (ThunkReceiver::*f)(Xfer *); } u; u.p = p; (((ThunkReceiver *)self)->*u.f)(x); }
static __forceinline void thunkThis2(void (*p)(), void *self, Xfer *x, void *v)
{ union { void (*p)(); void (ThunkReceiver::*f)(Xfer *, void *); } u; u.p = p; (((ThunkReceiver *)self)->*u.f)(x, v); }
static __forceinline void thunkFree2(void (*p)(), Xfer *x, void *v) { ((void (*)(Xfer *, void *))p)(x, v); }


// StringBase<char>'s header (reference count, then the 16-bit length), read the
// way the retail body tests a string for text: no out-of-line isEmpty call.
struct AsciiStringHeaderView { int m_refCount; unsigned short m_length; };
static __forceinline bool asciiHasText(const AsciiString &s)
{
	const AsciiStringHeaderView *h = *(const AsciiStringHeaderView *const *)&s;
	return h != 0 && h->m_length != 0;
}

void AIUpdateInterface::DoXfer(Xfer &xferRef)
{
 Xfer *xfer = &xferRef;
 Xfer::Version version(1, 6);
 *xfer == version;
 thunkThis1(j_000044c1, this, xfer);
 *xfer == m_priorWaypointID;
 *xfer == m_currentWaypointID;
 *xfer == *reinterpret_cast<Snapshot *>(m_stateMachine);
 bool gotsecondary;
 if (xfer->IsStoring()) gotsecondary = m_secondaryStateMachine != 0;
 *xfer == gotsecondary;
 if (gotsecondary) {
  if (xfer->IsLoading()) { m_secondaryStateMachine = makeStateMachine(); m_secondaryStateMachine->initDefaultState(); }
  *xfer == *reinterpret_cast<Snapshot *>(m_secondaryStateMachine);
 }
 if (version.m_minimum >= 5) {
 bool gottertiary;
 if (xfer->IsStoring()) gottertiary = m_tertiaryStateMachine != 0;
 *xfer == gottertiary;
 if (gottertiary) {
  if (xfer->IsLoading()) { m_tertiaryStateMachine = makeStateMachine(); m_tertiaryStateMachine->initDefaultState(); }
  *xfer == *reinterpret_cast<Snapshot *>(m_tertiaryStateMachine);
 }
 }
 *xfer == m_isAiDead;
 *xfer == m_isRecruitable;
 *xfer == m_nextEnemyScanTime;
 thunkFree2(j_0000c9b4, xfer, &m_currentVictimID);
 *xfer == m_desiredSpeed;
 thunkFree2(j_00004b79, xfer, &m_lastCommandSource);
 thunkFree2(j_0003c529, xfer, m_guardTargetType);
 *xfer == m_locationToGuard;
 thunkFree2(j_0000c9b4, xfer, &m_objectToGuard);
 *xfer == m_extra68;
 AsciiString triggerName;
 if (m_areaToGuard) triggerName = m_areaToGuard->m_name;
 *xfer == triggerName;
 if (xfer->IsLoading() && asciiHasText(triggerName)) m_areaToGuard = TheTerrainLogic->getTriggerAreaByName(triggerName);
 AsciiString attackName;
 if (m_attackInfo) attackName = m_attackInfo->getName();
 *xfer == attackName;
 if (xfer->IsLoading()) m_attackInfoName = attackName;
 *xfer == m_waypointCount;
 if (m_waypointCount < 0 || m_waypointCount > 16) throw XferException(5, 0);
 for (int i=0; i<m_waypointCount; ++i) *xfer == m_waypointQueue[i];
 *xfer == m_waypointIndex;
 *xfer == m_executingWaypointQueue;
 unsigned int id = 0x7fffffff;
 if (m_completedWaypoint) id = m_completedWaypoint->m_id;
 *xfer == id;
 if (xfer->IsLoading()) m_completedWaypoint = TheTerrainLogic->getWaypointByID(id);
 *xfer == m_waitingForPath;
 bool gotPath = m_path != 0;
 *xfer == gotPath;
 if (xfer->IsLoading() && gotPath) m_path = new Path;
 if (gotPath) m_path->xfer00401C70(xfer);
 thunkFree2(j_0000c9b4, xfer, &m_requestedVictimID);
 *xfer == m_requestedDestination;
 *xfer == m_requestedDestination2;
 thunkFree2(j_0000c9b4, xfer, &m_ignoreObstacleID);
 *xfer == m_f168;
 *xfer == m_u178;
 *xfer == m_queueForPathFrame;
 *xfer == m_finalPosition;
 *xfer == m_doFinalPosition;
 *xfer == m_isAttackPath;
 *xfer == m_isFinalGoal;
 *xfer == m_isApproachPath;
 *xfer == m_isSafePath;
 *xfer == m_movementComplete;
 *xfer == m_isSafePath;
 *xfer == m_upgradedLocomotors;
 *xfer == m_canPathThroughUnits;
 *xfer == m_randomlyOffsetMoodCheck;
 thunkFree2(j_0000c9b4, xfer, &m_repulsor1);
 thunkFree2(j_0000c9b4, xfer, &m_repulsor2);
 thunkFree2(j_0000c9b4, xfer, &m_moveOutOfWay1);
 thunkFree2(j_0000c9b4, xfer, &m_moveOutOfWay2);
 if (xfer->IsLoading()) { m_locomotorSet.clear(); m_curLocomotor = 0; }
 thunkThis2(j_000111da, &m_locomotorSet, xfer, &m_curLocomotor);
 thunkFree2(j_0003786c, xfer, &m_curLocomotorSet);
 xfer->XferRawBytes(&m_locomotorGoalType, 4);
 *xfer == m_locomotorGoalData;
 for (int t = 0; t < 2; ++t) if (m_turretAI[t]) *xfer == *m_turretAI[t];
 thunkFree2(j_000068fc, xfer, &m_turretSyncFlag);
 thunkFree2(j_00016c1b, xfer, &m_attitude);
 *xfer == m_nextMoodCheckTime;
 AsciiString name220;
 if (m_extra220) name220 = *reinterpret_cast<AsciiString *>(m_extra220);
 *xfer == name220;
 if (xfer->IsLoading()) {
  if (asciiHasText(name220)) m_extra220 = (Rva00336283Element *)((Rva001D0610Lua *)TheLuaScriptEngine)->rva002EBF60(name220);
  else m_extra220 = 0;
 }
 m_extra224.DoXfer(*xfer);
 thunkFree2(j_0000c9b4, xfer, &m_extra238);
 *xfer == m_b338;
 thunkThis1(j_00026dd7, &m_flags220, xfer);
 thunkThis1(j_00026dd7, &m_flags248, xfer);
 *xfer == m_b339;
 *xfer == m_b31C;
 thunkThis1(j_00002dec, &m_lastOutsideCommand, xfer);
 *xfer == m_b33A;
 if (version.m_minimum > 1) *xfer == m_f1A0;
 *xfer == m_b32F;
 *xfer == m_b336;
 *xfer == m_b333;
 *xfer == m_b334;
 *xfer == m_b329;
 *xfer == m_b325;
 *xfer == m_b326;
 *xfer == m_b330;
 *xfer == m_b324;
 *xfer == m_b335;
 *xfer == m_b337;
 *xfer == m_b32E;
 *xfer == m_b332;
 if (version.m_minimum >= 3) {
  *xfer == m_f1D4;
  xfer->XferRawBytes(&m_guardMode, 4);
  *xfer == m_extra174;
  *xfer == m_extra234;
  thunkThis1(j_00035a0d, &m_flags270, xfer);
 }
 if (version.m_minimum >= 4) *xfer == m_b33B;
 if (version.m_minimum >= 6) *xfer == m_i33C;
}
