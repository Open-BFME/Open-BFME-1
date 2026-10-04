// cl: /DNDEBUG /MD /EHsc
// CommandSetUpgrade::removeUpgrade: UpgradeMux slot 7 at retail 0x002D4470. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot); the TU-local UpgradeMux view
// declares slot 7 under that name so the override keeps its this-adjustment.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// and
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// CommandSetUpgrade's BFME slot-7 removal hook at retail 0x002D4470.
// The secondary UpgradeMux vtable proves the slot identity.

#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef bool Bool;

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() {}
};

extern void j_000220c5();

class Object
{
	unsigned char m_beforeCommandSetStringOverride[0x328];

public:
	AsciiString m_commandSetStringOverride;
};

class Rva0022A620Obj
{
public:
	void set(AsciiString value);
};

class ControlBar;
extern ControlBar *TheControlBar;

class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual Bool attemptUpgrade() = 0;
	virtual Bool wouldUpgrade() const = 0;
	virtual Bool resetUpgrade() = 0;
	virtual Bool isSubObjectsUpgrade() = 0;
	virtual void forceRefreshUpgrade() = 0;
	virtual void postUpgradeCheck() = 0;
	virtual void removeUpgrade() = 0;
	virtual void setUpgradeExecuted(Bool) = 0;
	virtual void upgradeImplementation() = 0;
	virtual void getUpgradeActivationMasks() const = 0;
	virtual void performUpgradeFX() = 0;
	virtual Bool requiresAllActivationUpgrades() const = 0;
	virtual void upgradeMuxSlot13() = 0;
	virtual void upgradeMuxSlot14() = 0;
	virtual void upgradeMuxSlot15() = 0;

private:
	Bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

class UpgradeModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
};

class CommandSetUpgrade : public UpgradeModule
{
protected:
	virtual void removeUpgrade();
};

void CommandSetUpgrade::removeUpgrade()
{
	if (!isAlreadyUpgraded())
		return;

	Object *object = m_object;
	typedef int (AsciiString::*CompareThunk)(const AsciiString &) const;
	union
	{
		void (*function)();
		CompareThunk call;
	} compare = { j_000220c5 };
	if ((object->m_commandSetStringOverride.*compare.call)(
			*(const AsciiString *)((const char *)m_moduleData + 0x70)) == 0)
		((Rva0022A620Obj *)object)->set("");
	*(Bool *)((char *)TheControlBar + 0x24) = true;
	setUpgradeExecuted(false);
}
