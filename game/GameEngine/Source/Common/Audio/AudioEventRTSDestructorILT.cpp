// cl: /DNDEBUG /MD /EHsc

// Retail ILT 0x0002671F tail-jumps to the nonvirtual 77-byte record destructor.
// The forwarder retains its existing address-derived ledger identity.
class Gen_000F9C60
{
public:
	~Gen_000F9C60();
};

class Rva0002671FAudioEventRTSDestructorThunk
{
public:
	void forward();
};

void Rva0002671FAudioEventRTSDestructorThunk::forward()
{
	Gen_000F9C60 *record = (Gen_000F9C60 *)this;
	record->Gen_000F9C60::~Gen_000F9C60();
}
