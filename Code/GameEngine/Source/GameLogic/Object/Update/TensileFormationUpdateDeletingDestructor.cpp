// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x00253600 calls TensileFormationUpdate::~TensileFormationUpdate through ILT 0x0001AB1D.

class TensileFormationUpdate
{
public:
	virtual ~TensileFormationUpdate();
};

__declspec(noinline) TensileFormationUpdate::~TensileFormationUpdate() {}

void Force_TensileFormationUpdate_Deleting_Destructor(TensileFormationUpdate *update)
{
	delete update;
}
