// cl: /O2
// Open-BFME: preserves the displaced retail body at 0x0024A270 (8 bytes).
// The bytes only prove a byte flag at +0xC8 is set; no class identity survives.

class Rva0024A270
{
public:
	void apply();

private:
	unsigned char m_beforeFlag[0xC8];
	char m_flag;
};

void Rva0024A270::apply()
{
	m_flag = 1;
}
