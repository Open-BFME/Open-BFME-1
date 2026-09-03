// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);

private:
	char *data;
};

extern const char g_Rva0107301CEmptyString[];

class Rva00770E70
{
public:
	Rva00770E70();

private:
	AsciiString text;
	int first;
	int second;
	int third;
	int fourth;
};

Rva00770E70::Rva00770E70()
	: text(g_Rva0107301CEmptyString)
{
	first = 0;
	second = 0;
	third = 0;
	fourth = 0;
}
