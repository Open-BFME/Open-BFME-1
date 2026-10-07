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
	int winEnable(bool enable);		// ILT 0x0004A1FB -> 0x004782E0
};

struct Rva0045F0A0Input
{
	unsigned char m_padding00[0x10];
	Rva0045F0A0AsciiString m_name;
	GameWindow *m_unit;
};

class Rva0045F0A0
{
public:
	void process(Rva0045F0A0Input *input);

private:
	bool m_enabled;
	unsigned char m_padding01[3];
	Rva0045F0A0AsciiString m_name;
};

extern "C" __declspec(dllimport) int __cdecl strncmp(char *, char *, int);

void Rva0045F0A0::process(Rva0045F0A0Input *input)
{
	if (strncmp(input->m_name.str(), m_name.str(), m_name.getLength()) == 0)
	{
		GameWindow *unit = input->m_unit;
		if (unit != 0)
		{
			if (((unit->winGetStatus() >> 3) & 1) != m_enabled)
			{
				unit->winEnable(m_enabled);
			}
		}
	}
}
