// cl: /DNDEBUG /MD /EHsc

class Rva003AC3C0
{
public:
	unsigned char getByteAt08() const;

private:
	unsigned char m_pad00[8];
	unsigned char m_byteAt08;
};

unsigned char Rva003AC3C0::getByteAt08() const
{
	return m_byteAt08;
}
