// cl: /DNDEBUG /MD /EHs-c-

class Rva0037A7C0
{
public:
	unsigned char getByte() const;

private:
	char m_pad00[8];
	unsigned char m_byte08;
};

unsigned char Rva0037A7C0::getByte() const
{
	return m_byte08;
}
