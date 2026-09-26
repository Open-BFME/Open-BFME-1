// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0026EE30 (38 bytes).

class Rva0026EE30
{
public:
	void guardedUpdate();

private:
	unsigned char m_unmodelled_000[0x134];
	int m_value;
	int m_limit;
	unsigned char m_unmodelled_138[0x1EF];
	unsigned char m_gate;
	unsigned char m_unmodelled_32C[1];
	unsigned char m_flag;
};

void Rva0026EE30::guardedUpdate()
{
	if (m_gate == 0 && m_value > 0)
	{
		m_limit = 0;
		m_flag = 1;
	}
}
