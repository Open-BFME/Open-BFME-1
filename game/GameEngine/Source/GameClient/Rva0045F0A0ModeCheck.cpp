extern const char g_bfmeEmptyAscii[];

struct Rva0045F0A0AsciiData
{
	unsigned int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

struct Rva0045F0A0AsciiString
{
	Rva0045F0A0AsciiData *m_data;
	int getLength() const
	{
		return m_data != 0 ? m_data->m_length : 0;
	}
	char *str() const
	{
		return m_data != 0 ? m_data->m_text : (char *)g_bfmeEmptyAscii;
	}
};

class GameWindow
{
public:
	unsigned int winGetStatus();
};

class BfmeUnit1013
{
public:
	void bfmeStop1013(char value);
};

struct Rva0045F0A0Input
{
	unsigned char m_padding00[0x10];
	Rva0045F0A0AsciiString m_name;
	BfmeUnit1013 *m_unit;
};

class Rva0045F0A0
{
public:
	void process(Rva0045F0A0Input *input);

private:
	char m_enabled;
	unsigned char m_padding01[3];
	Rva0045F0A0AsciiString m_name;
};

__declspec(dllimport) int __cdecl bfmeCmp1026(char *, char *, int);

void Rva0045F0A0::process(Rva0045F0A0Input *input)
{
	if (bfmeCmp1026(input->m_name.str(), m_name.str(), m_name.getLength()) == 0)
	{
		BfmeUnit1013 *unit = input->m_unit;
		if (unit != 0)
		{
			if (((((GameWindow *)unit)->winGetStatus() >> 3) & 1) != m_enabled)
			{
				unit->bfmeStop1013(m_enabled);
			}
		}
	}
}
