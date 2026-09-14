// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FadeAndDieOrnamentUpdate.
// Constructor 0x00292230 installs dedicated vtable 0x00CBE9B4; its slot
// zero routes through ILT 0x0004560B to this 30-byte wrapper, whose complete
// destructor route ILT 0x00045F20 reaches cleanup body 0x002921D0.

class FadeAndDieOrnamentUpdate
{
protected:
	virtual ~FadeAndDieOrnamentUpdate();
private:
	friend void forceFadeAndDieOrnamentUpdateDeletingDestructor();
};

void forceFadeAndDieOrnamentUpdateDeletingDestructor()
{
	FadeAndDieOrnamentUpdate value;
}
