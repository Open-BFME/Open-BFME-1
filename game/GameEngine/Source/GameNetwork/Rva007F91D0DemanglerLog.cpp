// cl: /O2 /GX- /GS

struct Rva00800E50Header
{
	unsigned m_type;
	int m_flags;
	const char *m_text;
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log(int level, const char *format, ...);
};

extern int Rva007EB810Get();
extern "C" int __cdecl isprint(int value);
extern "C" int __cdecl Rva007EEC30(
	const char *text, unsigned char *destination, int size, const char *empty);

void __cdecl Rva007F91D0(Rva00800E50Header *header, const char *direction)
{
	if (direction)
		((Rva007EB810Diag *)Rva007EB810Get())->log(0, "%s ", direction);

	int flags = header->m_flags;
	if (flags & 0x80000000)
	{
		if (flags & 0x40000000)
			((Rva007EB810Diag *)Rva007EB810Get())->log(0, "req");
		else
			((Rva007EB810Diag *)Rva007EB810Get())->log(0, "res");
	}

	int type = header->m_type;
	char first = (char)(type >> 24);
	char second = (char)(type >> 16);
	char third = (char)(type >> 8);
	char fourth = *(const char *)&header->m_type;

	if (isprint(first) && isprint(second) && isprint(third) && isprint(fourth))
		((Rva007EB810Diag *)Rva007EB810Get())->log(0, "%c%c%c%c ", first, second, third, fourth);
	else
		((Rva007EB810Diag *)Rva007EB810Get())->log(0, "0x%02x%02x%02x%02x ", first, second, third, fourth);

	if (header->m_flags)
		((Rva007EB810Diag *)Rva007EB810Get())->log(0, "0x%08x ", header->m_flags);
	((Rva007EB810Diag *)Rva007EB810Get())->log(0, "{");

	const char *text = header->m_text;
	volatile char padding;
	unsigned char decoded[0x40];
	char firstChunk = 1;
	int length;
	while ((length = Rva007EEC30(text, decoded, 0x40, "")) != 0)
	{
		((Rva007EB810Diag *)Rva007EB810Get())->log(0x80, "%s%.120s", firstChunk ? "" : ", ", decoded);
		text += length;
		if (*text == '\n')
		{
			++text;
			firstChunk = 0;
		}
		else
			firstChunk = 1;
	}

	((Rva007EB810Diag *)Rva007EB810Get())->log(0, "}\n");
}
