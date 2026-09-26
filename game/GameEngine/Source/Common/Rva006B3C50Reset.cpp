// Clean reconstruction of the retail reset helper at RVA 0x006B3C50.

extern void __stdcall initializeRva006B3C50(void *buffer);

class Rva006B3C50Owner
{
public:
	void reset();

	char padding[0x44];
	int state;
};

void Rva006B3C50Owner::reset()
{
	char buffer[8];
	state = 0;
	initializeRva006B3C50(buffer);
}
