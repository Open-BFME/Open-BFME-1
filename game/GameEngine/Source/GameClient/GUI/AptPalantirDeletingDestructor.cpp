// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0079DBD0 calls AptPalantir::~AptPalantir through ILT 0x0000867F.

class AptPalantir
{
public:
	virtual ~AptPalantir();
};

__declspec(noinline) AptPalantir::~AptPalantir() {}

void Force_AptPalantir_Deleting_Destructor(AptPalantir *palantir)
{
	delete palantir;
}
