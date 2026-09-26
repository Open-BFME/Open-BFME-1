// The retail body reads the object flag word at +0x3c and reports bit zero.
class Rva001FFAD0Object
{
public:
	bool test() const;

private:
	unsigned char m_prefix[0x3c];
	unsigned int m_flags;
};

bool Rva001FFAD0Object::test() const
{
	return (m_flags & 1) != 0;
}
