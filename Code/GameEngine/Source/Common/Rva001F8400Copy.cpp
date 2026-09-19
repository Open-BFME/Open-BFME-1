// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva001F8400Values
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
};

class Rva001F8400CopyState
{
public:
	void copyFrom(const Rva001F8400Values &source);

private:
	unsigned char m_padding_00[ 0x68 ];
	unsigned char m_active;
	unsigned char m_padding_69[ 3 ];
	Rva001F8400Values m_values;
};

void Rva001F8400CopyState::copyFrom(const Rva001F8400Values &source)
{
	m_active = 1;
	m_values = source;
}
