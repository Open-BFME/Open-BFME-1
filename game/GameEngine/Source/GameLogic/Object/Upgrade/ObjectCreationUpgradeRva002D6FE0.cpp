// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

// ObjectCreationUpgrade primary-table slot 6, retail 0x002D6FE0 (210 bytes),
// through ILT 0x000432F7 from the table at VA 0x010CD620.  Slot 2 there is
// the const BitFlags<192> test (wouldUpgrade), slot 7 the matched
// ObjectCreationUpgrade::removeUpgrade and slot 9 the matched
// upgradeImplementation; the satisfied branch is Zero Hour's giveSelfUpgrade
// sequence.  BFME adds this re-evaluation against the controlling player's
// and the object's completed upgrades; its name is unproven.  The mask is
// BFME's BitFlags<192>, an STLport bitset<192>.

#include "../../../../Include/Common/ScalarTypes.h"


struct UpgradeMaskType
{
	_STL::bitset<192> m_bits;
	void set(const UpgradeMaskType &other) { m_bits |= other.m_bits; }
};

class Player
{
public:
	const UpgradeMaskType &getCompletedUpgradeMask() const { return m_upgradesCompleted; }
private:
	unsigned char m_pad[0x8c];
	UpgradeMaskType m_upgradesCompleted;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	const UpgradeMaskType &getObjectCompletedUpgradeMask() const { return m_objectUpgradesCompleted; }
private:
	unsigned char m_pad[0x224];
	UpgradeMaskType m_objectUpgradesCompleted;
};

class ObjectCreationUpgrade
{
public:
	virtual Bool slot00() const;
	virtual Bool slot04(const UpgradeMaskType &);
	virtual Bool wouldUpgrade(const UpgradeMaskType &keyMask) const;
	virtual Bool slot0c(const UpgradeMaskType &);
	virtual Bool slot10();
	virtual void slot14();
	virtual void rva002D6FE0();
	virtual void removeUpgrade();
	virtual void setUpgradeExecuted(Bool executed);
	virtual void upgradeImplementation();
	virtual void slot28();
	virtual void performUpgradeFX();
	virtual void slot30();
	virtual void processUpgradeRemoval();

	Object *getObject() const { return m_object; }

private:
	unsigned char m_pad04[0xc];
	Object *m_object;
	unsigned char m_pad14[0x18];
	Bool m_upgradeExecuted;
};

// ?rva002D6FE0@ObjectCreationUpgrade@@UAEXXZ
void ObjectCreationUpgrade::rva002D6FE0()
{
	UpgradeMaskType keyMask = getObject()->getControllingPlayer()->getCompletedUpgradeMask();
	keyMask.set(getObject()->getObjectCompletedUpgradeMask());
	if (wouldUpgrade(keyMask))
	{
		if (!m_upgradeExecuted)
		{
			performUpgradeFX();
			processUpgradeRemoval();
			upgradeImplementation();
			setUpgradeExecuted(true);
		}
	}
	else
	{
		removeUpgrade();
	}
}
