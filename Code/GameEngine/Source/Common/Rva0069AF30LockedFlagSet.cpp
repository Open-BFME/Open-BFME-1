// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded byte flag updates selected by a bitmask argument.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

class Rva0069AF30Owner
{
public:
	void setFlags(unsigned char value, unsigned char mask);

	char m_pad0[0x62a];
	unsigned char m_flag0; // +0x62a  mask 8
	unsigned char m_flag1; // +0x62b  mask 2
	unsigned char m_flag2; // +0x62c  mask 4
	unsigned char m_flag3; // +0x62d  mask 1
	unsigned char m_flag4; // +0x62e  mask 0x10
	char m_pad1[0x95c - 0x62f];
	void *m_mutex;
};

void Rva0069AF30Owner::setFlags(unsigned char value, unsigned char mask)
{
	void *mutex = m_mutex;
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	unsigned char m = mask;
	unsigned char v = value;
	if (m & 1)
		m_flag3 = v;
	if (m & 0x10)
		m_flag4 = v;
	if (m & 2)
		m_flag1 = v;
	if (m & 4)
		m_flag2 = v;
	if (m & 8)
		m_flag0 = v;

	if (held)
		ReleaseMutex(mutex);
}
