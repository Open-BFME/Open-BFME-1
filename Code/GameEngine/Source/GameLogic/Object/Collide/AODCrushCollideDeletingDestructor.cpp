// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AODCrushCollide.
// Vtable 0x00CA9AC4 slots name this class (?getModuleNameKey@AODCrushCollide@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0001BEEB to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000F781 reaches cleanup body 0x00215A70.

class AODCrushCollide
{
protected:
	virtual ~AODCrushCollide();
private:
	friend void forceAODCrushCollideDeletingDestructor();
};

void forceAODCrushCollideDeletingDestructor()
{
	AODCrushCollide value;
}
