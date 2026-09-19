// cl: /O2

class Rva007A6220Object
{
public:
	float getValue() const;

private:
	char m_padding[0x4c];
	float m_value;
};

float Rva007A6220Object::getValue() const
{
	return m_value;
}
