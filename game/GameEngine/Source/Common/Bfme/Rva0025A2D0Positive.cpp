// cl: /DNDEBUG /MD /EHsc

class Rva0025A2D0
{
public:
	bool isPositive() const;

private:
	unsigned char m_padding[0x08];
	int m_value;
};

bool Rva0025A2D0::isPositive() const
{
	return m_value > 0;
}
