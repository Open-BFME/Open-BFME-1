// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x000B5E90 (9 bytes).
// Retail returns the bitwise OR of two 32-bit stack arguments.

class Rva000B5E90
{
public:
	static unsigned orValues(unsigned first, unsigned second);
};

unsigned Rva000B5E90::orValues(unsigned first, unsigned second)
{
	return first | second;
}
