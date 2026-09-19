// cl: /DNDEBUG /MD

class Rva00402170Object
{
public:
	unsigned char getByte() const;

private:
	char m_padding[4];
	unsigned char m_value;
};

unsigned char Rva00402170Object::getByte() const
{
	return m_value;
}
