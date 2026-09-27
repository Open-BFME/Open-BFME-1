// cl: /O2 /DNDEBUG /MD

class EAStringC
{
	struct StringDataC
	{
		unsigned short m_refCount;
		unsigned short m_size;
		unsigned short m_maxSize;
		unsigned short m_hash;
	};

	StringDataC *m_data;

public:
	void setCodepoint0089DE40(int cp);
};

void EAStringC::setCodepoint0089DE40(int cp)
{
	char *text = reinterpret_cast<char *>(m_data) + 8;
	if (cp < 0x80)
	{
		text[0] = (char)cp;
		text[1] = 0;
		m_data->m_size = 1;
		m_data->m_hash = 0;
		return;
	}
	if (cp < 0x800)
	{
		text[0] = (char)((cp >> 6) | 0xC0);
		text[1] = (char)((cp & 0x3F) | 0x80);
		text[2] = 0;
		m_data->m_size = 2;
		m_data->m_hash = 0;
		return;
	}
	if (cp < 0x10000)
	{
		text[0] = (char)((cp >> 12) | 0xE0);
		text[1] = (char)(((cp >> 6) & 0x3F) | 0x80);
		text[2] = (char)((cp & 0x3F) | 0x80);
		text[3] = 0;
		m_data->m_size = 3;
		m_data->m_hash = 0;
		return;
	}
	text[0] = (char)((cp >> 18) | 0xF0);
	text[1] = (char)(((cp >> 12) & 0x3F) | 0x80);
	text[2] = (char)(((cp >> 6) & 0x3F) | 0x80);
	text[3] = (char)((cp & 0x3F) | 0x80);
	text[4] = 0;
	m_data->m_size = 4;
	m_data->m_hash = 0;
}
