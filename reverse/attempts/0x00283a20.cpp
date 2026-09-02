// ?d_00283a20@@YAXXZ
// partial score=0.88 date=2026-09-03
extern "C" int (__cdecl * const g_bfmeD83A20Memcmp)(const void *left,
	const void *right, unsigned int count);

struct BfmeAsciiData
{
	char m_bfmeFields[4];
	unsigned short m_length;
	char m_bfmeReserved[2];
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);

	int bfmeCompare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text
			: reinterpret_cast<const char *>(0x0107388B);
		int length = m_data ? m_data->m_length : 0;
		const char *text = m_data ? m_data->m_text
			: reinterpret_cast<const char *>(0x0107388B);
		int result = g_bfmeD83A20Memcmp(text, otherText,
			length < otherLength ? length : otherLength);
		return result == 0 ? length - otherLength : result;
	}

private:
	BfmeAsciiData *m_data;
};

struct BfmeNamedStringEntry
{
	AsciiString m_name;
	char m_bfmeFields[0x2C];
	AsciiString m_value;
};

class Gen_00283A20
{
public:
	AsciiString bfmeFind(const AsciiString &name) const;

private:
	char m_bfmeFields[0x18];
	BfmeNamedStringEntry **m_bfmeBegin;
	BfmeNamedStringEntry **m_bfmeEnd;
};

// ?bfmeFind@Gen_00283A20@@QBE?AVAsciiString@@ABV2@@Z
AsciiString Gen_00283A20::bfmeFind(const AsciiString &name) const
{
	volatile int unused = 0;
	for (unsigned int index = 0; index <
		static_cast<unsigned int>(m_bfmeEnd - m_bfmeBegin); ++index) {
		if (m_bfmeBegin[index]->m_name.bfmeCompare(name) == 0)
			return m_bfmeBegin[index]->m_value;
	}

	return reinterpret_cast<const char *>(0x0107301C);
}
