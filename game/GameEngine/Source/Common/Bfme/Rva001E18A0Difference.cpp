// cl: /DNDEBUG /MD /EHsc

class Rva001E18A0
{
public:
	int difference() const;

private:
	unsigned char m_padding[0x18];
	int m_value;
	unsigned char m_gap[0x0C];
	int m_subtract;
};

int Rva001E18A0::difference() const
{
	return m_value - m_subtract;
}
