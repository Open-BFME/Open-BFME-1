class Rva0044F600ByteGetter
{
public:
	unsigned char get(void) const;
};

unsigned char Rva0044F600ByteGetter::get(void) const
{
	return *((unsigned char *)this + 1);
}
