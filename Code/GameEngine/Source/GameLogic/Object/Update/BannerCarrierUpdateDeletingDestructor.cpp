// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BannerCarrierUpdate.
// Vtable 0x00CBBB84 slots name this class (?getModuleNameKey@BannerCarrierUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00031F84 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000301B6 reaches cleanup body 0x00282E70.

class BannerCarrierUpdate
{
protected:
	virtual ~BannerCarrierUpdate();
private:
	friend void forceBannerCarrierUpdateDeletingDestructor();
};

void forceBannerCarrierUpdateDeletingDestructor()
{
	BannerCarrierUpdate value;
}
