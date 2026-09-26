// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HordeMemberCollide.
// Vtable 0x00CA9F04 slots name this class (?getModuleNameKey@HordeMemberCollide@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00017760 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002BA71 reaches cleanup body 0x00216760.

class HordeMemberCollide
{
protected:
	virtual ~HordeMemberCollide();
private:
	friend void forceHordeMemberCollideDeletingDestructor();
};

void forceHordeMemberCollideDeletingDestructor()
{
	HordeMemberCollide value;
}
