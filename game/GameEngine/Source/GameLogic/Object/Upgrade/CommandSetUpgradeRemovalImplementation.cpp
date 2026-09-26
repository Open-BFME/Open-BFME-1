// cl: /DNDEBUG /MD /EHsc
// CommandSetUpgrade's BFME slot-7 removal hook at retail 0x002D4470.
// The secondary UpgradeMux vtable proves the slot identity.

#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef bool Bool;

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	int compare(const AsciiString &other) const;
	~AsciiString() {}
};

#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?j_000220c5@@YAXXZ")

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
	virtual void upgradeRemovalImplementation() = 0;
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
	virtual void upgradeRemovalImplementation();
};

void CommandSetUpgrade::upgradeRemovalImplementation()
{
	if (!isAlreadyUpgraded())
		return;

	Object *object = m_object;
	if (object->m_commandSetStringOverride.compare(*(const AsciiString *)
		((const char *)m_moduleData + 0x70)) == 0)
		((Rva0022A620Obj *)object)->set((const char *)0x0107301C);
	*(Bool *)((char *)TheControlBar + 0x24) = true;
	setUpgradeExecuted(false);
}
