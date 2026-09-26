// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for WallUpgradeUpdate.
// Vtable 0x00CC529C slots name this class (?getModuleNameKey@WallUpgradeUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00015E38 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002575C reaches cleanup body 0x002B2100.

class WallUpgradeUpdate
{
protected:
	virtual ~WallUpgradeUpdate();
private:
	friend void forceWallUpgradeUpdateDeletingDestructor();
};

void forceWallUpgradeUpdateDeletingDestructor()
{
	WallUpgradeUpdate value;
}
