// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva008D30D0StringData
{
	char m_header[8];
	char m_text[1];
};

struct Rva008D30D0String
{
	Rva008D30D0StringData *m_data;
};

typedef int (__cdecl *Rva008D30D0Compare)(const char *, const char *);
extern void ji_009f6fa0();

class Rva008D30D0Owner
{
public:
	__declspec(noinline) void setEvent(Rva008D30D0String *name, void *, int remove);

private:
	char m_padding00[0x18];
	unsigned m_flags18;
};

void Rva008D30D0Owner::setEvent(Rva008D30D0String *name, void *, int remove)
{
	unsigned mask = 0;
	if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onPress") == 0)
		mask = 0x400;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onRelease") == 0)
		mask = 0x800;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onReleaseOutside") == 0)
		mask = 0x1000;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onRollOver") == 0)
		mask = 0x2000;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onRollOut") == 0)
		mask = 0x4000;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onDragOut") == 0)
		mask = 0x10000;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onDragOver") == 0)
		mask = 0x8000;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onLoad") == 0)
		mask = 1;
	else if (((Rva008D30D0Compare)ji_009f6fa0)(name->m_data->m_text, "onUnload") == 0)
		mask = 4;

	if (remove)
		m_flags18 &= ~mask;
	else
		m_flags18 |= mask;
}
