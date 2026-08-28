// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);

private:
	void *m_data;
};

class Rva002D8590
{
	AsciiString m_str;
	int m_4;
	int m_8;

public:
	Rva002D8590();
};

Rva002D8590::Rva002D8590()
	: m_str("")
{
	m_4 = 0;
	m_8 = 0;
}
