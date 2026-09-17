// cl: /O2

// Retail 0x0073A5B0 loads the float at this-relative offset 0x1C and returns it.
class Rva0073A5B0Owner
{
public:
	char m_padding[0x1C];
	float m_value;

	float get() const;
};

float Rva0073A5B0Owner::get() const
{
	return m_value;
}
