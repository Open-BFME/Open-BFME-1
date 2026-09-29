// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SupplyTruckAIUpdate@@: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// Open-BFME5: SupplyTruckAIUpdate::SupplyTruckAIUpdate, retail 0x002C6AE0 (280 B,
// boundary 0x002C6AE0..0x002C6BF7).
//
// IDENTITY. ?friend_newModuleInstance@SupplyTruckAIUpdate@@SAPAVModule@@ at
// 0x0011B930 is the only caller, through its ILT thunk, and the six vptr
// stores below (0x010C8FE8 primary, 0x010C8F20 at +0x0c, 0x010C8F10 at +0x10,
// 0x010C8F0C at +0x20, 0x010C8EF0 at +0x24, and 0x010C8E30 then 0x010C8E90 on
// the secondary at +0x340) all belong to SupplyTruckAIUpdate's own vtable
// group. The name that came with the lift is therefore proven, not assumed.
//
// LAYOUT. This is an ABI view rather than the game/ class, and the reason is
// recorded here so nobody reads it as a claim about the real hierarchy: the
// repository's own AIUpdateInterface / UpdateModule chain puts the secondary
// base's vptr at +0x218 where retail has +0x340, so no translation of the
// present-day bases can hold this body until those widths are reconciled. Every
// width below is one this body witnesses:
//
//   +0x00  primary vptr, 0x010C8FE8
//   +0x04  m_moduleData   `mov eax,[esi+4]; add eax,0x84` puts the voice at
//                         module data +0x84
//   +0x08  m_object       `mov ecx,[esi+8]` is the state machine's argument
//   +0x0c  0x010C8F20     +0x10 0x010C8F10 (three dwords follow)
//   +0x20  0x010C8F0C     +0x24  0x010C8EF0 (padding to +0x340)
//   +0x340 secondary vptr, 0x010C8E30 before the voice ctor, 0x010C8E90 after
//   +0x344 m_supplyTruckStateMachine     +0x348 m_preferredDock
//   +0x34c m_numberBoxes                 +0x350 and +0x354 unnamed
//   +0x358, +0x35c, +0x360, +0x361 unnamed flags
//   +0x364 m_suppliesDepletedVoice
//
// That +0x344 reading is in tension with the sibling view in
// SupplyTruckAIUpdate_updateAndPrivateDock_Thunk.cpp, which puts
// m_supplyTruckStateMachine at +0x334 on the strength of `mov eax,[ecx+4]`
// read through the secondary base. Both are byte-verified; they disagree about
// which class owns the 0x330..0x340 gap, and neither reading moves an offset
// the other body uses. The stores at +0x007f and +0x00e0 are what fix 0x344
// here.
//
// SHAPE. Two spellings in the body are forced by the bytes, not by taste, and
// both are load-bearing:
//
//   * The five leading dword clears go through `volatile unsigned int *`. The
//     clear of +0x344 is dead -- the `new` result overwrites it at +0x00e0 --
//     and MSVC 7.1 sinks a dead store whose address a later store also writes,
//     which rotates the whole block by one and lifts `push 0x44` above it.
//     Viewing that one clear through a different pointer type stops the merge
//     without changing a byte of the output.
//   * Exactly one of the four trailing flag stores is volatile. Volatile is
//     what keeps MSVC's list scheduler from hoisting that store above the
//     allocation; making all four volatile, or none, moves it to the other side
//     of retail's `push 0x44`.

class Thing;
class ModuleData;
class Object;
class AsciiString;

extern const AsciiString Rva01336E50Str;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameEngineAudio/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &name, int priority );		///< ILT 0x00025306
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=( const AudioEventRTS & );			///< ILT 0x0001F753

private:
	unsigned char m_unreconstructed_04[0x6c];
};

// Only vtable slot 7 (`call [edx+0x1c]`) is reached from this body; the six
// virtuals before it exist only to place it. sizeof is 0x44, the `push 0x44`
// operand at +0x009d.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckStateMachine.h
class SupplyTruckStateMachine
{
public:
	SupplyTruckStateMachine( Object *object );					///< ILT 0x00047C80
	virtual ~SupplyTruckStateMachine();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void initDefaultState();								///< `call [edx+0x1c]`, vtable slot 7

private:
	unsigned char m_unreconstructed_04[0x44 - 4];
};

