// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0024EA90 calls SlaughterHordeContainBase::~SlaughterHordeContainBase through ILT 0x0001445C.

class SlaughterHordeContainBase
{
public:
	virtual ~SlaughterHordeContainBase();
};

void Force_SlaughterHordeContainBase_Deleting_Destructor(SlaughterHordeContainBase *contain)
{
	// Emit the deleting wrapper while referring to the complete destructor's
	// owning TU, without supplying a second complete-destructor definition.
	SlaughterHordeContainBase value;
}
