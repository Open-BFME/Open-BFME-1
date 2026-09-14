// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x002408B0 calls HordeContain::~HordeContain through ILT 0x0001AB90.

class HordeContain
{
public:
	virtual ~HordeContain();
};

__declspec(noinline) HordeContain::~HordeContain() {}

void Force_HordeContain_Deleting_Destructor(HordeContain *contain)
{
	delete contain;
}
