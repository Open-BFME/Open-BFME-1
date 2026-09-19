// cl: /O2

class Rva007A6250Object
{
public:
	float getValue() const;

private:
	char m_padding[0x60];
	float m_value;
};

float Rva007A6250Object::getValue() const
{
	return m_value;
}
