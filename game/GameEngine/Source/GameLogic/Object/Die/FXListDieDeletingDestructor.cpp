// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FXListDie.
// Vtable 0x00CB2FDC slots name this class (?getClassMemoryPool@FXListDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000162D4 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000496D9 reaches cleanup body 0x00255320.

class FXListDie
{
protected:
	virtual ~FXListDie();
private:
	friend void forceFXListDieDeletingDestructor();
};

void forceFXListDieDeletingDestructor()
{
	FXListDie value;
}