// The only reads of the base this body makes are the two zeroing stores at
// +0x04 and +0x08, so its width here is fixed by the body, not by a header.
class BehaviorModule
{
public:
	virtual void slot00();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// The ILT slot 0x000292A3 is named for this ctor and tail-jumps to
// AIUpdateInterface's at 0x0027F4B0, so the call below reaches retail's bytes.
class AnimalAIUpdateBase : public BehaviorModule
{
public:
	AnimalAIUpdateBase( Thing *thing, const ModuleData *moduleData );

	Object *getObject() const { return m_object; }
};

// The remaining secondary bases, each named for the vtable this body stores
// into it. Only their widths are witnessed, and each width is fixed by where
// the next vptr store lands.
template <int N> class __declspec(novtable) Rva010C8F20Base { public: virtual void slot00() = 0; };
class __declspec(novtable) Rva010C8F10Base { public: virtual void slot00() = 0; private: unsigned int m_unreconstructed_10[3]; };
class __declspec(novtable) Rva010C8EF0Base { public: virtual void slot00() = 0; private: unsigned char m_unreconstructed_28[0x340 - 0x28]; };
class Rva010C8E90Base { public: virtual ~Rva010C8E90Base(); virtual void slot00(); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIUpdateModuleData
{
private:
	unsigned char m_unreconstructed_00[0x84];

public:
	AudioEventRTS m_suppliesDepletedVoice;						///< module data +0x84
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIUpdate : public AnimalAIUpdateBase, public Rva010C8F20Base<1>,
	public Rva010C8F10Base, public Rva010C8F20Base<2>, public Rva010C8EF0Base,
	public Rva010C8E90Base
{
public:
	SupplyTruckAIUpdate( Thing *thing, const ModuleData *moduleData );
	virtual ~SupplyTruckAIUpdate();

private:
	volatile SupplyTruckStateMachine *m_supplyTruckStateMachine;	///< retail this+0x344
	volatile unsigned int m_preferredDock;						///< retail this+0x348
	volatile unsigned int m_numberBoxes;							///< retail this+0x34c
	volatile unsigned int m_unreconstructed_350;					///< retail this+0x350
	volatile unsigned int m_unreconstructed_354;					///< retail this+0x354
	bool m_unreconstructed_358;									///< retail this+0x358
	unsigned char m_unreconstructed_359[3];
	unsigned int m_unreconstructed_35c;							///< retail this+0x35c
	bool m_unreconstructed_360;									///< retail this+0x360
	bool m_unreconstructed_361;									///< retail this+0x361
	unsigned char m_unreconstructed_362[2];
	AudioEventRTS m_suppliesDepletedVoice;						///< retail this+0x364
};

// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// Zero Hour's body unchanged, bar the members BFME added at +0x350..+0x361.
SupplyTruckAIUpdate::SupplyTruckAIUpdate( Thing *thing, const ModuleData *moduleData ) :
	AnimalAIUpdateBase( thing, moduleData ),
	m_suppliesDepletedVoice( Rva01336E50Str, 0 )
{
	*(volatile unsigned int *)&m_supplyTruckStateMachine = 0;
	*(volatile unsigned int *)&m_preferredDock = 0;
	*(volatile unsigned int *)&m_numberBoxes = 0;
	*(volatile unsigned int *)&m_unreconstructed_350 = 0;
	*(volatile unsigned int *)&m_unreconstructed_354 = 0;
	*(volatile bool *)&m_unreconstructed_358 = false;
	*(unsigned int *)&m_unreconstructed_35c = 0;
	*(bool *)&m_unreconstructed_360 = false;
	*(bool *)&m_unreconstructed_361 = false;
	SupplyTruckStateMachine *stateMachine = new SupplyTruckStateMachine( getObject() );
	*(volatile SupplyTruckStateMachine **)&m_supplyTruckStateMachine = stateMachine;
	stateMachine->initDefaultState();
	const SupplyTruckAIUpdateModuleData *supplyModuleData = (const SupplyTruckAIUpdateModuleData *)m_moduleData;
	m_suppliesDepletedVoice = supplyModuleData->m_suppliesDepletedVoice;
}
