// The carved boundary at 0x0045BD20 loads a float from this plus 0x2C.
// No caller or class table proves the owning type.
class Rva0045BD20FloatGetter
{
public:
	float get() const;

private:
	char m_padding[0x2C];
	float m_value;
};

float Rva0045BD20FloatGetter::get() const
{
	return m_value;
}
