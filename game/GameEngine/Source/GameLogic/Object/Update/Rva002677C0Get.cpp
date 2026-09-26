// cl: /O2 /DNDEBUG /MD /EHs-c-

class Rva002677C0Value
{
public:
	unsigned int get() const;

	unsigned char m_padding00[4];
	unsigned int m_value04;
};

unsigned int Rva002677C0Value::get() const
{
	return m_value04;
}
