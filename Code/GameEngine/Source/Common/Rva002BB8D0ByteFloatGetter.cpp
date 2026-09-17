// cl: /O2 /Ob0

class Rva002BB8D0ByteFloatGetter
{
public:
	float get() const;

	char m_padding[0x46c];
	unsigned char m_value;
};

float Rva002BB8D0ByteFloatGetter::get() const
{
	return (float)m_value;
}
