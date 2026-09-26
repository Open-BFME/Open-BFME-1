// cl: /O2

class Rva000EC9A0FieldGetter
{
public:
	unsigned int get(void) const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

// ?get@Rva000EC9A0FieldGetter@@QBEIXZ
unsigned int Rva000EC9A0FieldGetter::get(void) const
{
	return m_value;
}
