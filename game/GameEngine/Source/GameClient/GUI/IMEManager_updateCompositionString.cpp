// cl: /DNDEBUG /MD /O2 /Ob2
// IMEManager::updateCompositionString at retail 0x0048CF10.

extern "C" long __stdcall ImmGetCompositionStringW(
	void *context, unsigned long index, void *buffer, unsigned long bytes);

class IMEManager
{
public:
	void updateCompositionString(void);

private:
	char m_pad00[0x10];
	void *m_context;
	char m_pad14[0x0a];
	unsigned short m_compositionString[0x801];
	unsigned short m_resultsString[0x801];
	unsigned short m_resultsStringEnd;
	char m_pad2024[0x1000];
	int m_compositionCursorPos;
	int m_compositionStringLength;
};

void IMEManager::updateCompositionString(void)
{
	m_compositionCursorPos = 0;
	m_compositionString[0] = 0;
	m_resultsStringEnd = 0;
	m_compositionStringLength = 0;
	if (m_context != 0)
	{
		long bytes = ImmGetCompositionStringW(m_context, 8, m_compositionString, 0x800);
		if (bytes >= 0)
		{
			m_compositionStringLength = bytes / 2;
			m_compositionCursorPos = ImmGetCompositionStringW(m_context, 0x80, 0, 0) & 0xffff;
		}
	}
	m_compositionString[m_compositionStringLength] = 0;
	m_compositionString[0x800] = 0;
}
