// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CastleUpgrade.
// Vtable 0x00CCC2C4 slots name this class (?getModuleNameKey@CastleUpgrade@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00038096 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00019AC4 reaches cleanup body 0x002D3DA0.

class CastleUpgrade
{
protected:
	virtual ~CastleUpgrade();
private:
	friend void forceCastleUpgradeDeletingDestructor();
};

void forceCastleUpgradeDeletingDestructor()
{
	CastleUpgrade value;
}
