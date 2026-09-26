// cl: /O2 /DNDEBUG /MD

// Retail 0x00750280 is a carved three-byte boundary containing only ret 4.
// The address-derived name preserves the unknown owner and the one stack
// argument that the return instruction proves.

class Rva00750280Owner
{
public:
	void ret4(int);
};

void Rva00750280Owner::ret4(int)
{
}
