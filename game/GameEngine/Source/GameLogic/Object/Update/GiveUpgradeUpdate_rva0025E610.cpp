// Retail [0x0025E610,0x0025E73C), 300 bytes, RET 0.
// Constructor25D9A0+28 installs VA010B5368 at primary+0;
// slot15 contains ILT2E1D6 -> this full body.  The owner is kept address-labelled:
// the GiveUpgradeUpdate constructor/vtable evidence identifies the object
// family and slot, but not this method's original source name.
//
// The two calls whose semantic names are still unresolved are deliberately
// direct RVA-labelled member declarations.  They preserve thiscall ECX and
// the observed argument/result ABI without routing through raw function
// pointers or asserting an ICF alias.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include "Lib/BaseType.h"
#include "Common/GameType.h"
#include "Common/GameCommon.h"
#include "Common/KindOf.h"

typedef unsigned int UnsignedInt;

class UpgradeTemplate;
class Object;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
};

class Drawable
{
public:
	void colorFlash(const RGBColor *color, UnsignedInt decayFrames,
		UnsignedInt attackFrames, UnsignedInt sustainAtPeak);
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object
{
public:
	virtual void objectSlot00();
	virtual void objectSlot01();
	virtual void objectSlot02();
	virtual void objectSlot03();
	virtual void objectSlot04();
	virtual void objectSlot05();
	virtual void objectSlot06();
	virtual void objectSlot07();
	virtual void objectSlot08();
	virtual void objectSlot09();
	virtual Drawable *getDrawable();

	// BFME Object offsets proven by the target loads.  The upgrade mask is a
	// 192-bit/six-word view; it is not the neighboring 86-bit status mask.
	unsigned char m_pad04[0x200];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x1c];
	UnsignedInt m_upgradeMask[6];
	unsigned char m_pad23c[0x108];
	UnsignedInt m_privateStatus; // first word of the witnessed status field

	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	void giveUpgrade(const UpgradeTemplate *upgrade);
	void *unidentified_001BFE20() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int objectID);
	void deselectObject(Object *object, unsigned short playerMask,
		Bool affectClient);
};

// The retail global is typed as UpgradeCenter in the symbol table.  Its
// bfmeFindND operation is the independently matched BfmeThingND body.

struct BfmeNodeND;
class BfmeThingND
{
public:
	BfmeNodeND *bfmeFindND(const UnsignedInt *mask);
};

extern GameLogic *TheBfmeGameLogic;

// Existing typed pin: this ILT/body is shared by the neighboring charge
// application and carries the live receiver in ECX with no stack arguments.
class Rva0025EF90Owner
{
public:
	void callAt002A9850();
};

// Existing matched target-check ABI/name, reached through ILT 0x00008995.
class SpecialAbilityUpdate
{
public:
	Bool checkTarget(Object *target);
};

class UpgradeSink
{
public:
#define UPGRADE_SINK_SLOT(n) virtual void slot##n();
	UPGRADE_SINK_SLOT(00) UPGRADE_SINK_SLOT(01) UPGRADE_SINK_SLOT(02)
	UPGRADE_SINK_SLOT(03) UPGRADE_SINK_SLOT(04) UPGRADE_SINK_SLOT(05)
	UPGRADE_SINK_SLOT(06) UPGRADE_SINK_SLOT(07) UPGRADE_SINK_SLOT(08)
	UPGRADE_SINK_SLOT(09) UPGRADE_SINK_SLOT(10) UPGRADE_SINK_SLOT(11)
	UPGRADE_SINK_SLOT(12) UPGRADE_SINK_SLOT(13) UPGRADE_SINK_SLOT(14)
	UPGRADE_SINK_SLOT(15) UPGRADE_SINK_SLOT(16) UPGRADE_SINK_SLOT(17)
	UPGRADE_SINK_SLOT(18) UPGRADE_SINK_SLOT(19) UPGRADE_SINK_SLOT(20)
	UPGRADE_SINK_SLOT(21) UPGRADE_SINK_SLOT(22) UPGRADE_SINK_SLOT(23)
	UPGRADE_SINK_SLOT(24) UPGRADE_SINK_SLOT(25) UPGRADE_SINK_SLOT(26)
	UPGRADE_SINK_SLOT(27) UPGRADE_SINK_SLOT(28) UPGRADE_SINK_SLOT(29)
	UPGRADE_SINK_SLOT(30) UPGRADE_SINK_SLOT(31) UPGRADE_SINK_SLOT(32)
	UPGRADE_SINK_SLOT(33) UPGRADE_SINK_SLOT(34) UPGRADE_SINK_SLOT(35)
	UPGRADE_SINK_SLOT(36) UPGRADE_SINK_SLOT(37) UPGRADE_SINK_SLOT(38)
	UPGRADE_SINK_SLOT(39) UPGRADE_SINK_SLOT(40) UPGRADE_SINK_SLOT(41)
	UPGRADE_SINK_SLOT(42)
	// Matched ScriptActions::doUnitReceiveUpgrade independently uses this
	// returned interface at +0xAC with the upgrade-template pointer.
	virtual void *slotAC(const UpgradeTemplate *upgrade);
#undef UPGRADE_SINK_SLOT
};

