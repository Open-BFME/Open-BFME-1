// Retail at 0x000DF1D0 returns the dword at this+0x10.
// The owning type and field semantics were not recovered.
class Rva000DF1D0DwordGetter
{
public:
	unsigned int get();

private:
	char m_padding[0x10];
	unsigned int m_value;
};

unsigned int Rva000DF1D0DwordGetter::get()
{
	return m_value;
}
