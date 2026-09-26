// cl: /O2 /Ob1 /DNDEBUG /MD

// Retail at 0x00516650 returns the dword stored at this+0x08.  The carved
// boundary and its single caller do not prove the owning class or field name.
class Rva00516650DwordGetter
{
public:
	unsigned int get();

private:
	char m_padding[ 0x08 ];
	unsigned int m_value;
};

unsigned int Rva00516650DwordGetter::get()
{
	return m_value;
}
