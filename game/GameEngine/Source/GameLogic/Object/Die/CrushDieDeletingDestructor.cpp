// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CrushDie.
// Vtable 0x00CB2C84 slots name this class (?getClassMemoryPool@CrushDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0000A42F to this 30-byte wrapper, whose complete destructor
// route ILT 0x000060B9 reaches cleanup body 0x00254960.

class CrushDie
{
protected:
	virtual ~CrushDie();
private:
	friend void forceCrushDieDeletingDestructor();
};

void forceCrushDieDeletingDestructor()
{
	CrushDie value;
}
