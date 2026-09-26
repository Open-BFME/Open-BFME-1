// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LightPulseFXNugget.
// Vtable 0x00CF3408 slots name this class (?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z and ?doFXObj@LightPulseFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x00029E0B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00034A9A reaches cleanup body 0x00427390.

class LightPulseFXNugget
{
protected:
	virtual ~LightPulseFXNugget();
private:
	friend void forceLightPulseFXNuggetDeletingDestructor();
};

void forceLightPulseFXNuggetDeletingDestructor()
{
	LightPulseFXNugget value;
}
