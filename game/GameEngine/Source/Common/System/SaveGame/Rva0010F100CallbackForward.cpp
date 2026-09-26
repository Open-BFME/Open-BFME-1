// Retail 0x0010F100 forwards callback arguments one and three to the
// two-argument receiver at the independently decoded ILT 0x00036917.
class Rva0010F100Receiver
{
public:
	void rva0010ea60(void *first, void *third);
};

void __cdecl rva0010f100Forward(void *first, Rva0010F100Receiver *receiver, void *third)
{
	receiver->rva0010ea60(first, third);
}
