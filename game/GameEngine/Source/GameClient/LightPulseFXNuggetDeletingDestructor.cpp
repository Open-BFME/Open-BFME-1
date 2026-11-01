// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LightPulseFXNugget.
// Vtable 0x00CF3408 slots name this class (?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z and ?doFXObj@LightPulseFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x00029E0B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00034A9A reaches cleanup body 0x00427390.

// The destructor is implicit: retail ~LightPulseFXNugget at 0x00428F90 (own
// ILT 0x00034A9A) is a bare tail jump to FXNugget::~FXNugget
// (ILT 0x000033F0) with no vptr reset, the shape VC7.1 gives an implicit
// virtual destructor; both ILTs are ilt_oracle CONFIRMED exact.

class FXNugget
{
public:
	virtual ~FXNugget();
};

class LightPulseFXNugget : public FXNugget
{
private:
	friend void forceLightPulseFXNuggetDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceLightPulseFXNuggetDeletingDestructor(const LightPulseFXNugget &that)
{
	LightPulseFXNugget value(that);
}
