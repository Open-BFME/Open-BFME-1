// The carved body at 0x00422630 returns the first dword from its receiver.

class Rva00422630Owner
{
public:
	int get() const;

	int value;
};

int Rva00422630Owner::get() const
{
	return value;
}
