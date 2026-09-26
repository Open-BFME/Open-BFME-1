// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva007BBDB0Str
{
public:
	const char *str();

	char m_pad[8];
	char *m_data;
};

const char *Rva007BBDB0Str::str()
{
	if (m_data)
		return m_data + 8;
	return "";
}

class Rva007BBDD0Str
{
public:
	const char *str();

	char m_pad[0x10];
	char *m_data;
};

const char *Rva007BBDD0Str::str()
{
	if (m_data)
		return m_data + 8;
	return "";
}

class Rva003879F0Str
{
public:
	const char *str();

	char m_pad[4];
	char *m_data;
};

const char *Rva003879F0Str::str()
{
	if (m_data)
		return m_data + 8;
	return "";
}
