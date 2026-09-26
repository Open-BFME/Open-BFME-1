// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CameraShakerVolumeFXNugget.
// Vtable 0x00CF3450 slots name this class (?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z); its slot zero routes
// through ILT 0x0003E0DB to this 30-byte wrapper, whose complete destructor
// route ILT 0x000422AD reaches cleanup body 0x00427390.

class CameraShakerVolumeFXNugget
{
protected:
	virtual ~CameraShakerVolumeFXNugget();
private:
	friend void forceCameraShakerVolumeFXNuggetDeletingDestructor();
};

void forceCameraShakerVolumeFXNuggetDeletingDestructor()
{
	CameraShakerVolumeFXNugget value;
}
