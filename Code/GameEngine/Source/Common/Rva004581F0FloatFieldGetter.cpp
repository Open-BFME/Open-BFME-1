// cl: /O2 /Ob0

// Retail 0x004581F0 loads the float at this-relative offset 0x10 and returns it.
class Rva004581F0FloatField
{
public:
	char m_padding[0x10];
	float m_value;

	float get() const;
};

float Rva004581F0FloatField::get() const
{
	return m_value;
}
