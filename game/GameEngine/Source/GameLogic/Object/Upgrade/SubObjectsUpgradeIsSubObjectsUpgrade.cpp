// cl: /DNDEBUG /MD /EHsc /O2

// The retail body at 0x002D8410 implements the slot-4
// UpgradeModuleInterface::isSubObjectsUpgrade override for SubObjectsUpgrade.
class SubObjectsUpgrade
{
protected:
	virtual bool isSubObjectsUpgrade();
};

// ?isSubObjectsUpgrade@SubObjectsUpgrade@@MAE_NXZ
bool SubObjectsUpgrade::isSubObjectsUpgrade()
{
	return true;
}
