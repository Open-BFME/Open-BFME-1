// cl: /DNDEBUG /MD /EHsc

class Rva0029BC20
{
public:
	int difference() const;

private:
	unsigned char m_padding[0x20];
	int m_value;
	int m_subtract;
};

int Rva0029BC20::difference() const
{
	return m_value - m_subtract;
}
