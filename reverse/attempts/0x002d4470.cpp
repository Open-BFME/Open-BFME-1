// ?upgradeRemovalImplementation@CommandSetUpgrade@@MAEXXZ
// partial score=0.97 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// CommandSetUpgrade's BFME slot-7 removal hook at retail 0x002D4470.
//
// The constructor at 0x002D41A0 installs the UpgradeMux secondary vtable
// 0x010CC330 at complete-object +0x10.  Its slot 7 is reached through ILT
// 0x000319B2.  The matched slot-6 sibling at 0x002D43A0 calls this hook
// before attempting the newly completed upgrade, establishing the BFME
// removal-hook identity rather than the later Zero Hour implementation name.

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

// Retail calls the compare ILT at 0x000220C5, which targets the matched
// StringBase<char>::compare body at 0x0005FEB0.
#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?j_000220c5@@YAXXZ")

class Object
{
public:
	private:
	unsigned char m_beforeCommandSetStringOverride[0x328];

	public:
	AsciiString m_commandSetStringOverride;
};

// The by-value setter is the matched 0x0022A620 body reached through its ILT.
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
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpgradeMaskType;

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

class CommandSetUpgradeModuleData
{
private:
	unsigned char m_beforeTriggerAlt[0x70];

public:
	AsciiString m_triggerAlt;
};

// ?upgradeRemovalImplementation@CommandSetUpgrade@@MAEXXZ
void CommandSetUpgrade::upgradeRemovalImplementation()
{
	if (!isAlreadyUpgraded())
		return;

	Object *object = m_object;
	const CommandSetUpgradeModuleData &data =
		*(const CommandSetUpgradeModuleData *)m_moduleData;
	if (object->m_commandSetStringOverride.compare(
		data.m_triggerAlt) == 0)
		((Rva0022A620Obj *)object)->set((const char *)0x0107301C);
	*(Bool *)((char *)TheControlBar + 0x24) = true;
	setUpgradeExecuted(false);
}
