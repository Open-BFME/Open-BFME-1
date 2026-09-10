class BfmeLexEAN
{
public:
	int bfmeScanEAN();
	char bfmeExpandEAN(char *out);
	int bfmeFailEAN(int code);

	char *m_bfmePosEAN;
	char *m_bfmeLineEAN;
	char *m_bfmeSourceEAN;
	int m_bfmeLineNumberEAN;
	int m_bfmeTagEAN;
	char *m_bfmeBufEAN;
	int m_bfmeLimitEAN;
	char *m_bfmeTailEAN;
};

struct BfmeEntityEAN
{
	char *m_bfmeNameEAN;
	char m_bfmeCodeEAN;
	char m_bfmePaddingEAN[3];
};

extern BfmeEntityEAN g_bfmeEntityTableEAN[]; // retail 0x012B3ED0
__declspec(dllimport) int __cdecl bfmeCmp1026(char *left, char *right, int count);

char BfmeLexEAN::bfmeExpandEAN(char *out)
{
	++m_bfmePosEAN;

	if (*m_bfmePosEAN == 0)
		return 0;

	for (unsigned int index = 0; index < 5; ++index)
	{
		unsigned char c;
		char *name = g_bfmeEntityTableEAN[index].m_bfmeNameEAN;
		char *end = name;
		char *first = end + 1;

		do
			c = *end++;
		while (c != 0);

		int length = end - first;
		if (bfmeCmp1026(m_bfmePosEAN,
			g_bfmeEntityTableEAN[index].m_bfmeNameEAN, length) == 0)
		{
			m_bfmePosEAN += length;
			if (*m_bfmePosEAN != ';')
				return 0;

			*out = g_bfmeEntityTableEAN[index].m_bfmeCodeEAN;
			return 1;
		}
	}

	return 0;
}

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count);

int BfmeLexEAN::bfmeFailEAN(int code)
{
	BfmeLexEAN *self = this;
	char line[0x104];
	int length = 0;

	line[0] = 0;
	if (self->m_bfmeSourceEAN != 0)
	{
		char *cursor = self->m_bfmeSourceEAN;
		while (*cursor != 0 && *cursor != '\n')
		{
			++length;
			++cursor;
		}

		if (length != 0)
		{
			if (length >= 0x104)
				length = 0x103;
			strncpy(line, self->m_bfmeSourceEAN, length);
		}
	}

	self->m_bfmePosEAN = 0;
	self->m_bfmeLineNumberEAN = 0;
	self->m_bfmeSourceEAN = 0;
	self->m_bfmeLineEAN = 0;
	return code;
}

int BfmeLexEAN::bfmeScanEAN()
{
	int n = 0;

	for (;;)
	{
		char c = *m_bfmePosEAN;

		if (c == 0x26)
		{
			if (!bfmeExpandEAN(m_bfmeBufEAN + n))
				return bfmeFailEAN(-1);
		}
		else
		{
			m_bfmeBufEAN[n] = c;
		}

		c = *m_bfmePosEAN;

		if (c == 0x3c || c == 0)
			break;

		m_bfmePosEAN++;

		if (*m_bfmePosEAN == 0)
			return bfmeFailEAN(-1);

		if (n <= m_bfmeLimitEAN)
			n++;
	}

	m_bfmeBufEAN[n] = 0;

	m_bfmeTailEAN = m_bfmeBufEAN;

	return 3;
}
