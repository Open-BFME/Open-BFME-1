struct Rva007FD010Target
{
	unsigned char m_prefix[0x29c];
	unsigned int m_value;
};

class Rva007FD010Accessor
{
public:
	unsigned int get(const Rva007FD010Target *target, unsigned int unused);
};

unsigned int Rva007FD010Accessor::get(const Rva007FD010Target *target, unsigned int)
{
	return target->m_value;
}
