// cl: /DNDEBUG /MD /EHsc

class Rva007AEC70
{
public:
	void initialize();

private:
	unsigned char m_unmodelled_000[0x08];
	unsigned m_field_008;
	unsigned m_field_00C;
	unsigned m_field_010;
	unsigned char m_unmodelled_014[0x0c];
	unsigned m_field_020;
	unsigned char m_unmodelled_024[0x04];
	unsigned m_field_028;
	unsigned char m_unmodelled_02C[0x3c];
	unsigned m_field_068;
};

void Rva007AEC70::initialize()
{
	m_field_028 = ~0u;
	m_field_068 = 0;
	m_field_010 = 0;
	m_field_00C = 0;
	m_field_008 = 0;
	m_field_020 = 0;
}
