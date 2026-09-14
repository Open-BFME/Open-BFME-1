// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BoneFXUpdate.
// Vtable 0x00CBCA64 slots name this class (?getModuleNameKey@BoneFXUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000C9BE to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001BCE8 reaches cleanup body 0x00289030.

class BoneFXUpdate
{
protected:
	virtual ~BoneFXUpdate();
private:
	friend void forceBoneFXUpdateDeletingDestructor();
};

void forceBoneFXUpdateDeletingDestructor()
{
	BoneFXUpdate value;
}
