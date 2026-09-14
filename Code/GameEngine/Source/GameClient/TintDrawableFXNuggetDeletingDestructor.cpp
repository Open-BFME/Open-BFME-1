// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TintDrawableFXNugget.
// Vtable 0x00CF34F0 slots name this class (?doFXPos@TintDrawableFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z); its slot zero routes
// through ILT 0x00028AD3 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00044477 reaches cleanup body 0x00427390.

class TintDrawableFXNugget
{
protected:
	virtual ~TintDrawableFXNugget();
private:
	friend void forceTintDrawableFXNuggetDeletingDestructor();
};

void forceTintDrawableFXNuggetDeletingDestructor()
{
	TintDrawableFXNugget value;
}
