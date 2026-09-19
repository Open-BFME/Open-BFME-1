// cl: /DNDEBUG /MD

class Rva003D5660Object
{
public:
	int *fieldAddress();

private:
	char m_padding[0x10];
	int m_value;
};

int *Rva003D5660Object::fieldAddress()
{
	return &m_value;
}
