// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva000AF8C0CachedMode
{
public:
	int getMode(void);

private:
	unsigned char m_padding0[0x38];
	unsigned char m_flags;
	unsigned char m_padding39[0x4b];
	unsigned int m_kind;
	volatile int m_cachedMode;
};

int Rva000AF8C0CachedMode::getMode(void)
{
	if (m_cachedMode != -1)
		return m_cachedMode;

	if ((m_flags & 0x10) != 0) {
		m_cachedMode = 1;
		return m_cachedMode;
	}

	switch (m_kind) {
		case 0:
			m_cachedMode = 2;
			return m_cachedMode;
		case 1:
			m_cachedMode = 1;
			return m_cachedMode;
		case 2:
			m_cachedMode = 0;
			return m_cachedMode;
		case 3:
			m_cachedMode = 3;
			return m_cachedMode;
		case 4:
			m_cachedMode = 0;
			return m_cachedMode;
		default:
			m_cachedMode = 0;
			return m_cachedMode;
	}
}
