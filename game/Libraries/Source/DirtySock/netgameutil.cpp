// cl: /DNDEBUG /MD /GX /Od /GZ

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	struct NetGameUtilRef;
	void NetGameUtilControl(NetGameUtilRef *ref, int selector, int value);
}

int Rva007FE780Printf(const char *format, ...);

struct NetGameUtilRef
{
	char m_prefix[0x80];
	int m_maxWidth;
	int m_maxOutput;
	int m_maxInput;
	int m_advertiseFrequency;
};

// The 'advf', 'minp', 'mout' and 'mwid' control selectors, each of which logs
// "NetGameUtilControl: setting '<sel>' to %d".
void NetGameUtilControl(NetGameUtilRef *ref, int selector, int value)
{
	if (selector == 0x6D776964) {
		if (value <= 0x200) {
			ref->m_maxWidth = value + 14;
			Rva007FE780Printf("NetGameUtilControl: setting 'mwid' to %d\n", ref->m_maxWidth);
		} else {
			Rva007FE780Printf("NetGameUtilControl: 'mwid' value of %d is too large\n", value);
		}
	}
	if (selector == 0x6D696E70) {
		ref->m_maxInput = value;
		Rva007FE780Printf("NetGameUtilControl: setting 'minp' to %d\n", ref->m_maxInput);
	}
	if (selector == 0x6D6F7574) {
		ref->m_maxOutput = value;
		Rva007FE780Printf("NetGameUtilControl: setting 'mout' to %d\n", ref->m_maxOutput);
	}
	if (selector == 0x61647666) {
		ref->m_advertiseFrequency = value;
		Rva007FE780Printf("NetGameUtilControl: setting 'advf' to %d\n", ref->m_advertiseFrequency);
	}
}
