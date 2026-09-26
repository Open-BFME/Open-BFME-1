// The carved boundary at 0x000B20E0 loads a float from this+0x1c and returns.
// No caller or class table proves the semantic owner.
class Rva000B20E0Owner
{
public:
	float fieldAt1C(void) const;

private:
	char m_padding[0x1c];
	float m_value;
};

float Rva000B20E0Owner::fieldAt1C(void) const
{
	return m_value;
}
