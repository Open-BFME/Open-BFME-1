// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0079DBD0 calls AptPalantir::~AptPalantir through ILT 0x0000867F.

class AptPalantir
{
	friend void forceAptPalantirDeletingDestructorCopy(const AptPalantir &that);
public:
	virtual ~AptPalantir();
};


void Force_AptPalantir_Deleting_Destructor(AptPalantir *palantir)
{
	delete palantir;
}

// ~AptPalantir is matched out of line (AptPalantirDestructor.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceAptPalantirDeletingDestructorCopy(const AptPalantir &that)
{
	AptPalantir value(that);
}
