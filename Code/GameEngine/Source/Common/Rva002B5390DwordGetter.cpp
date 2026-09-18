// cl: /DNDEBUG /MD

class Rva002B5390DwordField
{
public:
	int get() const;

private:
	char m_padding[0x4];
	int m_value;
};

int Rva002B5390DwordField::get() const
{
	return m_value;
}
