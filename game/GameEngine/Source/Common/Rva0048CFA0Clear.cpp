// cl: /DNDEBUG /MD /O2 /Ob2
// Address-derived wide composition-buffer clear at retail 0x0048CFA0.

extern "C" long __stdcall ImmGetCompositionStringW(
	void *context, unsigned long index, void *buffer, unsigned long bytes);

class Rva0048CFA0
{
public:
	void getResultsString(void);

private:
	unsigned char m_padding00[0x10];
	void *m_context;
	unsigned char m_padding14[0x100c];
	unsigned short m_text[0x800];
	unsigned short m_tail;
};

void Rva0048CFA0::getResultsString(void)
{
	int stringLen = 0;
	m_text[0] = 0;
	if (m_context != 0)
	{
		long bytes = ImmGetCompositionStringW(m_context, 0x800, m_text, 0x800);
		if (bytes >= 0)
			stringLen = bytes / 2;
	}
	m_text[stringLen] = 0;
	m_tail = 0;
}
