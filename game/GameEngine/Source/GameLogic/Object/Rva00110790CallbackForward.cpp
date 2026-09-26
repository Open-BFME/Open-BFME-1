// Retail 0x00110790 forwards callback arguments one and three to the
// receiver at ILT 0x0001F546, which accepts two stack arguments and ECX.
class Rva00110790Receiver
{
public:
	void rva0010fe90(void *first, void *third);
};

void __cdecl rva00110790Forward(void *first, Rva00110790Receiver *receiver, void *third)
{
	receiver->rva0010fe90(first, third);
}
