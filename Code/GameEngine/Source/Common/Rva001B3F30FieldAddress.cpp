// ?get@Rva001B3F30Owner@@QAEPAHXZ
// Retail 0x001B3F30 returns the address of the field at this+0x54.

class Rva001B3F30Owner
{
public:
	int *get();

private:
	char m_pad00[0x54];
	int m_field54;
};

int *Rva001B3F30Owner::get()
{
	return &m_field54;
}
