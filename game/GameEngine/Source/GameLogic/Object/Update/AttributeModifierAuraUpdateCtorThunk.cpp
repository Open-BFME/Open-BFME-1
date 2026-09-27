// cl: /DNDEBUG /MD /EHsc
// Real C++ for ??0AttributeModifierAuraUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// which until now was a __declspec(naked) __emit copy of retail.
//
// IDENTITY.  The byte-true factory
//   ?friend_newModuleInstance@AttributeModifierAuraUpdate@@SAPAVModule@@PAVThing@@
//   PBVModuleData@@@Z
// (AttributeModifierAuraUpdateFriendNewModuleInstanceThunk.cpp) does
// `new AttributeModifierAuraUpdate(thing, data)` and allocates 0x28, so a
// MATCHED CALLER names this constructor and fixes its (Thing *, const
// ModuleData *) signature.  The two-round vptr install, the SEH trylevel and
// the `ret 8` tail are the Module-constructor shape.  The 0xAD-byte Ghidra size
// stops inside the epilogue; the real extent is 218 bytes, ending `ret 8` at
// 0x002801A7.
//
// SHAPE.  The first 0x73 bytes are the same three-base module-constructor
// prologue as ?0SpyVisionUpdate (SpyVisionUpdateCtor.cpp): an UpdateModule base
// whose PB_DeepBase base is a real call to the shared ObjectModule constructor
// ILT 0x000170E4, then a second base at +0x20 constructed by the shared
// UpgradeMux constructor ILT 0x0003D24E (body 0x002D9B80, matched as
// ??0Rva002D9B80@@QAE@XZ, whose 13 bytes store a dword and then a byte).
//
// The base-class NAMES are the ones the ledger already records for this class
// rather than fresh inventions:
//   ??_7AttributeModifierAuraUpdate@@6BAttributeModifierAuraUpdateInterface@@@
//     = 0x010BAD08, the vtable this body installs at +0x20
//   ??_7PB_Iface1@@6B@ = 0x0109C9D0 and ??_7PB_Iface2@@6B@ = 0x0109CBA0,
//     the pair the UpdateModule base stores at +0x0C and +0x10
// so targets/game/reverse/dir32_addresses.csv stays satisfied without a new row.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FRAME = 0
};

// The field this body tests is the byte at +0x90.  The matched
// AttributeModifierAuraUpdateModuleData constructor (189B, 0x00280B20) is what
// fixes that offset, and names the same byte.
struct AttributeModifierAuraUpdateModuleData
{
	unsigned char m_leading[ 0x90 ];
	unsigned char m_targetEnemies;
};

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	const AttributeModifierAuraUpdateModuleData *m_moduleData;
	Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData),
		  m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
	{
	}

protected:
	// ?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z is
	// protected and NON-virtual (the I/A pair), so the call at +0x95 is direct.
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

// The second base, at +0x20.  Retail dispatches through slots 0x2C, 0x34, 0x24
// and 0x20 of its vtable 0x010BAD08, so the class carries at least fourteen
// virtuals; the four that are called are named for the slot they occupy.
//
// Its size is 8 bytes: the vptr plus ONE dword.  The matched
// friend_newModuleInstance factory (0x0011A8D0, 96B) allocates 0x28, which is
// the 0x20 of UpdateModule plus 8.  The shared UpgradeMux constructor stores a
// dword at the sub-object's +0 and a byte at its +4; the dword lands on the
// vptr slot, which this ctor overwrites at +0x8F, so only the byte store
// survives and it is what initialises m_at24.
class AttributeModifierAuraUpdateInterface
{
public:
	AttributeModifierAuraUpdateInterface();

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20(bool);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();

protected:
	// Non-virtual, so `this` is adjusted to the +0x20 sub-object once and every
	// dispatch reloads [edi] -- which is what retail does.
	void giveSelfUpgrade()
	{
		slot2c();
		slot34();
		slot24();
		slot20(true);
	}

private:
	unsigned int m_at24;
};

class AttributeModifierAuraUpdate : public UpdateModule,
                                   public AttributeModifierAuraUpdateInterface
{
public:
	AttributeModifierAuraUpdate(Thing *, const ModuleData *);
};

// ??0AttributeModifierAuraUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AttributeModifierAuraUpdate::AttributeModifierAuraUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), AttributeModifierAuraUpdateInterface()
{
	setWakeFrame(getObject(), (UpdateSleepTime)1);
	if (m_moduleData->m_targetEnemies)
	{
		giveSelfUpgrade();
	}
}