// Retail 0x0025DE10: target call is thiscall(Object*) -> pointer.  The
// semantic callee identity remains unresolved, so this declaration is honest
// about only the address-derived ABI.
class Rva0025DE10Call
{
public:
	UpgradeSink *callAt0025DE10(Object *target);
};

// Retail 0x0025E0B0: target call is thiscall(Object*) -> void.  It is kept
// separate from the 0x0025E610 owner and from any unproven semantic method
// spelling.
class Rva0025E0B0Module
{
public:
	void update(Object *object);
};

class Rva0025E610Owner
{
public:
	// Primary vtable evidence places this body in slot 15.  Placeholder slots
	// preserve that ABI while leaving the original class/method name unknown.
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void runAt0025E610();

private:
	unsigned char m_pad04[4];
	Object *m_object;
	unsigned char m_gap0c[0xa0];
	int m_objectID;
	unsigned char m_gapb0[0x38];
	Bool m_created;
	Bool m_objectCreated;
};

// ?runAt0025E610@Rva0025E610Owner@@UAEXXZ
void Rva0025E610Owner::runAt0025E610()
{
	if (m_created)
		return;

	reinterpret_cast<Rva0025EF90Owner *>(this)->callAt002A9850();

	Object *object = m_object;
	Object *target = TheBfmeGameLogic->findObjectByID(m_objectID);
	if (target == 0 || (target->m_privateStatus & 1) != 0 ||
		!reinterpret_cast<SpecialAbilityUpdate *>(this)->checkTarget(target))
		goto failure;

	m_objectCreated = false;
	UpgradeTemplate *upgrade = reinterpret_cast<UpgradeTemplate *>(
		reinterpret_cast<BfmeThingND *>(TheUpgradeCenter)->bfmeFindND(
			object->m_upgradeMask));
	if (upgrade == 0)
	{
		reinterpret_cast<Rva0025E0B0Module *>(this)->update(object);
		return;
	}

	UpgradeSink *sink;
	if (reinterpret_cast<Thing *>(target)->isKindOf(
			static_cast<KindOfType>(108)))
		sink = reinterpret_cast<UpgradeSink *>(
			target->unidentified_001BFE20());
	else
		sink = reinterpret_cast<Rva0025DE10Call *>(this)->callAt0025DE10(
			target);

	if (sink != 0)
		sink->slotAC(upgrade);
	else if (target->affectedByUpgrade(upgrade))
	{
		RGBColor white = { 0.99f, 0.99f, 0.99f };
		target->giveUpgrade(upgrade);
		Drawable *drawable = target->getDrawable();
		if (drawable != 0)
			drawable->colorFlash(&white, 4, 4, 15);
	}

	TheBfmeGameLogic->deselectObject(object, 0xffff, true);
	reinterpret_cast<Rva0025E0B0Module *>(this)->update(object);
	return;

failure:
	AICommandInterface *commands = reinterpret_cast<AICommandInterface *>(
		reinterpret_cast<char *>(object->m_ai) + 0x20);
	commands->aiIdle(CMD_FROM_AI);
}
