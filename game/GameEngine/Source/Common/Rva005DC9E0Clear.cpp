// The carved body at 0x005DC9E0 loads its first dword, clears it, and returns.

class Rva005DC9E0Owner
{
public:
	void clear();

	volatile int value;
};

void Rva005DC9E0Owner::clear()
{
	int ignored = value;
	value = 0;
}
