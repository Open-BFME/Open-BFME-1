// cl: /Oy-
struct BfmeRectAAS
{
	int m_bfmeLeftAAS;
	int m_bfmeTopAAS;
	int m_bfmeRightAAS;
	int m_bfmeBottomAAS;
};

extern "C"
{
	__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) int __stdcall EnumThreadWindows(unsigned long id, int (__stdcall *fn)(void *, long), long param);
	__declspec(dllimport) long __stdcall GetWindowLongA(void *hwnd, int index);
	__declspec(dllimport) int __stdcall GetClientRect(void *hwnd, BfmeRectAAS *rect);
}

int __stdcall EnumThreadWndProc(void *hwnd, long param);

class BfmeHostAAS
{
public:
	bool bfmeProbeAAS();

	unsigned char m_bfmeHeadAAS[0x9f49];
	char m_bfme9F49AAS;
};

bool BfmeHostAAS::bfmeProbeAAS()
{
	char state = m_bfme9F49AAS;

	if (state != 0)
		return state > 0;

	void *found = 0;

	EnumThreadWindows(GetCurrentThreadId(), EnumThreadWndProc, (long)&found);

	if (found == 0)
		return true;

	m_bfme9F49AAS = (char)0xff;

	if ((GetWindowLongA(found, -0x10) & 0xc00000) != 0)
		m_bfme9F49AAS = 1;

	BfmeRectAAS r;

	if (GetClientRect(found, &r) != 0)
	{
		if (r.m_bfmeRightAAS - r.m_bfmeLeftAAS < r.m_bfmeBottomAAS - r.m_bfmeTopAAS)
			m_bfme9F49AAS = 1;
	}

	return m_bfme9F49AAS > 0;
}
