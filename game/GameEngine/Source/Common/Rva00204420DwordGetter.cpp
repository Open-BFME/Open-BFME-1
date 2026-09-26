// The carved body reads one dword at this plus 0x04. No caller or class table
// names the owner, so this source keeps the address-derived identity.

class Rva00204420DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

unsigned int Rva00204420DwordGetter::get() const
{
	return m_value;
}
