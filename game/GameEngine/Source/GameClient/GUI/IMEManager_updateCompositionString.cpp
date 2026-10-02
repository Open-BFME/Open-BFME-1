// cl: /DNDEBUG /MD /O2 /Ob2
// IMEManager::updateCompositionString at retail 0x0048CF10.

// Retail calls the import through its ILT thunk at 0x009F888A, which
// game/gen_small/imports_000.cpp defines as ?ji_009f888a@@YAXXZ (import slot
// 0x01359564 = IMM32!ImmGetCompositionStringW).  The thunk carries no
// signature, so the call goes through the retail stdcall shape below: four
// 32-bit arguments pushed, callee-cleaned, one plain `call`.
extern void ji_009f888a();

typedef long (__stdcall *ImmGetCompositionStringW_t)(void *context, unsigned long index, void *buffer, unsigned long bytes);

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
		long bytes = ((ImmGetCompositionStringW_t)&ji_009f888a)(m_context, 8, m_compositionString, 0x800);
		if (bytes >= 0)
		{
			m_compositionStringLength = bytes / 2;
			m_compositionCursorPos = ((ImmGetCompositionStringW_t)&ji_009f888a)(m_context, 0x80, 0, 0) & 0xffff;
		}
	}
	m_compositionString[m_compositionStringLength] = 0;
	m_compositionString[0x800] = 0;
}
