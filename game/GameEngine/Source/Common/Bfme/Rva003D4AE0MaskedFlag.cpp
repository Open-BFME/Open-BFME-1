// cl: /DNDEBUG /MD /EHsc

class Rva003D4AE0
{
public:
	int maskedFlag() const;

private:
	unsigned char m_padding[0x0F];
	unsigned char m_flag;
};

int Rva003D4AE0::maskedFlag() const
{
	return m_flag & 1;
}
