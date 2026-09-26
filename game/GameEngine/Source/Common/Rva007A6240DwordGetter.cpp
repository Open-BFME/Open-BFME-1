// cl: /O2

class Rva007A6240Object
{
public:
	unsigned getValue();

private:
	char m_padding[8];
	unsigned m_value;
};

unsigned Rva007A6240Object::getValue()
{
	return m_value;
}
