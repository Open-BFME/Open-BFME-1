// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HeroDie.
// Vtable 0x00CB312C slots name this class (?getModuleNameKey@HeroDie@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000AAC4 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003EEA5 reaches cleanup body 0x00255580.

class HeroDie
{
protected:
	virtual ~HeroDie();
private:
	friend void forceHeroDieDeletingDestructor();
};

void forceHeroDieDeletingDestructor()
{
	HeroDie value;
}
