// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0052C1B0 calls AptPlayerStatus::~AptPlayerStatus through ILT 0x00003EE0.

class AptPlayerStatus
{
public:
	virtual ~AptPlayerStatus();
};

__declspec(noinline) AptPlayerStatus::~AptPlayerStatus() {}

void Force_AptPlayerStatus_Deleting_Destructor(AptPlayerStatus *status)
{
	delete status;
}
