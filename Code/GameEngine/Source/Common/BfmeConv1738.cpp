void __cdecl bfmeStopAK(void *source, int handle, int flags);
int __cdecl bfmeStartAK(void *source);

class BfmeOwnAK
{
public:
	void bfmeToggleAK(int code);

	unsigned char m_bfmeHeadAK[0x288];
	void *m_bfmeSourceAK;
	unsigned char m_bfmeMidAK[0x80];
	int m_bfmeHandleAK;
};

void BfmeOwnAK::bfmeToggleAK(int code)
{
	if (code == 1)
	{
		int handle = m_bfmeHandleAK;

		if (handle != -1)
			bfmeStopAK(m_bfmeSourceAK, handle, 0);

		return;
	}

	void *source = m_bfmeSourceAK;

	if (source)
		m_bfmeHandleAK = bfmeStartAK(source);
}
