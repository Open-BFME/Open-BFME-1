struct Rva007FD000Target
{
	unsigned char m_prefix[0x20];
	unsigned int m_value;
};

class Rva007FD000Accessor
{
public:
	unsigned int get(const Rva007FD000Target *target);
};

unsigned int Rva007FD000Accessor::get(const Rva007FD000Target *target)
{
	return target->m_value;
}
