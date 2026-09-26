// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0006D5B0 (13 bytes).
// Retail sums two 32-bit stack arguments and pops both arguments on return.

class Rva0006D5B0
{
public:
	static unsigned __stdcall sum(unsigned first, unsigned second);
};

unsigned __stdcall Rva0006D5B0::sum(unsigned first, unsigned second)
{
	return first + second;
}
