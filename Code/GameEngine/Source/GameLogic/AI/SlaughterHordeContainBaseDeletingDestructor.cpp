// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0024EA90 calls SlaughterHordeContainBase::~SlaughterHordeContainBase through ILT 0x0001445C.

class SlaughterHordeContainBase
{
public:
	virtual ~SlaughterHordeContainBase();
};

__declspec(noinline) SlaughterHordeContainBase::~SlaughterHordeContainBase() {}

void Force_SlaughterHordeContainBase_Deleting_Destructor(SlaughterHordeContainBase *contain)
{
	delete contain;
}
