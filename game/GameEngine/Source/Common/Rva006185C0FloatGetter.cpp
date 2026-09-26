// Retail RVA 0x006185C0 loads the float at this+0x14 and returns.
// No caller or identity table proves the owning class or field name.

class Rva006185C0FloatGetter
{
public:
	float get() const;

private:
	char m_padding[0x14];
	float m_value;
};

float Rva006185C0FloatGetter::get() const
{
	return m_value;
}
