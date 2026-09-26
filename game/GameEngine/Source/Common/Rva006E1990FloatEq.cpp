// cl: /O2 /Ob0

class Rva006E1990
{
public:
	bool ok();

private:
	char m_pad[0x40];
	float m_val;
};

bool Rva006E1990::ok()
{
	return m_val == 100.0f;
}
