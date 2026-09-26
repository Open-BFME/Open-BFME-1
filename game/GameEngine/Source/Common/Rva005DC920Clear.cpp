// The carved body at 0x005DC920 loads its first dword, clears it, and returns.

class Rva005DC920Owner
{
public:
	void clear();

	volatile int value;
};

void Rva005DC920Owner::clear()
{
	int ignored = value;
	value = 0;
}
