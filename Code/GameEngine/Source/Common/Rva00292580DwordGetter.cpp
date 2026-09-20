// The carved body returns the dword at this plus 0x04.
// The caller proves no semantic owner, so the field name keeps the address.

class Rva00292580DwordField
{
public:
	int get() const;

private:
	int m_unmodelled_00;
	int m_value;
};

int Rva00292580DwordField::get() const
{
	return m_value;
}
