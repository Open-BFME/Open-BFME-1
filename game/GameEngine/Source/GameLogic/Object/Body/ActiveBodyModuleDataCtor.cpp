// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ActiveBodyModuleData's constructor, retail 0x0020F7C0, 230 bytes.
//
// The BFME1 module data is much wider than the Zero Hour twin, and every offset
// below is the binary's own: the retail FieldParse table at 0x00CA7AA8 pairs
// each INI key with the member offset this body writes.
//
//   0x08 MaxHealth                           0x28 UseDefaultDamageSettings
//   0x0C InitialHealth                       0x2C GrabObject
//   0x10 MaxHealthDamaged                    0x30 DamagedAttributeModifier
//   0x14 MaxHealthReallyDamaged              0x34 ReallyDamagedAttributeModifier
//   0x18 DodgePercent                        0x38 GrabFX
//   0x1C EnteringDamagedTransitionTime       0x3C GrabDamage
//   0x20 EnteringReallyDamagedTransitionTime 0x40 GrabOffset      (2 floats)
//   0x24 RecoveryTime                        0x48 HealingBuffFx   (FXList *)
//                                            0x4C CheerRadius
//                                            0x50 vector
//
// 0x00..0x07 is the ModuleData base; retail inlines its constructor away, so
// the only vptr store in the body is this class's own, at 0x010A76C0.
//
// 0x2C is handed the literal "EntThrownBuildingRock" (21 characters) through
// StringBase<char>::set, the two attribute-modifier names at 0x30/0x34 are
// emptied through the release body (retail's StringBase<char>::clear IS the
// releaseBuffer body at 0x00887940, the one the destructor reaches too), and
// the FXList pointer at 0x48 is filled from the GlobalData default healing buff
// FX list at +0xAA4 through the one guarded lookup, with isNotEmpty() and str()
// spelled the way those two inline accessors compile.

typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p12pod { int a[3]; };

// The container at +0x50 is three words wide in retail -- begin, finish and
// capacity -- and the sibling destructor body walks it with a 12-byte stride.
// STLport 4.5.3 as vendored here is four words wide because its base keeps the
// allocator, so the shape is spelled out rather than included.
class Gen_p12podVec
{
public:
	Gen_p12podVec() : m_start(0), m_finish(0), m_capacity(0) {}
	~Gen_p12podVec() { release(); }

private:
	void release(void);

	Gen_p12pod *m_start;
	Gen_p12pod *m_finish;
	Gen_p12pod *m_capacity;
};

class GlobalData;
class FXList;

extern const char Rva006A16B0Empty[];

// The retail string: m_data points at a block whose length word sits at +4 and
// whose characters start at +8; a null m_data reads as the empty literal.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

	// retail StringBase<char>::set, the two-argument setter the ledger already
	// pins at 0x00887D20
	void set(const char *text, int length);

	// The two attribute-modifier names are emptied through the release body:
	// retail's StringBase<char>::clear() IS that body (the ledger carries
	// ?clear@?$StringBase@D@@QAEXXZ and ?releaseBuffer@BFMERetailAsciiString on
	// the same 0x00887940), so the public releaseBuffer spelling already pinned
	// for this class is the one used here.
	void releaseBuffer(void);

	const char *str(void) const { return m_data ? m_data + 8 : Rva006A16B0Empty; }

	bool isNotEmpty(void) const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}

private:
	char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

// The one global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData
// (defined in Common/GlobalData.cpp). This TU reads its +0xAA4 string through
// a view class, so the extern carries the canonical type and the view is cast.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class BodyModuleGlobalDataView
{
public:
	unsigned char m_head[0xAA4];
	BFMERetailAsciiString m_defaultUnitHealingBuffFxList;	///< retail +0xAA4
};

extern FXListStore *TheFXListStore;

// The ModuleData base is unreconstructed: retail inlines its constructor away
// (the class's own vptr store is the only one in the body) but its destructor
// still counts -- the unwind state reaches 4 before the set() call, which is
// this base plus the three strings at +0x2C/+0x30/+0x34 and the container
// below -- so the base is spelled as a class with a destructor.
class ModuleDataBase
{
public:
	~ModuleDataBase();

	unsigned char m_head[0x04];								///< retail +0x04..+0x07, behind the vptr
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBodyModuleData : public ModuleDataBase
{
public:
	ActiveBodyModuleData();

	virtual ~ActiveBodyModuleData();

private:
	Real m_maxHealth;											///< +0x08
	Real m_initialHealth;										///< +0x0C
	Real m_maxHealthDamaged;									///< +0x10
	Real m_maxHealthReallyDamaged;								///< +0x14
	Real m_dodgePercent;										///< +0x18
	UnsignedInt m_enteringDamagedTransitionTime;				///< +0x1C
	UnsignedInt m_enteringReallyDamagedTransitionTime;			///< +0x20
	UnsignedInt m_recoveryTime;									///< +0x24
	Bool m_useDefaultDamageSettings;								///< +0x28

	BFMERetailAsciiString m_grabObject;						///< +0x2C
	BFMERetailAsciiString m_damagedAttributeModifier;			///< +0x30
	BFMERetailAsciiString m_reallyDamagedAttributeModifier;		///< +0x34
	const FXList *m_grabFX;									///< +0x38
	Real m_grabDamage;											///< +0x3C
	Real m_grabOffsetX;											///< +0x40
	Real m_grabOffsetY;											///< +0x44
	const FXList *m_healingBuffFx;								///< +0x48
	Real m_cheerRadius;											///< +0x4C
	Gen_p12podVec m_bfmeVector;									///< +0x50
};

// ??0ActiveBodyModuleData@@QAE@XZ
ActiveBodyModuleData::ActiveBodyModuleData()
	: m_cheerRadius(200.0f)
{
	m_maxHealth = 0.0f;
	m_maxHealthDamaged = 0.0f;
	m_maxHealthReallyDamaged = 0.0f;
	m_initialHealth = -1.0f;
	m_recoveryTime = 0;
	m_enteringDamagedTransitionTime = 0;
	m_enteringReallyDamagedTransitionTime = 0;
	m_dodgePercent = 0.0f;
	m_useDefaultDamageSettings = true;

	m_grabObject.set("EntThrownBuildingRock", 21);

	m_grabFX = 0;
	m_healingBuffFx = 0;
	m_grabDamage = 200.0f;
	m_grabOffsetX = 0.0f;
	m_grabOffsetY = 0.0f;

	m_damagedAttributeModifier.releaseBuffer();
	m_reallyDamagedAttributeModifier.releaseBuffer();

	if (((BodyModuleGlobalDataView *)TheWritableGlobalData)
		->m_defaultUnitHealingBuffFxList.isNotEmpty()) {
		m_healingBuffFx = TheFXListStore->findFXList(
			((BodyModuleGlobalDataView *)TheWritableGlobalData)
				->m_defaultUnitHealingBuffFxList.str());
	}
}
