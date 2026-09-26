// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The volume owner keeps one byte per channel/mode pair at +0x188.  The
// argument supplies a pointer to the cached-mode object used by the mixer.

class Rva000AF8C0CachedMode
{
public:
	int getMode(void);

	char m_padding0[0x38];
	unsigned char m_flags;
	char m_padding39[0x4b];
	unsigned int m_kind;
	int m_cachedMode;
	int m_first;
	int m_second;
};

class Rva00699580Owner
{
public:
	bool isDirty(Rva000AF8C0CachedMode **mode, int channel);

private:
	char m_pad[0x188];
	unsigned char m_state[48];
};

bool Rva00699580Owner::isDirty(Rva000AF8C0CachedMode **mode, int channel)
{
	Rva000AF8C0CachedMode *cached = *mode;
	int first = cached->m_first;
	int second = cached->m_second;
	int phase = 0;
	if (first == second)
		phase = 2;

	int modeIndex = cached->getMode();
	int offset = (channel + modeIndex * 2 + 0x62) * 4;
	unsigned char *state = (unsigned char *)this;
	if (state[offset + phase] != 0)
		return true;

	phase |= 1;
	offset += phase;
	if (state[offset] == 0)
		return false;
	return true;
}
