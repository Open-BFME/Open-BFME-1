// cl: /O2 /DNDEBUG /MD

// Retail 0x00350230 returns the first dword at its receiver.

class Rva00350230Owner
{
public:
	int firstDword();
};

int Rva00350230Owner::firstDword()
{
	return *(int *)this;
}
