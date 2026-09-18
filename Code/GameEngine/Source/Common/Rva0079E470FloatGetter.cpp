// cl: /DNDEBUG /MD /EHsc

class Rva0079E470Owner
{
public:
	float get() const;

private:
	char m_pad[0x74];
	float m_value;
};

// The carved body is reached only through thunk 0x0001CC79. Its neighboring
// setters fold across unrelated owners, so the address-derived owner is kept.
// ?get@Rva0079E470Owner@@QBEMXZ
float Rva0079E470Owner::get() const
{
	return m_value;
}
